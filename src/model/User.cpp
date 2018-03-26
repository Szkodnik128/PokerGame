//
// Created by kuba on 26.03.18.
//

#include "User.h"

User::User(const std::string &name) : name(name) {}

const std::string &User::getName() const {
    return name;
}
