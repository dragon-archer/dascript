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
#include "log.hpp"

DA_BEGIN_SCRIPT

enum class types {
	error_type = 0,
	object     = 1,

	// Modifiers
	plain    = 1 << 1 | object,
	compound = 1 << 2 | object,
	constant = 1 << 3 | object,

	// Abstract types
	number    = 1 << 4 | object,
	scope     = 1 << 5 | object,
	statement = 1 << 6 | object,
	function  = 1 << 7 | object,
	property  = 1 << 8 | object,

	// Actual types
	plain_number      = plain | number,
	compound_number   = compound | number,
	plain_function    = plain | function,
	compound_function = compound | function,
};
DA_DEFINE_ENUM_OPS(types, constexpr);

inline std::unordered_map<types, std::string_view> types_name = {
	{types::error_type, "error_type"},
	{types::object, "object"},

	{types::plain, "plain"},
	{types::compound, "compound"},
	{types::constant, "constant"},

	{types::number, "number"},
	{types::scope, "scope"},
	{types::statement, "statement"},
	{types::function, "function"},
	{types::property, "property"},

	{types::plain_number, "plain_number"},
	{types::compound_number, "compound_number"},
	{types::plain_function, "plain_function"},
	{types::compound_function, "compound_function"},
};

constexpr bool check_type(types check, types expected) noexcept {
	return (check & expected) == expected;
}

#define assert_type(check, expected) \
	(check_type((check), (expected)) \
	 || (log_error({"Type error! Expected {}, got {}"}, types_name[(expected)], types_name[(check)]), false))

class object {
	public:
	constexpr object() noexcept = default;
	virtual ~object() noexcept  = default;

	virtual constexpr types type() const noexcept {
		return types::object;
	}

	virtual constexpr bool is_constant() noexcept {
		return false;
	}

	virtual constexpr bool is_constant() const noexcept {
		return true;
	}
};

using object_ptr = std::shared_ptr<object>;

template<typename T, typename... Args>
inline object_ptr create_object(Args&&... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
	requires std::is_base_of_v<object, T>
inline std::shared_ptr<T> object_cast(object_ptr p) noexcept {
	try {
		auto np = dynamic_cast<T*>(p.get());
		return {p, np};
	} catch(const std::bad_cast&) {
		log_error({"Object cast failed, real type: {}"}, types_name[p->type()]);
		return {};
	}
}

DA_END_SCRIPT

#endif // _DA_SCRIPT_OBJECT_HPP_
