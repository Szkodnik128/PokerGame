//
// Created by Jakub Dębski on 18.02.18.
//

#include "Pot.h"


Pot::Pot()
{
    this->chips = 0;
}

unsigned int Pot::getChips() const
{
    return this->chips;
}

void Pot::addChips(unsigned int chips)
{
    this->chips += chips;
}

void Pot::zeroChips()
{
    this->chips = 0;
}
