#pragma once
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>

#define PORT 55000
#define MESSAGE_LENGTH 1024

class Server_socket
{
public:
  Server_socket();
  ~Server_socket(){close(_socket_descriptor);};
  void create_socket();
  void bind_socket();
  void insock(std::string ts);
  std::string outsock();

  int _socket_descriptor;
private:
char _buffer[MESSAGE_LENGTH];
char _message[MESSAGE_LENGTH];
int _message_size;
socklen_t _length;
struct sockaddr_in _address;
struct sockaddr_in _client;
};
