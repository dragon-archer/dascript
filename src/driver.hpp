/* SPDX-License-Identifier: MIT */
/**
 * @file      driver.hpp
 * @brief     driver for flex and bison
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2025 dragon-archer
 */

#ifndef _DA_SCRIPT_DRIVER_HPP_
#define _DA_SCRIPT_DRIVER_HPP_

#include "config.hpp"
#include "lexer.hpp"
#include "log.hpp"
#include "parser.hpp"

DA_BEGIN_SCANNER

class driver {
	private:
	parser _parser;
	lexer  _lexer;

	public:
	driver()
		: _lexer(*this)
		, _parser(_lexer, *this) {
	}

	int parse() {
		_lexer.switch_streams(std::cin, std::cout);
		_parser.set_debug_stream(std::cerr);
		_parser.set_debug_level(0);
		try {
			return _parser.parse();
		} catch(const std::exception& e) {
			log_error({"driver panicked at {}"}, e.what());
			return 1;
		}
	}

	virtual ~driver() { }
};

DA_END_SCANNER

#endif // _DA_SCRIPT_DRIVER_HPP_