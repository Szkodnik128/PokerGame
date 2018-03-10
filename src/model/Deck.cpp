//
// Created by Jakub Dębski on 18.02.18.
//

#include "Deck.h"


Deck::Deck()
{
    Card *card;
    CardSuit suit;
    CardValue value;

    for (int s=0; s<=3; s++) {
        suit = static_cast<CardSuit>(s);

        for (int v=2; v<=14; v++) {
            value = static_cast<CardValue>(v);

            card = new Card(value, suit);
            this->cards.push_front(card);
        }
    }
}

void Deck::shuffle()
{

}

Card Deck::getCardFromTop()
{
    Card *card;

    /* Check if deck is not empty */
    if (this->cards.empty()) {
        // TODO: Throw exception
    }

    /* Take card's pointer from list */
    card = *this->cards.begin();
    /* Remove card's from list */
    this->cards.pop_front();
    /* Add card to taken list */
    this->taken.push_front(card);

    return *card;
}

size_t Deck::getDeckSize()
{
    return this->cards.size();
}