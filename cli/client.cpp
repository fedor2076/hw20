#include "clientsocket.h"

int main()
{
  std::string data;
  Client_socket sock;

  sock.insock("\n");//отсылаем на сервер
  while(true)
    {
        data = sock.outsock();//принимаем с сервера
        if(data == "end")
          {
            data.clear();
            close(sock._socket_descriptor);
            break;
          }
       else if (data[0] != '~')
          {
            std::cout << ">" << data ;
            data.clear();
          }
      else if (data[0] == '~')
          {
            std::cout << "->";
            getline(std::cin, data);
            sock.insock(data);//отсылаем на сервер
            data.clear();
  }/*9
  else if(data == "#!")
  {
    std::cout << "-------#!-----\n";
  sock.insock(" new client ");
  data.clear();
}*/

}



}
