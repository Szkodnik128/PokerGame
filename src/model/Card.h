//
// Created by Jakub Dębski on 18.02.18.
//

#ifndef POKERGAME_CARD_H
#define POKERGAME_CARD_H

/**
 * Card values.
 */
enum CardValue {
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14,
};

/**
 * Card suits.
 */
enum CardSuit {
    SPADES = 1,
    HEARTS,
    DIAMONDS,
    CLUBS
};

/**
 * Card class.
 */
class Card {

private:
    /** Card's value. */
    const CardValue cardValue;
    /** Card's suit. */
    const CardSuit cardSuit;

public:
    /**
     * Constructor.
     *
     * @param cardValue     card's value
     * @param cardSuit      card's suit
     */
    Card(const CardValue cardValue, const CardSuit cardSuit);

    /**
     * Returns card's value.
     *
     * @return card's value
     */
    CardValue getCardValue();

    /**
     * Returns card's suit.
     *
     * @return card's suit
     */
    CardSuit getCardSuit();

    /**
     * Overloads '==' operator.
     *
     * @param card          card
     * @return true if equal to card
     */
    bool operator==(const Card &card) const;

    /**
     * Overloads '<' operator.
     *
     * @param card          card
     * @return true if lesser than card
     */
    bool operator<(const Card &card) const;

    /**
     * Overloads '>' operator.
     *
     * @param card          card
     * @return true if greater than card
     */
    bool operator>(const Card &card) const;

    /**
     * Overloads '<=' operator.
     *
     * @param card          card
     * @return true if lesser or equal to card
     */
    bool operator<=(const Card &card) const;

    /**
     * Overloads '>=' operator.
     *
     * @param card          card
     * @return true if greater or equal to card
     */
    bool operator>=(const Card &card) const;

    /**
     * Overloads '!=' operator.
     *
     * @param card          card
     * @return true if greater or equal to card
     */
    bool operator!=(const Card &card) const;
};


#endif //POKERGAME_CARD_H
