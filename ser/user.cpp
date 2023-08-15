#include "user.h"

User::User(const std::string& login, std::string& password, std::string& name) : _login(login), _password(password), _name(name)
{
}

std::string User::getLogin() const
{
	return _login;
}
std::string  User::getPassword() const
{
	return _password;
}
std::string  User::getName() const
{
	return _name;
}
