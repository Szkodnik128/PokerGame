//
// Created by kuba on 20.03.18.
//

#ifndef POKERGAME_LOBBY_H
#define POKERGAME_LOBBY_H

#include "Player.h"

class Lobby {

private:
    std::list<Table *>tables;

public:
    const std::list<Table *> &getTables() const;
    void createTable(); /* TODO: Add more arguments */
    void addPlayerToTable(int tableId, Player *const player);
    void removePlayerFromTable(int tableId, Player *const player);

};


#endif //POKERGAME_LOBBY_H
