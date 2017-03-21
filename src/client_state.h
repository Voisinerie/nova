#ifndef CLIENT_STATE_H
#define CLIENT_STATE_H

#include <cstdint>

enum class ClientState : uint8_t
{
    None,
    Recv,
    Idle
};

#endif
