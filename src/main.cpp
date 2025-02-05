/* SPDX-License-Identifier: MIT */
/**
 * @file      main.cpp
 * @brief     Entry point for dascript
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023-2025 dragon-archer
 */

#include "config.hpp"
#include "driver.hpp"
#include "init.hpp"
#include "log.hpp"

using namespace DA_SCRIPT;

int main(int argc, char const* argv[]) {
	log_begin();
	log_info({"Build with __cplusplus = {}"}, __cplusplus);
	scanner::driver d;
	d.parse();
	log_end();
	return 0;
}
