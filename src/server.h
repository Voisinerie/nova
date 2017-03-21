#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <client_state.h>
#include <non_copyable.h>

class Server : public NonCopyable
{
public:
    Server();
    ~Server();

    void start();

private:
    void    loop();
    void    tick();
    int     allocate_client();

    int                         _socket;
    size_t                      _client_buffer_count;
    std::vector<ClientState>    _client_states;
    std::vector<int>            _client_sockets;
};

#endif
