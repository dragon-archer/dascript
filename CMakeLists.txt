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

option(dascript_BuildTests   "Build unit tests"                  ${MAIN_PROJECT})
option(dascript_UseBundledDa "Use bundled da"                    OFF)
option(dascript_UseStdFormat "Use std::format instead of fmtlib" OFF)

set(TARGET_NAME ${PROJECT_NAME})

if(dascript_UseBundledDa)
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
if(dascript_UseStdFormat)
	target_compile_definitions(${TARGET_NAME} PRIVATE DASCRIPT_USE_STD_FORMAT)
endif()

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
