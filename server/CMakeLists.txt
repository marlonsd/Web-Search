cmake_minimum_required (VERSION 2.8.8)
project (Simple-Web-Server)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

include_directories(.)
include_directories(src/)
include_directories(src/utils)

file(GLOB SOURCESMODEL "src/*.cpp")
file(GLOB SOURCES "src/utils/*.cpp")

find_package(Threads REQUIRED)

find_package(Boost 1.54.0 COMPONENTS regex system thread filesystem date_time REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})



#TODO: add requirement for version 1.0.1g (can it be done in one line?)
find_package(OpenSSL)


add_executable(http_examples http_examples.cpp)
target_link_libraries(http_examples ${Boost_LIBRARIES})
target_link_libraries(http_examples ${SOURCES})
target_link_libraries(http_examples ${SOURCESMODEL})
target_link_libraries(http_examples ${CMAKE_THREAD_LIBS_INIT})

if(MSYS) #TODO: Is MSYS true when MSVC is true?
    target_link_libraries(http_examples ws2_32 wsock32)
endif()