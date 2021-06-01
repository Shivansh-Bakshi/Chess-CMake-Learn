set(EXECUTABLE_NAME chess)

list(APPEND LINK_LIBS game)

list(APPEND LINK_INCLUDES "${CMAKE_SOURCE_DIR}/src/game")

include_directories(${LINK_INCLUDES})
link_directories(${LINK_INCLUDES})

add_executable(${EXECUTABLE_NAME} main.cpp)

target_link_libraries(${EXECUTABLE_NAME} ${LINK_LIBS})
