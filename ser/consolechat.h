#pragma once
#include <map>
#include <vector>
#include <memory>
#include "message.h"
#include <fstream>
#include <filesystem>
#include "serversocket.h"
#include "sha1.h"
namespace fs = std::filesystem;

class LoginException :public std::exception
{
public:
	LoginException(const std::string& msg) :_msg(msg) {}
	virtual const char* what() const noexcept override
	{
		return "error: user login already exists ";
	}
private:
	std::string _msg;
};

class ConsoleChat: public Server_socket
{
public:
	void start();
	bool chatStarted() const;
	void startMenu();
	void signUp();
	void logIn();
	std::shared_ptr<User> getOnlineUser() const;
	void chatMenu();
	void sendMessage();
	int searchValue(const std::string& name, const std::map<std::string, std::string>& my_map);
	void startLoad();
	string hashPassword(const string& password);
	bool hashCompare(const string& password, const string& hash_password);

private:
	std::vector<User> _user;
	std::shared_ptr<User> _onlineUser = nullptr;
	std::vector<Message> _message;
	bool _chatStarted = false;
	std::shared_ptr<User> getUserByLogin(const std::string login) const;
	void openChat() const;
	std::map <std::string, std::string>
		main_menu = {
		{"1", "Regisrer"},
		{"2", "Enter chat"},
		{"3", "Leave the chat"},
	};
		std::map <std::string, std::string>
		chat_menu = {
		{"1", "Write a message"},
		{"2", "Exit"},
	};

};
