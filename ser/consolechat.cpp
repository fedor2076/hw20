#include "consolechat.h"
#include <iostream>

Server_socket server;

bool ConsoleChat::chatStarted() const
{
	return _chatStarted;
}

void ConsoleChat::start()
{
	_chatStarted = true;
}

string ConsoleChat::hashPassword(const std::string& password)
{
	uint* digest = sha1(password.c_str(), password.length());
	string hash_string;
	for(int i = 0; i<SHA1HASHLENGTHUINTS; ++i)
	{
		hash_string += to_string(digest[i]);
  }
	delete[] digest;
	return hash_string;
}

bool ConsoleChat::hashCompare(const std::string& password, const std::string& hash_password)
{
	return (hashPassword(password)==hash_password);
}

void ConsoleChat::startLoad()
{
	std::string file_n = "users";

	std::string login, password, name;
	std::ifstream in(file_n);

	if(!in.is_open())
	{
		std::ofstream in(file_n);
		fs::permissions(file_n ,
			fs::perms::group_write | fs::perms::group_read | fs::perms::others_all,
			fs::perm_options::remove);
			in.close();
		}
		if(in.is_open())
		{
			while(std::getline(in, login) && std::getline(in, password) && std::getline(in, name))
			{
				User user = User(login, password, name);
				_user.push_back(user);
			}
			fs::permissions(file_n ,
				fs::perms::group_write | fs::perms::group_read | fs::perms::others_all,
				fs::perm_options::remove);
			}
			in.close();
			//------------------------------------------------------------
			file_n = "messages";

			std::string from, to, text;
			in.open(file_n);

		if(!in.is_open())
			{
				std::ofstream in(file_n);
				fs::permissions(file_n ,
					fs::perms::group_write | fs::perms::group_read | fs::perms::others_all,
					fs::perm_options::remove);
					in.close();
				}
				if(in.is_open())
				{
					while(std::getline(in, from) && std::getline(in, to) && std::getline(in, text))
					{
						Message message = Message(from, to, text);
						_message.push_back(message);
					}
					fs::permissions(file_n ,
						fs::perms::group_write | fs::perms::group_read | fs::perms::others_all,
						fs::perm_options::remove);
					}
					in.close();
					//-------------------------------------------------------------------
					std::string action;
					action = server.outsock();


					start();
}

int ConsoleChat::searchValue(const std::string& name, const std::map<std::string, std::string>& my_map)
{
	int i = 1;
	for (auto& element : my_map)
		{
			if (name == element.first)
					return i;
			++i;
		}
	return 0;
}

void ConsoleChat::startMenu()//главное меню
{
	std::string action;
	server.insock("\tWelcome to chat!\n\n Choose an action to continue: \n\n") ;

	for (auto& element : main_menu)
		{
				action = element.first + " " + element.second + "\n";
				server.insock(action) ;
		}

	server.insock("~");
	action = server.outsock();
	switch (searchValue(action, main_menu))
		{
			case 1:
				signUp();
						break;
			case 2:
				logIn();
						break;
			case 3:
				server.insock("end");
				//_chatStarted = false;
					break;
			default:
				server.insock("Please check that the characters you are entering are correct.\n");
					break;
		}
};

std::shared_ptr<User> ConsoleChat::getUserByLogin(const std::string login) const
{
	for (auto& user : _user)
		{
			if (login == user.getLogin())
					return std::make_shared<User>(user);
		}
	return nullptr;
}

std::shared_ptr<User>  ConsoleChat::getOnlineUser() const
{
	return _onlineUser;
}

void ConsoleChat::logIn()//вход в чат
{
	std::string login, password;

	server.insock("Please enter a login: ");
	server.insock("~");
	login = server.outsock();

	server.insock("Enter password: ");
	server.insock("~");
	password = server.outsock();

	_onlineUser = getUserByLogin(login);
bool b = hashCompare(password, _onlineUser->getPassword());
	if (_onlineUser == nullptr || !b )
		{
			_onlineUser = nullptr;
			server.insock("Invalid login or password, please try again\n");
		}
}

void ConsoleChat::signUp()//регистрация
{
	std::string login, password, name;

	server.insock("Please enter a login: ");
	server.insock("~");
	login = server.outsock();

	server.insock("Enter password: ");
	server.insock("~");
	password = server.outsock();

	server.insock("Enter your name: ");
	server.insock("~");
	name = server.outsock();

	try
		{
			if (getUserByLogin(login) || login == "all")
				{
					throw LoginException("error: ");
				}
		}
	catch (const LoginException& ex)
		{
			std::cerr << "\n\n (" << ex.what() << ") \n\n";
			server.insock(ex.what());
			server.insock("\n");
			return;
		}
	password = hashPassword(password);
	User user = User(login, password, name);
	_user.push_back(user);
	_onlineUser = std::make_shared<User>(user);

	std::ofstream out("users", std::ios::app);
	if(out.is_open())
		{
			out<<user.getLogin()<<"\n"<<user.getPassword()<<"\n"<<user.getName()<<"\n";
		}
	out.close();
	server.insock("\nCongratulations! You have successfully registered!\n");
}

void ConsoleChat::openChat() const //вывод сообщений чата
{
	std::string sender, recipient;
	server.insock("-------users chatting online-----\n");
	server.insock(" login: ");
	for (auto& user : _user)
		{
			server.insock(" " + user.getLogin() + " ");
		}
	server.insock("\n--------login: " + _onlineUser->getLogin() + " Name: " + _onlineUser->getName() + "-----------------\n\n");
	for (auto& message : _message)
		{
			if (_onlineUser->getLogin() == message.getSender() || _onlineUser->getLogin() == message.getRecipient() || message.getRecipient() == "all")
					{
						sender = (_onlineUser->getLogin() == message.getSender()) ? _onlineUser->getLogin()  : getUserByLogin(message.getSender())->getLogin();
						if (message.getRecipient() == "all")
							{
								recipient = "all";
							}
						else
							{
								recipient = (_onlineUser->getLogin() == message.getRecipient()) ? _onlineUser->getLogin() : getUserByLogin(message.getRecipient())->getLogin();
							}
						server.insock(sender + ": to " + recipient + ":\n");
						server.insock(message.getLetter() + ";\n");
					}
		}
	server.insock("---------------------------------\n\n");
}

void ConsoleChat::sendMessage() //отправка сообшения
{
	std::string recipient, text;
	std::ofstream out("messages", std::ios::app);
	server.insock("to (login or all) - ");

	server.insock("~");
	recipient = server.outsock();

	server.insock("~");
	text = server.outsock();

	if (!(recipient == "all" || getUserByLogin(recipient)))
		{
			server.insock("error no such user  -- " + recipient + "\n");
			return;
		}
	if (recipient == "all")
		{
			_message.push_back(Message(_onlineUser->getLogin(), "all", text));
			if(out.is_open())
				{
					out<<_onlineUser->getLogin()<<"\n"<<"all"<<"\n"<<text<<"\n";
				}
		}
	else
		{
			_message.push_back(Message(_onlineUser->getLogin(), getUserByLogin(recipient)->getLogin(), text));
			server.insock("message send -  " + recipient + ":\n ");
			out<<_onlineUser->getLogin()<<"\n"<<getUserByLogin(recipient)->getLogin()<<"\n"<<text<<"\n";
		}
	out.close();
}

void ConsoleChat::chatMenu() //меню чата
{
	std::string action;
	action = "Welcome " + _onlineUser->getName() + "\n";
	server.insock(action);

	do
	{
		openChat();
		server.insock("\nChoose an action: \n");

		for (auto& element : chat_menu)
			{
				server.insock(element.first + " " + element.second + "\n");
			}

		server.insock("~");
		action = server.outsock();

		if(action[0]=='1')
			{
				sendMessage();
			}
		else if (action[0]=='2')
			{
				_onlineUser = nullptr;
			}
		}
		while (_onlineUser);
}
