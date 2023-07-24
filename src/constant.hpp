/* SPDX-License-Identifier: MIT */
/**
 * @file      constant.hpp
 * @brief     constant definition
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_CONSTANT_HPP_
#define _DA_SCRIPT_CONSTANT_HPP_

#include "config.hpp"
#include "object.hpp"

DA_BEGIN_SCRIPT

class constant : virtual public object {
	public:
	constant() noexcept          = default;
	virtual ~constant() noexcept = default;

	virtual constexpr types type() const noexcept override {
		return types::constant;
	}

	virtual constexpr bool is_constant() noexcept override {
		return true;
	}
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_CONSTANT_HPP_
