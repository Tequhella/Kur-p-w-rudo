cmake_minimum_required(VERSION 3.12)
project(kuripawarudo)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

# required!
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_LINK_COMMANDS ON)

set(SOURCES
    Kuripawarudo_Linux/sources/main.cpp
    Kuripawarudo_Linux/sources/carte.cpp
    Kuripawarudo_Linux/sources/case.cpp
    Kuripawarudo_Linux/sources/block.cpp
    Kuripawarudo_Linux/sources/entitee.cpp
    Kuripawarudo_Linux/sources/vide.cpp
    Kuripawarudo_Linux/sources/curseur.cpp
    Kuripawarudo_Linux/sources/entitee/vaisseau.cpp
    Kuripawarudo_Linux/sources/entitee/reacteur.cpp
    Kuripawarudo_Linux/sources/entitee/mineur.cpp
    Kuripawarudo_Linux/sources/entitee/bouclier.cpp
    Kuripawarudo_Linux/sources/entitee/phare.cpp
    Kuripawarudo_Linux/sources/entitee/bombe.cpp
    Kuripawarudo_Linux/sources/entitee/creeperEmetteur.cpp
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Kuripawarudo_Linux/build/obj)

add_executable(kuripawarudo-v0-3-7-CPP ${SOURCES})

target_include_directories(kuripawarudo-v0-3-7-CPP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Kuripawarudo_Linux/headers)

target_compile_options(kuripawarudo-v0-3-7-CPP PRIVATE -g -Wall -Wextra -Werror)
