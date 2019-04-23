#ifndef CONNECTION_H
#define CONNECTION_H
#include <SFML/Network.hpp>
#include<iostream>
class Connection
{
public:
    Connection(const std::string ip,int port);
    virtual ~Connection();
    void send_data(const std::string to_send);
    const std::string receive_data();

protected:
    void initialize_connection(const std::string ip,int port);
private:
    bool has_done(sf::Socket::Status stat);
    sf::TcpSocket socket;
};

#endif // CONNECTION_H
