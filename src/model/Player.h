//
// Created by Jakub Dębski on 18.02.18.
//

#ifndef POKERGAME_PLAYER_H
#define POKERGAME_PLAYER_H

#include "Card.h"
#include "CardSet.h"

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
    /** Player's card set */
    CardSet cardSet;

public:

    /**
     * Player's constructor
     *
     * @param name      player's name
     */
    Player(const std::string &name);

    /* Getters and setters */
    const std::string &getName() const;
    void setChips(unsigned int chips);
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
    const CardSet &getCardSet() const;
    void setCardSet(const CardSet &cardSet);
};

#endif //POKERGAME_PLAYER_H
