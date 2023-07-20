###
# @file      CMakeLists.txt
# @brief     CMake source file
# @version   0.1
# @author    dragon-archer
#
# @copyright Copyright (c) 2023 dragon-archer
#

cmake_minimum_required(VERSION 3.16)
project(dascript VERSION 0.1 LANGUAGES CXX)

set(TARGET_NAME ${PROJECT_NAME})

find_package(da REQUIRED)
find_package(spdlog REQUIRED)

file(GLOB SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

set(PCH pch.hpp)

set(LIBS
	da::da
	spdlog::spdlog
)

add_executable(${TARGET_NAME} ${SRCS})
target_precompile_headers(${TARGET_NAME} PRIVATE ${PCH})
target_link_libraries(${TARGET_NAME} PRIVATE ${LIBS})
