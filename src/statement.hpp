/* SPDX-License-Identifier: MIT */
/**
 * @file      statement.hpp
 * @brief     statement definition
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_STATEMENT_HPP_
#define _DA_SCRIPT_STATEMENT_HPP_

#include "config.hpp"
#include "function.hpp"
#include "object.hpp"
#include "scope.hpp"

DA_BEGIN_SCRIPT

class statement : virtual public object {
	object_ptr _lparam, _rparam;

	public:
	statement(object_ptr lparam, object_ptr rparam) noexcept
		: _lparam(lparam)
		, _rparam(rparam) { }
	virtual ~statement() = default;

	virtual constexpr types type() const noexcept override {
		return types::statement;
	}

	constexpr auto& get_lparam() noexcept {
		return _lparam;
	}

	constexpr auto& get_rparam() noexcept {
		return _rparam;
	}

	void operator()(scope_ptr s, object_ptr p) {
		auto f = object_cast<function>(_lparam);
		(*f)(s, _rparam, p);
	}
};

using statement_ptr = std::shared_ptr<statement>;

DA_END_SCRIPT

#endif // _DA_SCRIPT_STATEMENT_HPP_
