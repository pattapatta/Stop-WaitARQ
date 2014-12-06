#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <boost/asio.hpp>
#include <unistd.h>

class Client
{
    // Attributi
    private:
        udp::endpoint reciever_enpoint;
        string nome_file;


    // Metodi
    public:
        Client();
        Client(char[] reciever);
        ~Client();


    protected:
    private:
};

#endif // CLIENT_H
