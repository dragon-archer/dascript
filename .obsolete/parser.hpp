/* SPDX-License-Identifier: MIT */
/**
 * @file      parser.hpp
 * @brief     Script parser
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_PARSER_HPP_
#define _DA_SCRIPT_PARSER_HPP_

#include "config.hpp"
#include "lexer.hpp"
#include "object.hpp"

DA_BEGIN_SCRIPT

class parser {
	public:
	using string_t = lexer::string_t;

	private:
	enum class state {
		start,
		want_operator,
		want_rhs
	};

	lexer    _lexer;
	state    _state{start};

	public:
	constexpr parser(string_t content, string_t filename = ""sv) noexcept
		: _lexer(content, filename) { }
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_PARSER_HPP_
