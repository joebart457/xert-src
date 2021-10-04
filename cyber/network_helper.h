#pragma once

#include "network.hpp"
#include "callable.h"

#include <unordered_map>
#include <memory>
#include <atomic>

enum class MsgType : uint32_t
{
	Message,
};

class tokenizer;
class parser;
class interpreter;

class iNetHelper {
public:
	iNetHelper(
		uint16_t port,
		std::shared_ptr<interpreter> interpreter,
		bool bContinueOnError);
	~iNetHelper(){}

	uint16_t Port() { return m_port; }
	std::any GetLastError() { return m_lastError; }
protected:
	std::any InterpretMsgObject(std::vector<uint8_t> body);

	std::mutex m_mutex;
	bool m_bContinueOnError = false;
	std::any m_lastError = nullptr;
	uint16_t m_port{ 0 };

	std::shared_ptr<tokenizer> m_tokenizer{ nullptr };
	std::shared_ptr<parser> m_parser{ nullptr };
	std::shared_ptr<interpreter> m_interpreter{ nullptr }, m_iContext{ nullptr };
};


class NetClient : 
	public net::client_interface<MsgType>, 
	public iNetHelper 
{
public:
	NetClient(const std::string& host,
		uint16_t port, std::shared_ptr<callable> callback,
		std::shared_ptr<interpreter> interpreter,
		bool bContinueOnError = false,
		bool bSuppressOutput = false);
	~NetClient(){}


	bool Start();
	bool TryConnect();
	void SendMessageData(std::vector<uint8_t>& msg);

	std::string Host() { return m_host; }
private:

	void EngineThread();
	void CoreUpdate();
	std::any DoCallback(std::shared_ptr<callable> callback, _args args);

	std::shared_ptr<callable> m_callback;
	std::string m_host;

	// If anything sets this flag to false, the engine
	// will attempt to shut down gracefully
	static std::atomic<bool> bAtomActive;
};


class NetServer : 
	public net::server_interface<MsgType>,
	public iNetHelper
{	
public:
	NetServer(uint16_t port,
		std::shared_ptr<callable> onClientConnect,
		std::shared_ptr<callable> onClientValidated,
		std::shared_ptr<callable> onClientDisconnect,
		std::shared_ptr<callable> onMessage,
		std::shared_ptr<interpreter> interpreter,
		bool bContinueOnError = false,
		bool bSuppressOutput = false);

	void SendMessageData(std::shared_ptr<net::connection<MsgType>> client, std::vector<uint8_t>& msg);
	void MessageAllFromData(std::vector<uint8_t>& msg);

private:
	std::any DoCallback(std::shared_ptr<callable> callback, _args args);

	std::shared_ptr<callable> m_onClientConnect;
	std::shared_ptr<callable> m_onClientValidated;
	std::shared_ptr<callable> m_onClientDisconnect;
	std::shared_ptr<callable> m_onMessage;


protected:
	bool OnClientConnect(std::shared_ptr<net::connection<MsgType>> client);
	void OnClientValidated(std::shared_ptr<net::connection<MsgType>> client);
	void OnClientDisconnect(std::shared_ptr<net::connection<MsgType>> client);
	void OnMessage(std::shared_ptr<net::connection<MsgType>> client, net::message<MsgType>& msg);

};