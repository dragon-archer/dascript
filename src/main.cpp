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

int main() {
	log_info("dascript start");
	init_plain_functions();
	log_info("dascript exit");
	return 0;
}
