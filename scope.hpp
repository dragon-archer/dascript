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

using scope_ref = std::shared_ptr<scope>;

inline scope_ref empty_scope = std::make_shared<scope>(empty_scope, empty_scope, empty_scope);

class scope : virtual public object, public std::enable_shared_from_this<scope> {
	scope_ref _root, _from, _prev;

	public:
	scope(const scope_ref& root = empty_scope, const scope_ref& from = empty_scope, const scope_ref& prev = empty_scope) noexcept
		: _root(root)
		, _from(from)
		, _prev(prev) { }
	virtual ~scope() noexcept = default;

	virtual constexpr types type() const noexcept override {
		return types::scope;
	}

	scope_ref root_scope() noexcept {
		return _root;
	}

	scope_ref from_scope() noexcept {
		return _from;
	}

	scope_ref prev_scope() noexcept {
		return _prev;
	}

	scope_ref this_scope() noexcept {
		return shared_from_this();
	}
};

DA_END_SCRIPT

#endif // _DA_SCRIPT_SCOPE_HPP_
