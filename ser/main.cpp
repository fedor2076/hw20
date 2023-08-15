//данные User и Message реализованы в <vector>
//стартовое меню и меню чата реализованы в <map>
//g++ -std=c++20 -o chat *.cpp

#include "consolechat.h"

auto main() -> int
{

		ConsoleChat ConsoleChat;

	ConsoleChat.startLoad();// Запуск чата

	while (ConsoleChat.chatStarted()) // Пока чат запущен
	{
		ConsoleChat.startMenu(); // Отображать стартовое меню

		while (ConsoleChat.getOnlineUser()) // Пока в системе есть пользователь
		{
			ConsoleChat.chatMenu(); // Отображать меню чата
		}
	}

}
