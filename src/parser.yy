/* SPDX-License-Identifier: MIT */
/**
 * @file      parser.yy
 * @brief     bison input
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2025 dragon-archer
 */

%skeleton "lalr1.cc"

%require "3.7"

%define api.filename.type {std::string_view}
%define api.location.file "location.hpp"
%define api.namespace {da::script::scanner}
%define api.parser.class {parser}
%define api.token.constructor
%define api.token.prefix {TOKEN_}
%define api.value.type variant
%define parse.assert
%define parse.error detailed
%define parse.lac full
%define parse.trace

%locations

%code requires // for parser.hpp
{

#include "config.hpp"

DA_BEGIN_SCANNER

class lexer;
class driver;

using json = nlohmann::json;

enum class node_type : int {
	statements,
	list,
	compound,
	scope,
};

enum class op_type : int {
	eq,
	ne,
	lt,
	gt,
	le,
	ge,
	qe,
};

DA_END_SCANNER

}

%code top // for parser.cpp
{

#include "config.hpp"
#include "lexer.hpp"
#include "log.hpp"

DA_BEGIN_SCANNER

static parser::symbol_type yylex(lexer& l, driver& d) {
	return l.next_token();
}

DA_END_SCANNER

}

%lex-param { lexer& l }
%lex-param { driver& d }

%parse-param { lexer& l }
%parse-param { driver& d }

%token
	OP_EQ OP_NE OP_LT OP_GT OP_LE OP_GE OP_QE
	LBRACE RBRACE COLON DOT
;
%token <bool>        BOOLEAN
%token <double>      NUMBER
%token <std::string> IDENTIFIER STRING

%type <json> statements statement compound entity scope entity_list value list comparison_op plain_value block

%start document

%%

document:
	statements { log_info({"\n{}"}, $1.dump(4)); }
	;

statements:
	statement { $$ = { node_type::statements, $1 };}
	| statements statement { $$ = $1; $$.push_back($2); }
	;

statement:
	entity comparison_op value {
		$$ = { $1, $2, $3 };
	}
	| compound comparison_op value {
		$$ = { $1, $2, $3 };
	}
	;

comparison_op:
	OP_EQ	{ $$ = op_type::eq; }
	| OP_NE { $$ = op_type::ne; }
	| OP_LT { $$ = op_type::lt; }
	| OP_GT { $$ = op_type::gt; }
	| OP_LE { $$ = op_type::le; }
	| OP_GE { $$ = op_type::ge; }
	| OP_QE { $$ = op_type::qe; }
	;

compound: entity_list entity { $$ = $1; $$.push_back($2); $$[0] = node_type::compound; }
	;

entity_list:
	entity DOT               { $$[1] = $1; }
	| entity_list entity DOT { $$ = $1; $$.push_back($2); }
	;

entity:
	IDENTIFIER { $$ = $1; }
	| NUMBER   { $$ = $1; }
	| scope    { $$ = $1; }
	;

scope:
	IDENTIFIER COLON IDENTIFIER { $$ = { node_type::scope, $1, $3 }; }
	;

plain_value:
	STRING       { $$ = $1; }
	| NUMBER     { $$ = $1; }
	| BOOLEAN    { $$ = $1; }
	| IDENTIFIER { $$ = $1; }
	;

value:
	plain_value           { $$ = $1; }
	| compound            { $$ = $1; }
	| LBRACE block RBRACE { $$ = $2; }
	;

block:
	%empty       { $$ = json::array(); }
	| statements { $$ = $1; }
	| list       { $$ = $1; }
	;

list:
	plain_value        { $$ = { node_type::list, $1 }; }
	| list plain_value { $$ = $1; $$.push_back($2); }
	;

%%

DA_BEGIN_SCANNER

void parser::error(const location& loc, const std::string& msg) {
	// TODO: Directly format location
	std::ostringstream os;
	os << loc;
	log_error({"parser panicked at {}, because of {}"}, os.str(), msg);
}

DA_END_SCANNER
