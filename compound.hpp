/* SPDX-License-Identifier: MIT */
/**
 * @file      compound.hpp
 * @brief     compound definition
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_COMPOUND_HPP_
#define _DA_SCRIPT_COMPOUND_HPP_

#include "config.hpp"
#include "object.hpp"
#include "statement.hpp"

DA_BEGIN_SCRIPT

using visitor = std::function<void(statement_ptr)>;
using compound_impl = std::vector<statement_ptr>;

class compound : virtual public object {
	compound_impl _value{};

	public:
	compound() noexcept = default;
	virtual ~compound() noexcept  = default;

	virtual constexpr types type() const noexcept override {
		return types::compound;
	}

	constexpr auto& get() noexcept {
		return _value;
	}

	constexpr auto& get() const noexcept {
		return _value;
	}

	void visit(const visitor& vis) const {
		for(const auto& v : _value) {
			vis(v);
		}
	}
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_COMPOUND_HPP_
