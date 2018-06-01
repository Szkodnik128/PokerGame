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

    Card *firstPairCard;
    Card *secondPairCard;
    Card *threeOfAKindCard;
    Card *fourOfAKindCard;

public:
    CardSetCategory getCardSetCategory() const;
    const std::list<Card *> &getCards() const;
    void setCardSetCategory(CardSetCategory cardSetCategory);
    void addCard(Card *card);
    void removeCard(Card *card);
    void removeLastCard();
    void sortCards();
    Card *getFirstPairCard() const;
    Card *getSecondPairCard() const;
    Card *getThreeOfAKindCard() const;
    Card *getFourOfAKindCard() const;
    void setFirstPairCard(Card *firstPairCard);
    void setSecondPairCard(Card *secondPairCard);
    void setThreeOfAKindCard(Card *threeOfAKindCard);
    void setFourOfAKindCard(Card *fourOfAKindCard);

    /**
 * Overloads '==' operator.
 *
 * @param card          card
 * @return true if equal to card
 */
    bool operator==(const CardSet &cardSet) const;

    /**
     * Overloads '<' operator.
     *
     * @param card          card
     * @return true if lesser than card
     */
    bool operator<(const CardSet &cardSet) const;

    /**
     * Overloads '>' operator.
     *
     * @param card          card
     * @return true if greater than card
     */
    bool operator>(const CardSet &cardSet) const;

    /**
     * Overloads '<=' operator.
     *
     * @param card          card
     * @return true if lesser or equal to card
     */
    bool operator<=(const CardSet &cardSet) const;

    /**
     * Overloads '>=' operator.
     *
     * @param card          card
     * @return true if greater or equal to card
     */
    bool operator>=(const CardSet &cardSet) const;
};


#endif //POKERGAME_CARDSET_H
