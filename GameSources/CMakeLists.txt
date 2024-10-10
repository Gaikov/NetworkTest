project(GameTemplate)

set(SRC
        GameApp.cpp
        GameAppInfo.cpp
)

if (ANDROID)
    add_library(GameTemplate STATIC ${sources} ${SRC})
else ()
    add_executable(GameTemplate ${sources} ${SRC})
endif ()

include_directories(./)

target_link_libraries(
        GameTemplate
        ${GROM_ENGINE_LIBS}
)