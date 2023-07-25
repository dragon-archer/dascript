/* SPDX-License-Identifier: MIT */
/**
 * @file      unit.cpp
 * @brief     Entry point of all unit tests
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#define DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_NO_MULTITHREADING
#include <doctest/doctest.h>
#include <init.hpp>
using namespace DA_SCRIPT;

int main(int argc, char** argv) {
	log_begin_test();
	on_log_handler fail_on_error = []() {
		CHECK(("Error occurs, the test will fail.", false));
	};
	set_on_log_handler(spdlog::level::err, fail_on_error);
	set_on_log_handler(spdlog::level::critical, fail_on_error);
	init_plain_functions();

	int ret = doctest::Context(argc, argv).run();

	log_end();

	return ret;
}
