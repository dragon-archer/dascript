/* SPDX-License-Identifier: MIT */
/**
 * @file      number.hpp
 * @brief     Definition for number, plain_number and compound_number
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_NUMBER_HPP_
#define _DA_SCRIPT_NUMBER_HPP_

#include "config.hpp"
#include "compound.hpp"
#include "object.hpp"
#include "scope.hpp"

DA_BEGIN_SCRIPT

using number_impl = fixed_point<5>;

class number : virtual public object {
	public:
	number() noexcept          = default;
	virtual ~number() noexcept = default;

	virtual constexpr types type() const noexcept override {
		return types::number;
	}

	virtual number_impl get_value(scope_ptr = empty_scope) const noexcept = 0;
};

class plain_number : public number {
	number_impl _value;

	public:
	plain_number(number_impl v = {}) noexcept
		: _value(v) { }
	virtual ~plain_number() noexcept = default;

	virtual constexpr types type() const noexcept override {
		return types::plain_number;
	}

	constexpr operator number_impl() const noexcept {
		return _value;
	}

	constexpr void set_value(number_impl v) noexcept {
		_value = v;
	}

	virtual number_impl get_value(scope_ptr = empty_scope) const noexcept override {
		return _value;
	}
};

class compound_number : public compound, public number {
	public:
	compound_number() noexcept          = default;
	virtual ~compound_number() noexcept = default;

	virtual constexpr types type() const noexcept override {
		return types::compound_number;
	}

	virtual number_impl get_value(scope_ptr s = empty_scope) const noexcept override {
		auto v = std::make_shared<plain_number>();
		this->visit([&v, &s](const statement_ptr& p) {
			(*p)(s, v);
		});
		return v->get_value();
	}
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_NUMBER_HPP_
