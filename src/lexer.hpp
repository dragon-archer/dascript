/* SPDX-License-Identifier: MIT */
/**
 * @file      lexer.hpp
 * @brief     Lexer for flex and bison
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2025 dragon-archer
 */

#ifndef _DA_SCRIPT_LEXER_HPP_
#define _DA_SCRIPT_LEXER_HPP_

#include "config.hpp"
#include "parser.hpp"

#if !defined(yyFlexLexerOnce)
	#undef yyFlexLexer
	#define yyFlexLexer daFlexLexer

	#include <FlexLexer.h>
#endif
#undef YY_DECL
#define YY_DECL parser::symbol_type lexer::next_token()

DA_BEGIN_SCANNER

class driver;

class lexer : public yyFlexLexer {
	private:
	driver& _driver;

	public:
	lexer(driver& d)
		: _driver(d) { }

	virtual parser::symbol_type next_token();

	virtual ~lexer() { }
};

DA_END_SCANNER

#endif // _DA_SCRIPT_LEXER_HPP_