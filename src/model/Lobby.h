//
// Created by kuba on 20.03.18.
//

#ifndef POKERGAME_LOBBY_H
#define POKERGAME_LOBBY_H

#include "Player.h"

class Lobby {
    
private:
    std::list<Player *>players;

public:
    void addPlayer(Player *const player);
    void removePlayer(Player *const player);
    bool isPlayer(Player *const player);
};


#endif //POKERGAME_LOBBY_H
