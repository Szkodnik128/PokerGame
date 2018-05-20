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
    bool createTable(const std::string &name, int maxPlayers);
    bool joinTable(const std::string &name, Player *player);
    void leaveTable(const std::string &name, Player *player);
    void deleteTable(const std::string &name);

    Table *getTableByName(const std::string &name) const;
    Table *getTableByPlayer(Player *player) const;

    DummyLobbyView *getLobbyView() const;
};


#endif //POKERGAME_LOBBY_H
