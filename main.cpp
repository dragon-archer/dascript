/* SPDX-License-Identifier: MIT */
/**
 * @file      main.cpp
 * @brief     Entry point for dascript
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#include "config.hpp"
#include "init.hpp"
#include "log.hpp"
using namespace DA_SCRIPT;

void mock() {
	/*
		Mock for:
		value = {
			add = 5
			add = 6
		}
	*/
	auto v = std::make_shared<compound_number>();
	v->get_compound().emplace_back(std::make_shared<statement>(
		get_global_object(da::hash("add")),
		std::make_shared<plain_number>(5)));
	v->get_compound().emplace_back(std::make_shared<statement>(
		get_global_object(da::hash("add")),
		std::make_shared<plain_number>(6)));
	log_debug("{}", v->get_value());
}

int main() {
	log_info("dascript start");
	init_plain_functions();
	mock();
	log_info("dascript exit");
	return 0;
}
