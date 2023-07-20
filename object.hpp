/* SPDX-License-Identifier: MIT */
/**
 * @file      object.hpp
 * @brief     Object definition
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_OBJECT_HPP_
#define _DA_SCRIPT_OBJECT_HPP_

#include "config.hpp"

DA_BEGIN_SCRIPT

enum class types {
	error        = 0,
	object       = 1,
	scope        = 1 << 1 | object,
	raw_function = 1 << 2 | object,
	math_value   = 1 << 3 | scope,
	function     = 1 << 4 | scope,
};
DA_DEFINE_ENUM_OPS(types, constexpr);

class object {
	public:
	constexpr object() noexcept = default;
	virtual ~object() noexcept  = default;

	virtual constexpr types type() const noexcept {
		return types::object;
	}
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_OBJECT_HPP_
