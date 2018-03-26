//
// Created by kuba on 26.03.18.
//

#ifndef POKERGAME_USER_H
#define POKERGAME_USER_H

#include <string>

class User {

private:
    std::string name;

public:
    User(const std::string &name);
    const std::string &getName() const;
};


#endif //POKERGAME_USER_H
