//
// Created by kuba on 20.03.18.
//

#ifndef POKERGAME_LOBBY_H
#define POKERGAME_LOBBY_H

#include "Table.h"
#include "Player.h"

#include <protocol/Protocol.pb.h>

class Lobby {

private:
    std::list<Table *>tables;
    std::map<Player *, Table *>playersMap;

public:
    const std::list<Table *> &getTables() const;
    void createTable(const std::string &name, int maxPlayers);
    void joinTable(const std::string &name, Player *player);
    void leaveTable(const std::string &name, Player *player);
    void deleteTable(const std::string &name);

    DummyLobbyView *getLobbyView();
};


#endif //POKERGAME_LOBBY_H
