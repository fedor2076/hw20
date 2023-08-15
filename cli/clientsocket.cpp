#include "clientsocket.h"

Client_socket::Client_socket()
{
  create_socket();
  create_connection();
}

void Client_socket::create_socket()
{
  _address.sin_family = AF_INET;
  _address.sin_port = htons( PORT );
  _address.sin_addr.s_addr = inet_addr(HOSTNAME);
  _socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
}

void Client_socket::create_connection()
{
  if (connect(_socket_descriptor, (struct sockaddr*)&_address, sizeof(_address)) < 0)
    {
        std::cout <<"\n connection attempt failed.\n";
        exit(1);
    }
  std::cout<<"Connection Successfull.\n";
}

void Client_socket::insock(std::string ts)
{
  strcpy (_message, ts.c_str());
  sendto(_socket_descriptor, _message, MESSAGE_LENGTH, 0, nullptr, sizeof(_address));
}

std::string Client_socket::outsock()
{
  recvfrom(_socket_descriptor, _buffer, sizeof(_buffer), 0, nullptr, nullptr);
  return std::string(_buffer);
}
