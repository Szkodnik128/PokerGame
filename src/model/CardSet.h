//
// Created by Jakub Dębski on 27.05.18.
//

#ifndef POKERGAME_CARDSET_H
#define POKERGAME_CARDSET_H

#include "Card.h"

#include <list>

enum CardSetCategory {
    HIGH_CARD = 1,
    PAIR = 2,
    TWO_PAIRS = 3,
    THREE_OF_A_KIND = 4,
    STRAIGHT = 5,
    FLUSH = 6,
    FULL_HOUSE = 7,
    FOUR_OF_A_KIND = 8,
    STRAIGHT_FLUSH = 9
};

class CardSet {

private:
    CardSetCategory cardSetCategory;
    std::list <Card *> cards;

public:
    CardSetCategory getCardSetCategory() const;
    const std::list<Card *> &getCards() const;
    void setCardSetCategory(CardSetCategory cardSetCategory);
    void addCard(Card *card);
    void removeCard(Card *card);
    void removeLastCard();
    void sortCards();
};


#endif //POKERGAME_CARDSET_H
