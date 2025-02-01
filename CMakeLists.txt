cmake_minimum_required(VERSION 3.10)

project(Kuripawarudo)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

set(SOURCE_DIR Kuripawarudo_Linux/sources)
set(SOURCE_ENTITEES_DIR Kuripawarudo_Linux/sources/entitee)
set(INCLUDE_DIR Kuripawarudo_Linux/headers)
set(INCLUDE_ENTITEES_DIR Kuripawarudo_Linux/headers/entitee)

include_directories(${INCLUDE_DIR})
include_directories(${INCLUDE_ENTITEES_DIR})

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
file(GLOB SOURCES_ENTITEES ${SOURCE_ENTITEES_DIR}/*.cpp)

set(SOURCES ${SOURCES} ${SOURCES_ENTITEES})

# Rechercher Boost
find_package(Boost REQUIRED COMPONENTS log log_setup)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(Kuripawarudo-v0-3-7 ${SOURCES})
    target_link_libraries(Kuripawarudo-v0-3-7 ${Boost_LIBRARIES} Boost::log Boost::log_setup)
else()
    message(FATAL_ERROR "Boost not found")
endif()

# change executable path to root directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})