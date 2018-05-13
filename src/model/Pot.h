//
// Created by Jakub Dębski on 18.02.18.
//

#ifndef POKERGAME_POT_H
#define POKERGAME_POT_H


class Pot {
private:
    unsigned int chips;

public:
    /**
     * Pot constructor
     */
    Pot();

    /**
     * Returns pot's chips;
     * @return pot's chips
     */
    unsigned int getChips() const;

    /**
     * Adds chips to pot.
     *
     * @param chips         chips to add
     */
    void addChips(unsigned int chips);

    /**
     * Zeros chips in pot.
     */
    void zeroChips();

};


#endif //POKERGAME_POT_H
