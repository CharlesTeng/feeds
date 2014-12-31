cmake_minimum_required(VERSION 2.6)

PROJECT(schd C)

INCLUDE(CheckFunctionExists)

ADD_DEFINITIONS(-Os -Wall -Werror --std=gnu99 -g3 -Wmissing-declarations)

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

ADD_EXECUTABLE(schd ubus.c schd.c signal.c service.c)
TARGET_LINK_LIBRARIES(schd ubox ubus uci)

INSTALL(TARGETS schd RUNTIME DESTINATION sbin)
