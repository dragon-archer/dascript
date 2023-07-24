/* SPDX-License-Identifier: MIT */
/**
 * @file      function.hpp
 * @brief     function definition
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_FUNCTION_HPP_
#define _DA_SCRIPT_FUNCTION_HPP_

#include "config.hpp"
#include "scope.hpp"
#include "object.hpp"

DA_BEGIN_SCRIPT

class function : virtual public object {
	public:
	function() noexcept = default;
	virtual ~function() = default;

	virtual constexpr types type() const noexcept override {
		return types::function;
	}

	virtual void operator()(scope_ptr scope_, object_ptr param, object_ptr ret) = 0;
};

using plain_function_impl = std::function<void(scope_ptr, object_ptr, object_ptr)>;

class plain_function : public function {
	plain_function_impl _func{};

	public:
	plain_function() noexcept = default;
	plain_function(const plain_function_impl& func)
		: _func(func) { }
	virtual ~plain_function() = default;

	virtual constexpr types type() const noexcept override {
		return types::plain_function;
	}

	constexpr auto& get() noexcept {
		return _func;
	}

	virtual void operator()(scope_ptr s, object_ptr p, object_ptr r) override {
		_func(s, p, r);
	}
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_FUNCTION_HPP_
