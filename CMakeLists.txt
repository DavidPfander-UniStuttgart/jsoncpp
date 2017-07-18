cmake_minimum_required(VERSION 3.2)

project(jsoncpp)

# find_package(PkgConfig REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wno-unused-parameter ${CMAKE_CXX_FLAGS}")

include_directories(src/)

set(SOURCES_JSONCPP "src/dict_node.cpp" "src/id_node.cpp" "src/json.cpp" "src/json_exception.cpp" "src/list_node.cpp" "src/node.cpp" "src/text_node.cpp")

set(HEADERS_JSONCPP "src/dict_node.hpp" "src/id_node.hpp" "src/json.hpp" "src/json_exception.hpp" "src/list_node.hpp" "src/node.hpp" "src/text_node.hpp" "src/token.hpp")

add_library(jsoncpp SHARED ${SOURCES_JSONCPP})
add_library(jsoncpp_static STATIC ${SOURCES_JSONCPP})

install(TARGETS jsoncpp DESTINATION lib)
install(TARGETS jsoncpp_static DESTINATION lib)
install(FILES ${HEADERS_JSONCPP} DESTINATION include)
