//
// Created by Jakub Dębski on 18.02.18.
//

#include "Deck.h"


Deck::Deck()
{
    CardSuit suit;
    CardValue value;

    for (int s=0; s<=3; s++) {
        suit = static_cast<CardSuit>(s);

        for (int v=2; v<=14; v++) {
            value = static_cast<CardValue>(v);

            Card card(value, suit);
            this->cards.insert(this->cards.begin(), card);
        }
    }
}

void Deck::shuffle()
{

}

Card Deck::getCardFromTop()
{

}