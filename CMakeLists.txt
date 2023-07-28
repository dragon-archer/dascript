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

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Detect whether it is built as a subproject or a main project
set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(MAIN_PROJECT ON)
endif()

option(dascript_BuildTests "Build unit tests" ${MAIN_PROJECT})

if(USE_CCACHE)
	find_program(CCACHE_FOUND ccache)
	if(CCACHE_FOUND)
		set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
		set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
	endif()
endif()

set(TARGET_NAME ${PROJECT_NAME})

if(WITH_DA_SUBMODULE)
	add_subdirectory(${PROJECT_SOURCE_DIR}/da)
else()
	find_package(da REQUIRED)
endif()

find_package(spdlog REQUIRED)

file(GLOB SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
)

set(PCH src/pch.hpp)

set(LIBS
	da::da
	spdlog::spdlog
)

add_executable(${TARGET_NAME} ${SRCS})
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
target_precompile_headers(${TARGET_NAME} PRIVATE ${PCH})
target_link_libraries(${TARGET_NAME} PRIVATE ${LIBS})

# Tests
if(dascript_BuildTests)
	set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1) # Forbid CTest to add targets
	include(CTest)
	enable_testing()
	add_subdirectory(tests)
endif()

if(dascript_Coverage)
	include(coverage)
endif()
