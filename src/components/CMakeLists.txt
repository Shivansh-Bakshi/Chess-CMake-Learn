add_library(pieces pieces.cpp)

add_library(board board.cpp)

target_link_libraries(board pieces)