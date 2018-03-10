//
// Created by Jakub Dębski on 18.02.18.
//

#ifndef POKERGAME_PLAYER_H
#define POKERGAME_PLAYER_H

#include <tuple>
#include "Card.h"
#include "Table.h"

class Player {

private:
    /** Player's name */
    std::string name;
    /** Player's hand */
    std::tuple<Card, Card>hand;
    /** Player's chips */
    unsigned int chips;
    /** Table where player is playing */
    Table *table;

public:
    /**
     * Player constructor.
     *
     * @param name      player name
     */
    Player(std::string const &name);

    /**
     * Sets player's hand.
     *
     * @param hand      hand to set
     */
    void setHand(std::tuple<Card, Card>hand);

    /**
     * Returns player's hand.
     *
     * @return player's hand
     */
    std::tuple getHand();

    /**
     * Sets player's chips.
     *
     * @param chips player's chips
     */
    void setChips(unsigned int chips);

    /**
     * Returns player's chips.
     *
     * @return player's chips
     */
    unsigned int getChips();

    /**
     * Sets table.
     *
     * @param table     pointer to table
     */
    void setTable(Table *table);

    /**
     * Returns pointer to table.
     *
     * @return pointer to table
     */
    Table *getTable();
};

#endif //POKERGAME_PLAYER_H
