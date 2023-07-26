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

	SUBCASE("value") {
		auto v = std::make_shared<compound_number>();
		v->get_compound().emplace_back(std::make_shared<statement>(
			get_global_object(da::hash("value")),
			std::make_shared<plain_number>(4)));
		CHECK_EQ(v->get_value(), 4);
	}

	SUBCASE("add") {
		auto v = std::make_shared<compound_number>();
		v->get_compound().emplace_back(std::make_shared<statement>(
			get_global_object(da::hash("add")),
			std::make_shared<plain_number>(5)));
		CHECK_EQ(v->get_value(), 5);
	}

	SUBCASE("subtract") {
		auto v = std::make_shared<compound_number>();
		v->get_compound().emplace_back(std::make_shared<statement>(
			get_global_object(da::hash("subtract")),
			std::make_shared<plain_number>(6)));
		CHECK_EQ(v->get_value(), -6);
	}

	SUBCASE("mix") {
		auto v = std::make_shared<compound_number>();
		v->get_compound().emplace_back(std::make_shared<statement>(
			get_global_object(da::hash("value")),
			std::make_shared<plain_number>(1)));
		v->get_compound().emplace_back(std::make_shared<statement>(
			get_global_object(da::hash("add")),
			std::make_shared<plain_number>(2)));
		v->get_compound().emplace_back(std::make_shared<statement>(
			get_global_object(da::hash("subtract")),
			std::make_shared<plain_number>(4)));
		v->get_compound().emplace_back(std::make_shared<statement>(
			get_global_object(da::hash("max")),
			std::make_shared<plain_number>(-2)));
		v->get_compound().emplace_back(std::make_shared<statement>(
			get_global_object(da::hash("multiply")),
			std::make_shared<plain_number>(5)));
		v->get_compound().emplace_back(std::make_shared<statement>(
			get_global_object(da::hash("min")),
			std::make_shared<plain_number>(-8)));
		v->get_compound().emplace_back(std::make_shared<statement>(
			get_global_object(da::hash("divide")),
			std::make_shared<plain_number>(3)));
		CHECK_EQ(v->get_value(), -2);
	}
}
