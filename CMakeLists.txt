cmake_minimum_required(VERSION 3.9)
project(PokerGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(PokerGame
        src/main.cpp
        src/model/Card.cpp src/model/Card.h
        src/model/Deck.cpp src/model/Deck.h
        src/model/Pot.cpp src/model/Pot.h
        src/model/Table.cpp src/model/Table.h
        src/model/Player.cpp src/model/Player.h
        src/server/Server.cpp src/server/Server.h)