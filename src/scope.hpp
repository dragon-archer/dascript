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

class scope;

using scope_ptr = std::shared_ptr<scope>;

inline scope_ptr empty_scope = std::make_shared<scope>(empty_scope, empty_scope, empty_scope);

class scope : virtual public object, public std::enable_shared_from_this<scope> {
	scope_ptr _root, _from, _prev;

	public:
	scope(const scope_ptr& root = empty_scope, const scope_ptr& from = empty_scope, const scope_ptr& prev = empty_scope) noexcept
		: _root(root)
		, _from(from)
		, _prev(prev) { }
	virtual ~scope() noexcept = default;

	virtual constexpr types type() const noexcept override {
		return types::scope;
	}

	scope_ptr root_scope() noexcept {
		return _root;
	}

	scope_ptr from_scope() noexcept {
		return _from;
	}

	scope_ptr prev_scope() noexcept {
		return _prev;
	}

	scope_ptr this_scope() noexcept {
		return shared_from_this();
	}
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_SCOPE_HPP_
