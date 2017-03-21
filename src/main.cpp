#include <nova/config.h>
#include <server.h>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    Server server;
    server.start();

    return 0;
}
