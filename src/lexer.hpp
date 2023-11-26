/* SPDX-License-Identifier: MIT */
/**
 * @file      lexer.hpp
 * @brief     Script lexer
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_LEXER_HPP_
#define _DA_SCRIPT_LEXER_HPP_

#include "config.hpp"
#include "log.hpp"
#include "number.hpp"
#include "global.hpp"

DA_BEGIN_SCRIPT

using lexer_impl = std::string_view;

enum class lexer_type {
	error,
	identifier,
	number,
	string,
	opcode,
};
DA_DEFINE_ENUM_OPS(lexer_type, constexpr);

class lexer {
	using iter_t = lexer_impl::iterator;
	using char_t = std::remove_cvref_t<decltype(*std::declval<iter_t>())>;

	iter_t     _cur, _end;
	int        _line{1};
	lexer_type _type{lexer_type::error};
	union {
		lexer_impl  _error;
		lexer_impl  _identifier;
		number_impl _number;
		lexer_impl  _string;
		char_t      _opcode;
	};

	enum class type { // internal type
		error,
		digit,
		alphabet,
		opcode,
	};

	public:
	constexpr lexer(lexer_impl s) noexcept
		: _cur(s.begin())
		, _end(s.end()) { }

	constexpr lexer(iter_t begin, iter_t end) noexcept
		: _cur(begin)
		, _end(end) { }

	constexpr lexer_type next() noexcept {
		skip_white();
		switch(peek_type()) {
			case type::digit:
				next_number();
				break;
			case type::alphabet:
				next_alphabet();
				break;
			case type::opcode:
				next_opcode();
				break;
		}
		return _type;
	}

	private:
	constexpr void emit_error(std::string_view reason) noexcept {
		_error = reason;
		_type  = lexer_type::error;
	}

	constexpr type peek_type() const noexcept {
		const auto c = *_cur;
		if(std::isalpha(c) || in_list(c, "_\""sv)) {
			return type::alphabet;
		} else if(in_list(c, "0123456789.-"sv)) {
			return type::digit;
		} else if(in_list(c, "={}"sv)) {
			return type::opcode;
		} else {
			return type::error;
		}
	}

	constexpr void skip_white() noexcept {
		while(is_valid()) {
			switch(*_cur) {
				case '\n':
					++_line;
					[[fallthorugh]];
				case '\t':
					[[fallthorugh]];
				case '\v':
					[[fallthorugh]];
				case '\f':
					[[fallthorugh]];
				case '\r':
					[[fallthorugh]];
				case ' ':
					++_cur;
					break;
				default:
					return;
			}
		}
	}

	constexpr char_t next_char() noexcept {
		++_cur;
		return *_cur;
	}

	constexpr bool next_number() noexcept {
		auto        ch = *_cur;
		number_impl f = 1, v = 0, mul = 0.1;
		bool        has_dot = false;
		if(ch == '-') {
			f  = -1;
			ch = next_char();
		}
		while(valid_char(ch)) {
			if(ch == '.') {
				if(has_dot) {
					emit_error("Multiple dots found in a number."sv);
					return false;
				}
				has_dot = true;
			} else if(ch >= '0' && ch <= '9') {
				if(has_dot) {
					v += (ch - '0') * mul;
					mul *= 0.1;
				} else {
					v *= 10;
					v += ch - '0';
				}
			} else {
				emit_error("Invalid character found in a number."sv);
				return false;
			}
			ch = next_char();
		}
		_type   = lexer_type::number;
		_number = v * f;
		return true;
	}

	constexpr bool next_alphabet() noexcept {
		auto ch = *_cur;
		if(ch == '"') { // is_quoted
			bool is_escaped = false;
			std::string s;
			while((ch = next_char()) && is_valid()) {
				if(is_escaped) {
					DA_IFLIKELY(ch == '"') {
						s += '"';
					} else {
						emit_error("Invalid escaped letter in quoted string."sv);
						return false;
					}
					is_escaped = false;
				} else {
					switch(ch) {
						case '"':
							_type   = lexer_type::string;
							_string = create_global_string(std::move(s));
							++_cur;
							return true;
						case '\\':
							is_escaped = true;
							break;
						case '\n':
							++_line;
							[[fallthrough]];
						default:
							s += ch;
							break;
					}
				}
			}
			emit_error("Unexpected end reached in quoted string."sv);
			return false;
		} else { // normal
			auto it = ++_cur;
			while(it != _end && !std::isblank(*it)) {
				++it;
			}
			_type = lexer_type::identifier;
			_identifier = create_global_string(std::string(_cur, it));
			_cur        = it;
			return true;
		}
	}

	constexpr bool next_opcode() noexcept {
		_type   = lexer_type::opcode;
		_opcode = *_cur;
		++_cur;
		return true;
	}

	static constexpr bool in_list(char_t ch, lexer_impl s) noexcept {
		return s.find(ch) != s.npos;
	}

	constexpr bool is_valid() const noexcept {
		return _cur != _end;
	}

	constexpr bool valid_char(char_t ch) const noexcept {
		return is_valid() && !std::isblank(ch);
	}
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_LEXER_HPP_
