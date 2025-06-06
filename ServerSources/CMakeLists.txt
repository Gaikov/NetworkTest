project(ServerApp)

set(sources
        main.cpp
        ServerTestApp.cpp
        ServerTestApp.h
        TestServer.cpp
        TestServer.h
)

include_directories(./)

add_executable(ServerApp ${sources})
target_link_libraries(ServerApp ${GROM_ENGINE_LIBS} Networking)
