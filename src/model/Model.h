//
// Created by kuba on 18.03.18.
//

#ifndef POKERGAME_MODEL_H
#define POKERGAME_MODEL_H

#include "Lobby.h"
#include "server/ClientHandler.h"
#include "protocol/Protocol.pb.h"

#include <map>
#include <list>

class Model {

private:
    std::list<Player *> players;
    std::map<const ClientHandler *, Player *> clientHandlersMap;
    std::map<Player *, const ClientHandler *> playersMap;
    Lobby lobby;
    Player *getUserWithName(std::string name);

public:
    void login(const Login &login, ClientHandler *const clientHandler);
    void createTable(const CreateTable &createTable, ClientHandler *const clientHandler);
    void joinTable(const JoinTable &joinTable, ClientHandler *const clientHandler);
    void leaveTable(const LeaveTable &leaveTable, ClientHandler *const clientHandler);
    void raise(const Raise &raise, ClientHandler *const clientHandler);
    void fold(const Fold &fold, ClientHandler *const clientHandler);
    void call(const Call &call, ClientHandler *const clientHandler);
    void disconnect(ClientHandler *const clientHandler);
};


#endif //POKERGAME_MODEL_H
