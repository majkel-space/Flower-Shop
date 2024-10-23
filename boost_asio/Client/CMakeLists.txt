cmake_minimum_required(VERSION 3.10)

project(ClientApp)

add_executable(client.o
    client.cpp
    main.cpp
)

target_include_directories(client.o PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(client.o PRIVATE -pthread)
