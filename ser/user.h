#pragma once
#include <string>

class User
{
public:
	User(const std::string& login, std::string& password, std::string& name);
	~User() = default;

	std::string getLogin() const;
	std::string getPassword() const;
	std::string getName() const;
private:
	std::string _login;
	std::string _password;
	std::string _name;
};
