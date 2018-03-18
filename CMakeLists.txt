cmake_minimum_required(VERSION 3.9)
project(PokerGame)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES "src/*.cpp"
                       "src/controller/*.cpp" "src/controller/*.h"
                       "src/model/*.cpp" "src/model/*.h"
                       "src/protocol/*pb.cc" "src/protocol/*pb.h"
                       "src/server/*.cpp" "src/server/*.h"
                       "src/utils/*.cpp" "src/utils/*.h"
                       "src/event/*.cpp" "src/event/*.h")

add_executable(PokerGame ${SOURCE_FILES})

target_link_libraries(PokerGame pthread protobuf)
target_include_directories(PokerGame PUBLIC src)