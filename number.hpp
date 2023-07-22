/* SPDX-License-Identifier: MIT */
/**
 * @file      number.hpp
 * @brief     Definition for number, constant_number and compound_number
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_NUMBER_HPP_
#define _DA_SCRIPT_NUMBER_HPP_

#include "config.hpp"
#include "object.hpp"

DA_BEGIN_SCRIPT

using number_imp_t = int64_t;

class number : virtual public object {
	number_imp_t _value{};

	public:
	number() noexcept = default;
	number(number_imp_t v) noexcept
		: _value(v), object() { }
	virtual ~number() noexcept = default;

	virtual constexpr types type() const noexcept override {
		return types::number;
	}

	constexpr operator number_imp_t() const noexcept {
		return _value;
	}

	constexpr auto& get() noexcept {
		return _value;
	}
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_NUMBER_HPP_
