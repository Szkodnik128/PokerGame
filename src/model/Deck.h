//
// Created by Jakub Dębski on 18.02.18.
//

#ifndef POKERGAME_DECK_H
#define POKERGAME_DECK_H

#include "Card.h"

#include <list>

class Deck {

private:
    /** Cards in deck */
    std::list<Card *> cards;
    /** Taken cards from deck */
    std::list<Card *> taken;

public:
    /**
     * Deck constructor.
     */
    Deck();

    /**
     * Shuffles deck.
     */
    void shuffle();

    /**
     * Pops card from deck's top.
     *
     * @return card
     */
    Card *getCardFromTop();

    /**
     * Returns deck's size.
     *
     * @return deck's size
     */
    size_t getDeckSize();
};


#endif //POKERGAME_DECK_H
