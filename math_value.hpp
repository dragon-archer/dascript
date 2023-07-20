/* SPDX-License-Identifier: MIT */
/**
 * @file      math_value.hpp
 * @brief     math_value definition
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_MATH_VALUE_HPP_
#define _DA_SCRIPT_MATH_VALUE_HPP_

#include "config.hpp"
#include "scope.hpp"

DA_BEGIN_SCRIPT

class math_value : public scope {
	int64_t _value{};

	public:
	constexpr math_value() noexcept = default;
	virtual ~math_value() noexcept  = default;

	virtual constexpr types type() const noexcept override {
		return types::math_value;
	}

	constexpr operator int64_t() const noexcept {
		return _value;
	}

	constexpr int64_t& get() noexcept {
		return _value;
	}
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_MATH_VALUE_HPP_
