add_library(game game.cpp)

list(APPEND GAME_LINK_LIBS pieces)
list(APPEND GAME_LINK_LIBS board)

list(APPEND GAME_LINK_INCLUDES "${CMAKE_SOURCE_DIR}/src/components")

include_directories(${GAME_LINK_INCLUDES})
link_directories(${GAME_LINK_INCLUDES})

target_link_libraries(game ${GAME_LINK_LIBS})