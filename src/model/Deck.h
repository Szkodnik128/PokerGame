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
    std::list<Card> cards;
    /** Taken cards from deck */
    std::list<Card> taken;

public:
    Deck();

    void shuffle();
    Card getCardFromTop();


};


#endif //POKERGAME_DECK_H
