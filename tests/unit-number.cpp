/* SPDX-License-Identifier: MIT */
/**
 * @file      unit-number.cpp
 * @brief     Unit test for module number
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#include <doctest/doctest.h>
#include <init.hpp>

TEST_CASE("number") {
	using namespace DA_SCRIPT;

	log_begin_test();
	init_plain_functions();

	SUBCASE("add") {
		auto v = std::make_shared<compound_number>();
		v->get_compound().emplace_back(std::make_shared<statement>(
			get_global_object(da::hash("add")),
			std::make_shared<plain_number>(5)));
		CHECK_EQ(v->get_value(), 5);
	}

	log_end();
}
