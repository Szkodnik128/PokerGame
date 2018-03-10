//
// Created by Jakub Dębski on 18.02.18.
//

#ifndef POKERGAME_TABLE_H
#define POKERGAME_TABLE_H


#include "Deck.h"
#include "Pot.h"

class Table {

private:
    Deck deck;
    Pot pot;

public:
    Table();
};


#endif //POKERGAME_TABLE_H
