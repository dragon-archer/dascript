/* SPDX-License-Identifier: MIT */
/**
 * @file      lexer.ll
 * @brief     flex input
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2025 dragon-archer
 */

%{ // for lexer.cpp

#include "config.hpp"
#include "parser.hpp"
#include "lexer.hpp" 
#include "location.hpp"

static DA_SCANNER::location loc;
#define YY_USER_ACTION loc.columns (yyleng);

using namespace DA_SCANNER;

%}

%option c++
%option noyywrap
%option yyclass="lexer"
%option prefix="da"
%option nounistd

str \"([^\\\"]|\\.)*\"
num [0-9]+(\.[0-9]*)?
id  [a-zA-Z_][a-zA-Z0-9_]*

%%
%{
	loc.step();
%}

[ \t]+  { loc.step(); }
\n      { loc.lines(1); loc.step(); }
#.*     { loc.step(); }

"="     { return parser::make_OP_EQ(loc); }
"!="    { return parser::make_OP_NE(loc); }
"<="    { return parser::make_OP_LE(loc); }
">="    { return parser::make_OP_GE(loc); }
"<"     { return parser::make_OP_LT(loc); }
">"     { return parser::make_OP_GT(loc); }
"?="    { return parser::make_OP_QE(loc); }
"{"     { return parser::make_LBRACE(loc); }
"}"     { return parser::make_RBRACE(loc); }
":"     { return parser::make_COLON(loc); }
"."     { return parser::make_DOT(loc); }
"yes"   { return parser::make_BOOLEAN(true, loc); }
"no"    { return parser::make_BOOLEAN(false, loc); }
{str}   { return parser::make_STRING({ yytext+1, static_cast<uint64_t>(yyleng-2) }, loc); }
{num}   { return parser::make_NUMBER(std::atof(yytext), loc); }
{id}    { return parser::make_IDENTIFIER(yytext, loc); }

<<EOF>> { return parser::make_YYEOF(loc); }
.       { return parser::make_YYerror(loc); }

%%
