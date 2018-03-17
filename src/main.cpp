#include "server/Server.h"
#include "protocol/protocol.pb.h"

#include <string>

int main() {
    std::string address = "localhost";
    std::string service = "9988";
    Server *server;

    server = new Server(address, service, 256);
    server->run();

    return 0;
}