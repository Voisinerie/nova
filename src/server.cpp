#include <netdb.h>
#include <cstdlib>
#include <iostream>
#include <server.h>

Server::Server()
{

}

Server::~Server()
{

}

void Server::start()
{
    protoent* proto;
    proto = getprotobyname("tcp");
    if ((_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    {
        std::cerr << "Could not create socket" << std::endl;
        exit(1);
    }
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8080);
    if (bind(_socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)))
    {
        std::cerr << "Could not bind socket to 0.0.0.0:8080 (already in use?)" << std::endl;
        exit(1);
    }
    if (listen(_socket, 128))
    {
        std::cerr << "Could not listen on socket" << std::endl;
        exit(1);
    }
    loop();
}

void Server::loop()
{
    for (;;)
    {
        tick();
    }
}

void Server::tick()
{

}

int Server::allocate_client()
{
    return 0;
}
