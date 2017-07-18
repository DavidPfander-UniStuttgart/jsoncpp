cmake_minimum_required(VERSION 3.2)

project(jsoncpp)

# find_package(PkgConfig REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wno-unused-parameter ${CMAKE_CXX_FLAGS}")

include_directories(src/)

set(SOURCES_JSONCPP "src/DictNode.cpp" "src/IDNode.cpp" "src/JSON.cpp" "src/json_exception.cpp" "src/ListNode.cpp" "src/Node.cpp" "src/TextNode.cpp")

set(HEADERS_JSONCPP "src/DictNode.hpp" "src/IDNode.hpp" "src/JSON.hpp" "src/json_exception.hpp" "src/ListNode.hpp" "src/Node.hpp" "src/TextNode.hpp" "src/Token.hpp")

add_library(jsoncpp SHARED ${SOURCES_JSONCPP})
add_library(jsoncpp_static STATIC ${SOURCES_JSONCPP})

install(TARGETS jsoncpp DESTINATION lib)
install(TARGETS jsoncpp_static DESTINATION lib)
install(FILES ${HEADERS_JSONCPP} DESTINATION include)
