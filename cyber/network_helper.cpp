#include "network_helper.h"

#include "ContextBuilder.hpp"


iNetHelper::iNetHelper(
	uint16_t port,
	std::shared_ptr<interpreter> interpreter,
	bool bContinueOnError
) : m_port{ port }, m_iContext{ interpreter }, m_bContinueOnError{ bContinueOnError }
{
	m_tokenizer = ContextBuilder().BuildTokenizer();
	m_parser = ContextBuilder().BuildParser();
	m_interpreter = ContextBuilder().BuildInterpreter(false);
}

std::any iNetHelper::InterpretMsgObject(std::vector<uint8_t> body)
{
	std::string src = std::string(body.begin(), body.end());
	try {
		auto tokens = m_tokenizer->tokenize(src);
		m_parser->init(tokens);
		return m_interpreter->acceptExpression(m_parser->parse_expression());
	}
	catch (PanicException pe) {
		m_lastError = ExceptionBuilder().Build(ExceptionTypes().PARSING(), "unable to parse message data", Severity().MEDIUM()).value();
	}
	catch (ProgramException pe) {
		m_lastError = ExceptionBuilder().Build(ExceptionTypes().PARSING(), "unable to parse message data", Severity().MEDIUM()).value();
	}
	catch (std::exception e) {
		m_lastError = ExceptionBuilder().Build(ExceptionTypes().PARSING(), "unable to parse message data", Severity().MEDIUM()).value();
	}
	return nullptr;
}


std::atomic<bool> NetClient::bAtomActive = false;

NetClient::NetClient(const std::string& host, 
	uint16_t port, 
	std::shared_ptr<callable> callback, 
	std::shared_ptr<interpreter> interpreter, 
	bool bContinueOnError,
	bool bSuppressOutput)
	: client_interface<MsgType>(bSuppressOutput), iNetHelper(port, interpreter, bContinueOnError), m_callback{ callback }, m_host{ host }
{
	m_tokenizer = ContextBuilder().BuildTokenizer();
	m_parser = ContextBuilder().BuildParser();
	m_interpreter = ContextBuilder().BuildInterpreter(false);
}

bool NetClient::Start()
{
	// Start the thread
	bAtomActive = true;
	std::thread t = std::thread(&NetClient::EngineThread, this);

	// Wait for thread to be exited
	t.join();

	return true;
}

void NetClient::Stop()
{
	bAtomActive = false;
}



bool NetClient::TryConnect()
{
	if (!IsConnected()) {
		return Connect(m_host, m_port);
	}
	return true;
}


void NetClient::SendMessageData(std::vector<uint8_t>& msg) {
	net::message<MsgType> message;
	message.header.id = MsgType::Message;
	message.addSerializedData(msg);
	Send(message);
}

void NetClient::EngineThread()
{
	if (!IsConnected()) bAtomActive = false;

	while (bAtomActive)
	{
		// Run as fast as possible
		CoreUpdate();
	}
}

void NetClient::CoreUpdate() {
	// Check for incoming network messages
	if (IsConnected())
	{
		while (!Incoming().empty())
		{
			auto msg = Incoming().pop_front().msg;
			std::vector<std::any> args = { InterpretMsgObject(msg.body) };

			DoCallback(m_callback, args);
		}
	}
}

std::any NetClient::DoCallback(std::shared_ptr<callable> callback, _args args)
{
	std::scoped_lock(m_mutex);
	try {
		return callback->call(m_iContext, args);
	}
	catch (PanicException pe) {
		m_lastError = pe.value();
		if (!m_bContinueOnError) {
			bAtomActive = false;
		}
	}
	catch (ProgramException pe) {
		m_lastError = ExceptionBuilder().Build(pe.type(),pe.message(), pe.severity(), pe.loc()).value();
		if (!m_bContinueOnError) {
			bAtomActive = false;
		}
	}
	catch (std::exception e) {
		m_lastError = ExceptionBuilder().Build(ExceptionTypes().SYSTEM(), e.what(), Severity().CRITICAL()).value();
		if (!m_bContinueOnError) {
			bAtomActive = false;
		}
	}
	return nullptr;
}



NetServer::NetServer(uint16_t port,
	std::shared_ptr<callable> onClientConnect,
	std::shared_ptr<callable> onClientValidated,
	std::shared_ptr<callable> onClientDisconnect,
	std::shared_ptr<callable> onMessage,
	std::shared_ptr<interpreter> interpreter,
	bool bContinueOnError,
	bool bSuppressOutput)
	: net::server_interface<MsgType>(port, bSuppressOutput), iNetHelper(port, interpreter, bContinueOnError),
	m_onClientConnect{ onClientConnect }, m_onClientValidated{ onClientValidated }, m_onClientDisconnect{ onClientDisconnect }, m_onMessage{ onMessage }
{
}

void NetServer::SendMessageData(uint32_t clientId, std::vector<uint8_t>& msg) {
	net::message<MsgType> message;
	message.header.id = MsgType::Message;
	message.addSerializedData(msg);
	MessageClient(GetConnectionById(clientId), message);
}

void NetServer::MessageAllFromData(std::vector<uint8_t>& msg, uint32_t except)
{
	net::message<MsgType> message;
	message.header.id = MsgType::Message;
	message.addSerializedData(msg);
	MessageAllClients(message, GetConnectionById(except));
}

std::any NetServer::DoCallback(std::shared_ptr<callable> callback, _args args)
{
	std::scoped_lock(m_mutex);
	try {
		return callback->call(m_iContext, args);
	}
	catch (PanicException pe) {
		m_lastError = pe.value();
		if (!m_bContinueOnError) {
			RequestStop(); // Can't actually stop from a handler, so must request server shutdown on its own
		}
	}
	catch (ProgramException pe) {
		m_lastError = ExceptionBuilder().Build(pe.type(), pe.message(), pe.severity(), pe.loc()).value();
		if (!m_bContinueOnError) {
			RequestStop();
		}
	}
	catch (std::exception e) {
		m_lastError = ExceptionBuilder().Build(ExceptionTypes().SYSTEM(), e.what(), Severity().CRITICAL()).value();
		if (!m_bContinueOnError) {
			RequestStop();
		}
	}
	return nullptr;
}


bool NetServer::OnClientConnect(const std::string& host, uint16_t port)
{
	std::scoped_lock(m_mutex);

	if (m_onClientConnect == nullptr) {
		// There is no filter function, so just allow the connection 
		return true;
	}
	std::vector<std::any> args = { host, port };
	std::any temp = DoCallback(m_onClientConnect, args);
	return Utilities().isTruthyNoThrow(temp);
}

void NetServer::OnClientValidated(std::shared_ptr<net::connection<MsgType>> client)
{
	// Client passed validation check
	if (client == nullptr) {
		return;
	}
	if (m_onClientValidated == nullptr) {
		// There is no callback
		return;
	}
	std::vector<std::any> args = { client->GetID() };
	DoCallback(m_onClientValidated, args);
}

void NetServer::OnClientDisconnect(std::shared_ptr<net::connection<MsgType>> client)
{
	// Client passed validation check
	if (client == nullptr) {
		return;
	}
	if (m_onClientDisconnect == nullptr) {
		// There is no callback
		return;
	}
	std::vector<std::any> args = { client->GetID() };
	DoCallback(m_onClientDisconnect, args);

}

void NetServer::OnMessage(std::shared_ptr<net::connection<MsgType>> client, net::message<MsgType>& msg)
{
	if (client == nullptr) {
		return;
	}
	if (m_onMessage == nullptr) {
		// There is no callback
		return;
	}
	std::vector args = { client->GetID(), InterpretMsgObject(msg.body) };
	DoCallback(m_onMessage, _args(args));
}