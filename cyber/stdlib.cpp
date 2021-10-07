#include "stdlib.h"

#include <ctime>
#include <thread>
#include <vector>
#include <chrono>
#include <thread>

#include "FileHandle.hpp"
#include "Utilities.h"
#include "StringUtilities.h"
#include "exceptions.hpp"
#include "network_helper.h"
#include "Serializer.hpp"
#include "db_helper.h"
#include "ConsoleHandle.hpp"


// Thread

std::any thread_sleep(std::shared_ptr<interpreter> i, _args args)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(args.get<uint64_t>(0)));
	return nullptr;
}

// Time

std::any time_timestamp(std::shared_ptr<interpreter> i, _args args)
{
	int64_t result = std::time(nullptr);
	return result;
}

std::any time_timestamp_to_timestring(std::shared_ptr<interpreter> i, _args args)
{
	int64_t timestamp = args.get<int64_t>(0);
	std::tm timeStruct;
	localtime_s(&timeStruct, &timestamp);
	char buffer[32];

	std::strftime(buffer, 32, "%x %X", &timeStruct); // see documentation for format specifiers
	return std::string(buffer);
}

std::any time_timestamp_to_timestring_f(std::shared_ptr<interpreter> i, _args args)
{
	std::time_t timestamp = args.get<int64_t>(0);
	std::string szFormat = args.get<std::string>(1);
	std::tm timeStruct;
	localtime_s(&timeStruct, &timestamp);
	char buffer[64];

	std::strftime(buffer, 64, szFormat.c_str(), &timeStruct); // see documentation for format specifiers
	return std::string(buffer);
}



// DB Methods

std::any db_open(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	std::shared_ptr<db_helper> db = context->get<std::shared_ptr<db_helper>>("__raw__");
	db->open(args.get<std::string>(0));
	return nullptr;
}


std::any db_get(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	std::shared_ptr<db_helper> db = context->get<std::shared_ptr<db_helper>>("__raw__");

	std::vector<std::any> results = db->get(args.get<std::string>(0));

	std::shared_ptr<klass_definition> ls = context->get_coalesce<std::shared_ptr<klass_definition>>("Containers.list");
	klass_instance results_container = ls->create();
	std::any_cast<std::shared_ptr<native_fn>>(results_container.Get("constructor", location()))->call(i, _args(results));
	return results_container;
}


std::any db_run_prepared_query(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	std::shared_ptr<db_helper> db = context->get<std::shared_ptr<db_helper>>("__raw__");

	std::vector<std::any> results = db->run_prepared(
		std::any_cast<std::string>(args.at(0)),
		args.subset(2, 0),
		args.get<std::shared_ptr<klass_definition>>(1),
		false);

	std::shared_ptr<klass_definition> ls = context->get_coalesce<std::shared_ptr<klass_definition>>("Containers.list");
	klass_instance results_container = ls->create();
	results_container.Get<std::shared_ptr<native_fn>>("constructor", location())->call(i, _args(results));
	return results_container;
}


// List methods

std::any list_push(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	auto raw = context->get<std::shared_ptr<std::vector<std::any>>>("__raw__");
	if (raw == nullptr) {
		throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
	}

	raw->push_back(args.at(0));
	return nullptr;
}

std::any list_remove(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	auto raw = context->get<std::shared_ptr<std::vector<std::any>>>("__raw__");
	if (raw == nullptr) {
		throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
	}

	raw->erase(raw->begin() + args.get<int32_t>(0));

	return nullptr;
}


std::any list_size(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	auto raw = context->get<std::shared_ptr<std::vector<std::any>>>("__raw__");
	if (raw == nullptr) {
		throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
	}

	return static_cast<uint32_t>(raw->size());
}

std::any list_constructor(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	context->define("__raw__", std::make_shared<std::vector<std::any>>(args.data()), false, location());

	return nullptr;
}

std::any list_join(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	auto raw = context->get<std::shared_ptr<std::vector<std::any>>>("__raw__");
	if (raw == nullptr) {
		throw ExceptionBuilder().Build(ExceptionTypes().TYPE_MISMATCH(), "__raw__ was nullptr", Severity().HIGH());
	}

	std::string delim = args.get<std::string>(0);
	std::string result = "";
	if (raw->size() >= 1) {
		result = Utilities().stringify(raw->at(0));
	}
	for (unsigned int i{ 1 }; i < raw->size(); i++) {
		result += delim + Utilities().stringify(raw->at(i));
	}
	return result;
}

// Map methods
std::any map_add(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	std::string szName = args.get<std::string>(0);
	std::any value = args.at(1);

	context->define(szName, value , true, location());
	return nullptr;
}

std::any map_delete(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	std::string szName = args.get<std::string>(0);

	return context->remove(szName);
}

std::any map_constructor(std::shared_ptr<interpreter> i, _args args)
{
	return nullptr;
}

std::any map_exists(std::shared_ptr<interpreter> i, _args args)
{
	auto context = Utilities().fetch_context(i);
	return context->exists(args.get<std::string>(0));
}


// Std

std::any print(std::shared_ptr<interpreter> i, _args args)
{
	for (unsigned int j{ 0 }; j < args.size(); j++) {
		std::cout << std::any_cast<std::string>(::to_string(i, args.at(j)));
	}
	return nullptr;
}


std::any to_string(std::shared_ptr<interpreter> i, std::any& rhs)
{
	return Utilities().stringify(rhs);
}

// Null

std::any null_isNullType(std::shared_ptr<interpreter> i, _args args)
{
	return args.at(0).type() == typeid(nullptr);
}


// String

std::any string_split(std::shared_ptr<interpreter> i, _args args)
{
	auto context = Utilities().fetch_context(i);
	auto lsProto = context->get_coalesce<std::shared_ptr<klass_definition>>("Containers.list");
	std::string szSrc = args.get<std::string>(0);
	std::string szDelim = args.get<std::string>(1);
	std::vector<std::string> results = StringUtilities().split(szSrc, szDelim);
	std::vector<std::any> arguments;
	for (auto str : results) {
		arguments.push_back(str);
	}
	klass_instance lsInstance = lsProto->create();
	lsInstance.Get<std::shared_ptr<native_fn>>("constructor", location())->call(i, _args(arguments));
	return lsInstance;
}


std::any string_rtrim(std::shared_ptr<interpreter> i, _args args)
{
	std::string szSrc = args.get<std::string>(0);
	return StringUtilities().rtrim(szSrc);
}

std::any string_ltrim(std::shared_ptr<interpreter> i, _args args)
{
	std::string szSrc = args.get<std::string>(0);
	return StringUtilities().ltrim(szSrc);
}

std::any string_trim(std::shared_ptr<interpreter> i, _args args)
{
	std::string szSrc = args.get<std::string>(0);
	return StringUtilities().trim(szSrc);
}

std::any string_find(std::shared_ptr<interpreter> i, _args args)
{
	return StringUtilities().find(args.get<std::string>(0), args.get<std::string>(1));
}

std::any string_substr(std::shared_ptr<interpreter> i, _args args)
{
	return StringUtilities().substr(args.get<std::string>(0), args.get<uint64_t>(1), args.get<uint64_t>(2));
}

std::any string_pad(std::shared_ptr<interpreter> i, _args args)
{
	return StringUtilities().pad(args.get<std::string>(0), args.get<uint8_t>(1), args.get<int64_t>(2));
}

std::any string_to_char(std::shared_ptr<interpreter> i, _args args)
{
	std::string src = args.get<std::string>(0);
	if (src.size() != 1) {
		throw ExceptionBuilder().Build(ExceptionTypes().RUNTIME(), "unable to convert string of size " + std::to_string(src.size()) + " to char", Severity().MEDIUM());
	}
	return static_cast<uint8_t>(src.at(0));
}

std::any string_length(std::shared_ptr<interpreter> i, _args args)
{
	return static_cast<uint32_t>(args.get<std::string>(0).size());
}


// Console

std::any console_write(std::shared_ptr<interpreter> i, _args args)
{
	std::cout << Utilities().stringify(args.at(0));
	return nullptr;
}
std::any console_writeline(std::shared_ptr<interpreter> i, _args args)
{
	std::cout << Utilities().stringify(args.at(0)) << "\n";
	return nullptr;
}

std::any console_readKey(std::shared_ptr<interpreter> i, _args args)
{
	return ConsoleHandle().ReadKey();
}

std::any console_readLine(std::shared_ptr<interpreter> i, _args args)
{
	return ConsoleHandle().ReadLine();
}

// Language

std::any print_environment(std::shared_ptr<interpreter> i, _args args)
{
	Utilities().fetch_context(i)->output();
	return nullptr;
}

std::any print_operators(std::shared_ptr<interpreter> i, _args args)
{
	Utilities().fetch_context(i)->output_operators();
	return nullptr;
}


std::any flush_imports(std::shared_ptr<interpreter> i, _args args)
{
	Utilities().check_context(i);
	i->FlushImports();
	return nullptr;
}

std::any flush_import(std::shared_ptr<interpreter> i, _args args)
{
	Utilities().check_context(i);
	i->FlushImport(args.get<std::string>(0));
	return nullptr;
}


// FileSystem
std::any fs_relative_path(std::shared_ptr<interpreter> i, _args args)
{
	auto context = Utilities().fetch_context(i);
	auto fs = context->get<std::shared_ptr<klass_definition>>("FileSystem");
	auto wd = fs->Get<std::string>("WorkingDirectory", location());
	return wd + "/" + args.get<std::string>(0);
}

std::any fs_copy_file(std::shared_ptr<interpreter> i, _args args)
{
	FileHandle().copyFile(args.get<std::string>(0), args.get<std::string>(1));
	return nullptr;
}

std::any fs_remove_all(std::shared_ptr<interpreter> i, _args args)
{
	uint64_t removed = FileHandle().removeAll(args.get<std::string>(0));
	return removed;
}

std::any fs_read_file(std::shared_ptr<interpreter> i, _args args)
{
	auto context = Utilities().fetch_context(i);
	auto arrLines = FileHandle().readFile(args.get<std::string>(0));

	auto listDefintion = context->get_coalesce<std::shared_ptr<klass_definition>>("Containers.list");

	std::vector<std::any> arguments;
	for (std::string line : arrLines) {
		arguments.push_back(line);
	}
	auto lsInstance = listDefintion->create();
	Utilities().getCallable(lsInstance.Get("constructor", location()))->call(i, _args(arguments));

	return lsInstance;
}

std::any fs_real_file_to_string(std::shared_ptr<interpreter> i, _args args)
{
	return FileHandle().readFileAsString(args.get<std::string>(0));
}

std::any fs_read_line_from_file(std::shared_ptr<interpreter> i, _args args)
{
	return FileHandle().readLine(args.get<std::string>(0), args.get<uint64_t>(1));
}

std::any fs_write_to_file(std::shared_ptr<interpreter> i, _args args)
{
	klass_instance lsInstance = args.get<klass_instance>(1);
	uint64_t size = lsInstance.Get<uint64_t>("size", location());
	std::vector<std::string> data;
	for (uint64_t i{ 0 }; i < size; i++) {
		data.push_back(Utilities().stringify(lsInstance.Get(std::to_string(i), location())));
	}

	FileHandle().writeToFile(args.get<std::string>(0), data, args.get<bool>(2));
	return nullptr;
}

std::any fs_write_line_to_file(std::shared_ptr<interpreter> i, _args args)
{
	FileHandle().writeLine(args.get<std::string>(0), args.get<std::string>(1), args.get<bool>(2));
	return nullptr;
}

std::any fs_count_lines(std::shared_ptr<interpreter> i, _args args)
{
	return FileHandle().countLines(args.get<std::string>(0));
}

std::any fs_current_path(std::shared_ptr<interpreter> i, _args args)
{
	return FileHandle().current_path();
}

std::any fs_parent_path(std::shared_ptr<interpreter> i, _args args)
{
	return FileHandle().parent_path(args.get<std::string>(0));
}

std::any fs_absolute_path(std::shared_ptr<interpreter> i, _args args)
{
	return FileHandle().absolute_path(args.get<std::string>(0));
}


std::any fs_rename_file(std::shared_ptr<interpreter> i, _args args)
{
	FileHandle().rename(args.get<std::string>(0), args.get<std::string>(1));
	return nullptr;
}

std::any fs_file_size(std::shared_ptr<interpreter> i, _args args)
{
	return FileHandle().file_size(args.get<std::string>(0));
}

std::any fs_exists(std::shared_ptr<interpreter> i, _args args)
{
	return FileHandle().exists(args.get<std::string>(0));
}

std::any fs_replace_line(std::shared_ptr<interpreter> i, _args args)
{
	return FileHandle().replaceLine(args.get<std::string>(0), args.get<std::string>(1), args.get<uint64_t>(2));
}

std::any fs_get_unique_name(std::shared_ptr<interpreter> i, _args args)
{
	return FileHandle().getUniqueName(args.get<std::string>(0), args.get<uint32_t>(1));
}


// Network

std::any net_create_client(std::shared_ptr<interpreter> i, _args args) 
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	std::shared_ptr<callable> native_callback = nullptr;
	std::any callback = args.at(2);
	if (callback.type() != typeid(nullptr)) {
		native_callback = Utilities().getCallable(callback);
	}
	std::any client = std::make_shared<NetClient>(args.get<std::string>(0), args.get<uint16_t>(1), native_callback, i, args.get<bool>(3), args.get<bool>(4));

	context->define("raw",
		client,	true, location()
	);

	return nullptr;
}


std::any net_client_send(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetClient> client = context->get<std::shared_ptr<NetClient>>("raw");
	if (client == nullptr) {
		return false;
	}

	auto data = Serializer().Serialize(args.at(0));
	client->SendMessageData(data);
	return true;
}


std::any net_client_isconnected(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetClient> client = context->get<std::shared_ptr<NetClient>>("raw");
	if (client == nullptr) {
		return false;
	}
	return client->IsConnected();
}

std::any net_client_connect(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetClient> client = context->get<std::shared_ptr<NetClient>>("raw");
	if (client == nullptr) {
		return false;
	}
	return client->TryConnect();
}


std::any net_client_disconnect(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetClient> client = context->get<std::shared_ptr<NetClient>>("raw");
	if (client == nullptr) {
		return nullptr;
	}
	client->Disconnect();
	return nullptr;
}

std::any net_client_start(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetClient> client = context->get<std::shared_ptr<NetClient>>("raw");
	if (client == nullptr) {
		return false;
	}
	return client->Start();
}

std::any net_client_start_async(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetClient> client = context->get<std::shared_ptr<NetClient>>("raw");
	if (client == nullptr) {
		return false;
	}
	std::thread t(&NetClient::Start, client);
	t.detach();
	return true;
}


std::any net_client_port(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetClient> client = context->get<std::shared_ptr<NetClient>>("raw");
	if (client == nullptr) {
		return static_cast<uint16_t>(0);
	}
	return client->Port();
}

std::any net_client_host(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetClient> client = context->get<std::shared_ptr<NetClient>>("raw");
	if (client == nullptr) {
		return std::string("");
	}
	return client->Host();
}


std::any net_client_getlasterror(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetClient> client = context->get<std::shared_ptr<NetClient>>("raw");
	if (client == nullptr) {
		return nullptr;
	}
	return client->GetLastError();
}



std::any net_create_server(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	std::shared_ptr<callable> onClientConnect = nullptr;
	std::shared_ptr<callable> onClientValidated = nullptr;
	std::shared_ptr<callable> onClientDisconnect = nullptr;
	std::shared_ptr<callable> onMessage = nullptr;

	if (args.at(1).type() != typeid(nullptr)) {
		onClientConnect = Utilities().getCallable(args.at(1));
	}
	if (args.at(2).type() != typeid(nullptr)) {
		onClientValidated = Utilities().getCallable(args.at(2));
	}
	if (args.at(3).type() != typeid(nullptr)) {
		onClientDisconnect = Utilities().getCallable(args.at(3));
	}
	if (args.at(4).type() != typeid(nullptr)) {
		onMessage = Utilities().getCallable(args.at(4));
	}
	std::any server = std::make_shared<NetServer>(args.get<uint16_t>(0), onClientConnect, onClientValidated, onClientDisconnect, onMessage, i, args.get<bool>(5), args.get<bool>(6));

	context->define("raw",
		server, true, location()
	);

	return nullptr;
}

std::any net_server_messageclient(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetServer> server = context->get<std::shared_ptr<NetServer>>("raw");

	if (server == nullptr) {
		return nullptr;
	}

	auto data = Serializer().Serialize(args.at(1));
	server->SendMessageData(args.get<std::shared_ptr<net::connection<MsgType>>>(0), data);
	return nullptr;
}

std::any net_server_messageall(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetServer> server = context->get<std::shared_ptr<NetServer>>("raw");

	if (server == nullptr) {
		return nullptr;
	}

	auto data = Serializer().Serialize(args.at(0));
	server->MessageAllFromData(data);
	return nullptr;
}

std::any net_server_getconnectionbyid(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetServer> server = context->get<std::shared_ptr<NetServer>>("raw");

	if (server == nullptr) {
		return nullptr;
	}

	return server->GetConnectionById(args.get<uint32_t>(0));
}


std::any net_server_start(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetServer> server = context->get<std::shared_ptr<NetServer>>("raw");

	if (server == nullptr) {
		return false;
	}
	return server->Start();
}

std::any net_server_stop(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetServer> server = context->get<std::shared_ptr<NetServer>>("raw");

	if (server == nullptr) {
		return false;
	}
	server->Stop();
	return true;
}

std::any net_server_update(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetServer> server = context->get<std::shared_ptr<NetServer>>("raw");

	if (server == nullptr) {
		return nullptr;
	}
	server->Update(args.get<uint32_t>(0), args.get<bool>(1));
	return nullptr;
}


std::any net_server_getlasterror(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetServer> server = context->get<std::shared_ptr<NetServer>>("raw");
	if (server == nullptr) {
		return nullptr;
	}
	return server->GetLastError();
}

std::any net_server_port(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<NetServer> server = context->get<std::shared_ptr<NetServer>>("raw");
	if (server == nullptr) {
		return 0;
	}
	return server->Port();
}