#pragma once
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h> // Библиотека для работы с сокетами
#include <arpa/inet.h>

#define PORT 55000
#define HOSTNAME "127.0.0.1"
#define MESSAGE_LENGTH 1024

class Client_socket
{
public:
  Client_socket();
  ~Client_socket(){};
  void insock(std::string ts);
  std::string outsock();
  void create_socket();
  void create_connection();
  int _socket_descriptor;
private:
  char _buffer[MESSAGE_LENGTH];
  char _message[MESSAGE_LENGTH];
  struct sockaddr_in _address;

};
