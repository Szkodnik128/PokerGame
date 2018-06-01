//
// Created by Jakub Dębski on 27.05.18.
//

#include "CardSet.h"

bool cardSortDescending(const Card *first, const Card *second)
{
    return first >= second;
}

CardSetCategory CardSet::getCardSetCategory() const
{
    return cardSetCategory;
}

const std::list<Card *> &CardSet::getCards() const
{
    return cards;
}

void CardSet::setCardSetCategory(CardSetCategory cardSetCategory)
{
    CardSet::cardSetCategory = cardSetCategory;
}

void CardSet::sortCards()
{
    this->cards.sort(cardSortDescending);
}

void CardSet::addCard(Card *card)
{
    this->cards.push_front(card);
}

void CardSet::removeCard(Card *card)
{
    for (auto const_iterator = this->cards.begin(); const_iterator != this->cards.end(); ++const_iterator) {
        if (*const_iterator == card) {
            this->cards.erase(const_iterator);
            break;
        }
    }
}

void CardSet::removeLastCard()
{
    this->cards.pop_back();
}

Card *CardSet::getFirstPairCard() const {
    return firstPairCard;
}

Card *CardSet::getSecondPairCard() const {
    return secondPairCard;
}

Card *CardSet::getThreeOfAKindCard() const {
    return threeOfAKindCard;
}

Card *CardSet::getFourOfAKindCard() const {
    return fourOfAKindCard;
}

void CardSet::setFirstPairCard(Card *firstPairCard) {
    CardSet::firstPairCard = firstPairCard;
}

void CardSet::setSecondPairCard(Card *secondPairCard) {
    CardSet::secondPairCard = secondPairCard;
}

void CardSet::setThreeOfAKindCard(Card *threeOfAKindCard) {
    CardSet::threeOfAKindCard = threeOfAKindCard;
}

void CardSet::setFourOfAKindCard(Card *fourOfAKindCard) {
    CardSet::fourOfAKindCard = fourOfAKindCard;
}

bool CardSet::operator==(const CardSet &cardSet) const
{
    std::list<Card *>::const_iterator it1;
    std::list<Card *>::const_iterator it2;

    if (this->cardSetCategory != cardSet.cardSetCategory) {
        return this->cardSetCategory == cardSet.cardSetCategory;
    }

    switch (cardSet.cardSetCategory) {
        case PAIR:
            if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard == cardSet.firstPairCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 == *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case TWO_PAIRS:
            if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard == cardSet.firstPairCard;
            } else if (this->secondPairCard != cardSet.secondPairCard) {
                return this->secondPairCard == cardSet.secondPairCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 == *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case THREE_OF_A_KIND:
            if (this->threeOfAKindCard != cardSet.threeOfAKindCard) {
                return this->threeOfAKindCard == cardSet.threeOfAKindCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 == *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case FOUR_OF_A_KIND:
            if (this->fourOfAKindCard != cardSet.fourOfAKindCard) {
                return this->fourOfAKindCard == cardSet.fourOfAKindCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 == *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case FULL_HOUSE:
            if (this->threeOfAKindCard != cardSet.threeOfAKindCard) {
                return this->threeOfAKindCard == cardSet.threeOfAKindCard;
            } else if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard == cardSet.firstPairCard;
            }

            return true;
        default:
            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 == *it2;
                }


                it1++;
                it2++;
            }

            return true;
    }
}

bool CardSet::operator<(const CardSet &cardSet) const
{
    std::list<Card *>::const_iterator it1;
    std::list<Card *>::const_iterator it2;

    if (this->cardSetCategory != cardSet.cardSetCategory) {
        return this->cardSetCategory < cardSet.cardSetCategory;
    }

    switch (cardSet.cardSetCategory) {
        case PAIR:
            if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard < cardSet.firstPairCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 < *it2;
                }


                it1++;
                it2++;
            }

            return false;
        case TWO_PAIRS:
            if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard < cardSet.firstPairCard;
            } else if (this->secondPairCard != cardSet.secondPairCard) {
                return this->secondPairCard < cardSet.secondPairCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 < *it2;
                }


                it1++;
                it2++;
            }

            return false;
        case THREE_OF_A_KIND:
            if (this->threeOfAKindCard != cardSet.threeOfAKindCard) {
                return this->threeOfAKindCard < cardSet.threeOfAKindCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 < *it2;
                }


                it1++;
                it2++;
            }

            return false;
        case FOUR_OF_A_KIND:
            if (this->fourOfAKindCard != cardSet.fourOfAKindCard) {
                return this->fourOfAKindCard < cardSet.fourOfAKindCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 < *it2;
                }


                it1++;
                it2++;
            }

            return false;
        case FULL_HOUSE:
            if (this->threeOfAKindCard != cardSet.threeOfAKindCard) {
                return this->threeOfAKindCard < cardSet.threeOfAKindCard;
            } else if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard < cardSet.firstPairCard;
            }

            return false;
        default:
            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 < *it2;
                }


                it1++;
                it2++;
            }

            return false;
    }
}

bool CardSet::operator>(const CardSet &cardSet) const
{
    std::list<Card *>::const_iterator it1;
    std::list<Card *>::const_iterator it2;

    if (this->cardSetCategory != cardSet.cardSetCategory) {
        return this->cardSetCategory > cardSet.cardSetCategory;
    }

    switch (cardSet.cardSetCategory) {
        case PAIR:
            if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard > cardSet.firstPairCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 > *it2;
                }


                it1++;
                it2++;
            }

            return false;
        case TWO_PAIRS:
            if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard > cardSet.firstPairCard;
            } else if (this->secondPairCard != cardSet.secondPairCard) {
                return this->secondPairCard > cardSet.secondPairCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 > *it2;
                }


                it1++;
                it2++;
            }

            return false;
        case THREE_OF_A_KIND:
            if (this->threeOfAKindCard != cardSet.threeOfAKindCard) {
                return this->threeOfAKindCard > cardSet.threeOfAKindCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 > *it2;
                }


                it1++;
                it2++;
            }

            return false;
        case FOUR_OF_A_KIND:
            if (this->fourOfAKindCard != cardSet.fourOfAKindCard) {
                return this->fourOfAKindCard > cardSet.fourOfAKindCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 > *it2;
                }


                it1++;
                it2++;
            }

            return false;
        case FULL_HOUSE:
            if (this->threeOfAKindCard != cardSet.threeOfAKindCard) {
                return this->threeOfAKindCard > cardSet.threeOfAKindCard;
            } else if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard > cardSet.firstPairCard;
            }

            return true;
        default:
            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 > *it2;
                }


                it1++;
                it2++;
            }

            return false;
    }
}

bool CardSet::operator<=(const CardSet &cardSet) const
{
    std::list<Card *>::const_iterator it1;
    std::list<Card *>::const_iterator it2;

    if (this->cardSetCategory != cardSet.cardSetCategory) {
        return this->cardSetCategory <= cardSet.cardSetCategory;
    }

    switch (cardSet.cardSetCategory) {
        case PAIR:
            if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard <= cardSet.firstPairCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 <= *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case TWO_PAIRS:
            if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard <= cardSet.firstPairCard;
            } else if (this->secondPairCard != cardSet.secondPairCard) {
                return this->secondPairCard <= cardSet.secondPairCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 <= *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case THREE_OF_A_KIND:
            if (this->threeOfAKindCard != cardSet.threeOfAKindCard) {
                return this->threeOfAKindCard <= cardSet.threeOfAKindCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 <= *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case FOUR_OF_A_KIND:
            if (this->fourOfAKindCard != cardSet.fourOfAKindCard) {
                return this->fourOfAKindCard <= cardSet.fourOfAKindCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 <= *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case FULL_HOUSE:
            if (this->threeOfAKindCard != cardSet.threeOfAKindCard) {
                return this->threeOfAKindCard <= cardSet.threeOfAKindCard;
            } else if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard <= cardSet.firstPairCard;
            }

            return true;
        default:
            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 <= *it2;
                }


                it1++;
                it2++;
            }

            return true;
    }
}

bool CardSet::operator>=(const CardSet &cardSet) const
{
    std::list<Card *>::const_iterator it1;
    std::list<Card *>::const_iterator it2;

    if (this->cardSetCategory != cardSet.cardSetCategory) {
        return this->cardSetCategory <= cardSet.cardSetCategory;
    }

    switch (cardSet.cardSetCategory) {
        case PAIR:
            if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard >= cardSet.firstPairCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 >= *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case TWO_PAIRS:
            if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard >= cardSet.firstPairCard;
            } else if (this->secondPairCard != cardSet.secondPairCard) {
                return this->secondPairCard >= cardSet.secondPairCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 >= *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case THREE_OF_A_KIND:
            if (this->threeOfAKindCard != cardSet.threeOfAKindCard) {
                return this->threeOfAKindCard >= cardSet.threeOfAKindCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 >= *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case FOUR_OF_A_KIND:
            if (this->fourOfAKindCard != cardSet.fourOfAKindCard) {
                return this->fourOfAKindCard >= cardSet.fourOfAKindCard;
            }

            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 >= *it2;
                }


                it1++;
                it2++;
            }

            return true;
        case FULL_HOUSE:
            if (this->threeOfAKindCard != cardSet.threeOfAKindCard) {
                return this->threeOfAKindCard >= cardSet.threeOfAKindCard;
            } else if (this->firstPairCard != cardSet.firstPairCard) {
                return this->firstPairCard >= cardSet.firstPairCard;
            }

            return true;
        default:
            it1 = this->cards.begin();
            it2 = cardSet.cards.begin();

            while (it1 != this->cards.end()) {
                if (*it1 != *it2) {
                    return *it1 >= *it2;
                }


                it1++;
                it2++;
            }

            return true;
    }
}
