//
// Created by kuba on 17.03.18.
//

#ifndef POKERGAME_CLIENTHANDLER_H
#define POKERGAME_CLIENTHANDLER_H

#include <cstddef>

class ClientHandler {

private:
    const int client_sock;
    bool logged_in;
    bool handle_msg(unsigned char *const data, size_t size);

public:
    ClientHandler(const int client_sock);
    void listen();
    bool send_msg(unsigned char *const data, size_t size);
};


#endif //POKERGAME_CLIENTHANDLER_H
