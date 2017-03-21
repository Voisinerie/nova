#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <server.h>

Server::Server()
{

}

Server::~Server()
{
    shutdown(_socket, SHUT_RDWR);
    close(_socket);
}

void Server::start()
{
    int val;
    socklen_t len;
    protoent* proto;
    proto = getprotobyname("tcp");
    if ((_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    {
        std::cerr << "Could not create socket" << std::endl;
        exit(1);
    }
    val = 1;
    len = sizeof(val);
    setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &val, len);
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
    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    _kernel_queue = kqueue();
    _kernel_events.resize(3);
    _kernel_slots.resize(64);
    EV_SET(_kernel_events.data(), _socket, EVFILT_READ, EV_ADD, 0, 0, nullptr);
    EV_SET(_kernel_events.data() + 1, SIGINT, EVFILT_SIGNAL, EV_ADD, 0, 0, nullptr);
    EV_SET(_kernel_events.data() + 2, SIGINT, EVFILT_SIGNAL, EV_ADD, 0, 0, nullptr);
    loop();
}

void Server::loop()
{
    std::cout << "Server started on localhost:8080" << std::endl;
    _running = true;
    while (_running)
    {
        tick();
    }
    std::cout << "Server stopped" << std::endl;
}

void Server::tick()
{
    int event_count;

    event_count = kevent(_kernel_queue, _kernel_events.data(), _kernel_events.size(), _kernel_slots.data(), _kernel_slots.size(), nullptr);
    std::cout << "Event" << std::endl;
    for (int i = 0; i < event_count; ++i)
        handle_event(_kernel_slots[i]);
}

int Server::allocate_client()
{
    return 0;
}

void Server::handle_event(struct kevent& event)
{
    switch (event.filter)
    {
        case EVFILT_SIGNAL:
            handle_event_signal(event);
            break;
        case EVFILT_READ:
            handle_event_read(event);
            break;
    }
}

void Server::handle_event_read(struct kevent& event)
{
    /* FIXME */
    sockaddr_in addr;
    socklen_t addr_len;
    static const char* str = "HTTP/1.1 200 OK\r\nContent-Length: 20\r\n\r\n<h1>Test server</h1>";
    static const size_t str_size = strlen(str);

    int client = accept(_socket, reinterpret_cast<sockaddr*>(&addr), &addr_len);
    send(client, str, str_size, 0);
    shutdown(client, SHUT_RDWR);
    close(client);
}

void Server::handle_event_signal(struct kevent& event)
{
    _running = false;
}
