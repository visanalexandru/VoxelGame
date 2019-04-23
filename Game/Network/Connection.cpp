#include "Connection.h"

Connection::Connection(const std::string ip,int port)
{
    //ctor
    initialize_connection(ip,port);
}
void Connection::initialize_connection(const std::string ip,int port)
{
    sf::Socket::Status status = socket.connect(ip,port);
    if(status==sf::Socket::Done)
        std::cout<<"CONNECTED"<<std::endl;
    else
        std::cout<<"COULD NOT CONNECT"<<std::endl;
}
const std::string Connection::receive_data()
{
    sf::Packet packet;
    sf::Socket::Status status=socket.receive(packet);
    if(!has_done(status))
        std::cout<<"COULD NOT RECEIVE PACKET"<<std::endl;
    std::string received;
    packet>>received;
    return received;


}
bool Connection::has_done(sf::Socket::Status stats)
{
    return stats==sf::Socket::Status::Done;
}
void Connection::send_data(std::string to_send)
{
    sf::Packet packet;
    packet<<to_send;
    sf::Socket::Status status=socket.send(packet);
    if(!has_done(status))
        std::cout<<"COULD NOT SEND PACKET"<<std::endl;
}
Connection::~Connection()
{
    //dtor
}
