//
// Created by kuba on 18.03.18.
//

#ifndef POKERGAME_MODEL_H
#define POKERGAME_MODEL_H

#include "Player.h"
#include "Lobby.h"
#include "server/ClientHandler.h"
#include "protocol/Protocol.pb.h"

#include <map>
#include <list>


class Model {

private:
    std::list<Player *> players;
    std::map<const ClientHandler *, Player *> clientHandlersMap;
    Lobby lobby;
    bool isPlayerWithName(std::string name);

public:
    void login(const MsgLogin &login, ClientHandler *const clientHandler);
    void joinTable(const MsgJoinTable &joinTable, ClientHandler *const clientHandler);
    void leaveTable(const MsgLeaveTable &leaveTable, ClientHandler *const clientHandler);
    void raise(const MsgRaise &raise, ClientHandler *const clientHandler);
    void fold(const MsgFold &fold, ClientHandler *const clientHandler);
    void call(const MsgCall &call, ClientHandler *const clientHandler);
    void disconnect(ClientHandler *const clientHandler);
};


#endif //POKERGAME_MODEL_H
