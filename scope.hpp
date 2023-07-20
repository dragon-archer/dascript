/* SPDX-License-Identifier: MIT */
/**
 * @file      scope.hpp
 * @brief     Scope definition
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_SCOPE_HPP_
#define _DA_SCRIPT_SCOPE_HPP_

#include "config.hpp"
#include "object.hpp"

DA_BEGIN_SCRIPT

class scope : public object {
	size_t _root{}, _from{}, _this{}, _prev{};

	public:
	constexpr scope() noexcept = default;
	virtual ~scope() noexcept  = default;

	virtual constexpr types type() const noexcept override {
		return types::scope;
	}
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_SCOPE_HPP_
