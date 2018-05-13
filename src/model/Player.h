//
// Created by Jakub Dębski on 18.02.18.
//

#ifndef POKERGAME_PLAYER_H
#define POKERGAME_PLAYER_H

#include "Card.h"

#include <string>
#include <tuple>

class Player {

private:
    /** Player's name */
    std::string name;
    /** Connected flag */
    bool connected;
    /** Player's chips */
    unsigned int chips;
    /** Playing flag */
    bool playing;
    /** In the table flag */
    bool inTable;
    /** In game - player didn't fold yet */
    bool inGame;
    /** Turn flag */
    bool turn;
    /** Player's hand */
    std::tuple<Card *, Card *> hand;
    /** Player's bet */
    unsigned int bet;

public:

    /**
     * Player's constructor
     *
     * @param name      player's name
     */
    Player(const std::string &name);

    /**
     * Returns player's name
     *
     * @return player's name
     */
    const std::string &getName() const;

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

    bool isConnected() const;
    void setConnected(bool connected);
    bool isPlaying() const;
    void setPlaying(bool playing);
    bool isInTable() const;
    void setInTable(bool inTable);
    const std::tuple<Card *, Card *> &getHand() const;
    void setHand(const std::tuple<Card *, Card *> &hand);
    bool isInGame() const;
    void setInGame(bool inGame);
    bool isTurn() const;
    void setTurn(bool turn);
    unsigned int getBet() const;
    void setBet(unsigned int bet);
};

#endif //POKERGAME_PLAYER_H
