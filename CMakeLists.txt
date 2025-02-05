###
# @file      CMakeLists.txt
# @brief     CMake source file
# @version   0.1
# @author    dragon-archer
#
# @copyright Copyright (c) 2023-2025 dragon-archer
#

cmake_minimum_required(VERSION 3.16)
project(dascript VERSION 0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Detect whether it is built as a subproject or a main project
set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(MAIN_PROJECT ON)
endif()

list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_23 dascript_HasCxx23)

option(dascript_BuildTests   "Build unit tests"                  ${MAIN_PROJECT})
option(dascript_UseBundledDa "Use bundled da"                    OFF)
option(dascript_UseCxx23     "Enable C++23"                      ${dascript_HasCxx23})
option(dascript_UseStdFormat "Use std::format instead of fmtlib" OFF)

set(TARGET_NAME ${PROJECT_NAME})

if(dascript_UseBundledDa)
	add_subdirectory(${PROJECT_SOURCE_DIR}/da)
else()
	find_package(da REQUIRED)
endif()

find_package(spdlog REQUIRED)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(nlohmann_json REQUIRED)

flex_target(lexer ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.ll ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
bison_target(parser ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp)
add_flex_bison_dependency(lexer parser)

file(GLOB SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
)

set(SRCS ${SRCS} ${FLEX_lexer_OUTPUTS} ${BISON_parser_OUTPUTS})

set(PCH src/pch.hpp)

set(LIBS
	da::da
	spdlog::spdlog
	nlohmann_json::nlohmann_json
)

add_executable(${TARGET_NAME} ${SRCS})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty) # Use bundled FlexLexer.h
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_precompile_headers(${TARGET_NAME} PRIVATE ${PCH})
target_link_libraries(${TARGET_NAME} PRIVATE ${LIBS})
# Fix __cplusplus for MSVC
target_compile_options(${TARGET_NAME} PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")

if(dascript_UseCxx23)
	if(NOT dascript_HasCxx23)
		message(FATAL_ERROR "dascript is configured to use C++23 but the compiler does not support C++23")
	else()
		target_compile_features(${TARGET_NAME} INTERFACE cxx_std_23)
	endif()
else()
	list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_20 dascript_HasCxx20)
	if(NOT dascript_HasCxx20)
		message(FATAL_ERROR "dascript should be compiled under at least C++20")
	endif()
	target_compile_features(${TARGET_NAME} INTERFACE cxx_std_20)
endif()

if(dascript_UseStdFormat)
	target_compile_definitions(${TARGET_NAME} PRIVATE DASCRIPT_USE_STD_FORMAT)
endif()

# Tests
if(dascript_BuildTests)
	enable_testing()
	add_subdirectory(tests)
endif()

if(dascript_Coverage)
	include(coverage)
endif()
