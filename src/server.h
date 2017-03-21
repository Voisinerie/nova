#ifndef SERVER_H
#define SERVER_H

#include <sys/event.h>
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
    void    handle_event(struct kevent& event);
    void    handle_event_read(struct kevent& event);
    void    handle_event_signal(struct kevent& event);

    bool                        _running;
    int                         _socket;
    size_t                      _client_buffer_count;
    std::vector<ClientState>    _client_states;
    std::vector<int>            _client_sockets;
    int                         _kernel_queue;
    std::vector<struct kevent>  _kernel_events;
    std::vector<struct kevent>  _kernel_slots;
};

#endif
