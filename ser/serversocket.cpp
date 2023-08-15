#include "serversocket.h"
const char *end_string = "end";

Server_socket::Server_socket()
{
  create_socket();
  bind_socket();
}

void Server_socket::create_socket()
{
  _socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);// Создадим UDP сокет
  _address.sin_addr.s_addr = htonl(INADDR_ANY);
  _address.sin_port = htons(PORT); // Зададим порт для соединения
  _address.sin_family = AF_INET;// Используем IPv4
}

void Server_socket::bind_socket()
{
  bind(_socket_descriptor, (struct sockaddr*)&_address, sizeof(_address));
}
void Server_socket::insock(std::string ts)
{
  strcpy (_message, ts.c_str());
  sendto(_socket_descriptor, _message, MESSAGE_LENGTH, 0, (struct sockaddr*)&_client, sizeof(_client));
}
std::string Server_socket::outsock()
{
  _length = sizeof(_client);
  recvfrom(_socket_descriptor, _buffer, sizeof(_buffer), 0, (struct sockaddr*)&_client, &_length);
  return std::string(_buffer);
}
