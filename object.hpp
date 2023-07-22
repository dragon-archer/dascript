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

/*
	Example:
	namespace = da						# field init using string
	da.1 = {							# field init using compound
		name = da.1.t					# field init using token
		trigger = {						# field init using compound_trigger
			is_ai = no					# scoped trigger
			gold > 1000					# comparison trigger
			^ <=> greater_than = { left = gold right = 1000 }
		}
		option = {						# field init using compound_effect
			add_gold = {				# field init using math_value
				add = 10				# field init using constant
				if = {					# effect init using compound_effect
					limit = {			# field
						gold < 2000		# trigger
					}
					add = 20			# effect
				}
			}
		}
	}

	trigger: bool(size_t scope_id, size_t param_id)
	effect: void(size_t scope_id, size_t param_id), modify will happen on scope_id
*/

enum class types {
	error  = 0,
	object = 1,

	// Modifiers
	constant = 1 << 1 | object,
	native   = 1 << 2 | object,
	compound = 1 << 3 | object,

	// Abstract types
	number  = 1 << 4 | object,
	scope   = 1 << 5 | object,
	trigger = 1 << 6 | object,
	effect  = 1 << 7 | object,

	// Actual types
	constant_number  = constant | number,
	compound_number  = compound | number,
	native_trigger   = native | trigger,
	compound_trigger = compound | trigger,
	native_effect    = native | effect,
	compound_effect  = compound | effect,
};
DA_DEFINE_ENUM_OPS(types, constexpr);

inline std::unordered_map<types, std::string_view> types_name = {
	{types::error, "error type"},
	{types::object, "object"},

	{types::constant, "constant"},
	{types::native, "native"},
	{types::compound, "compound"},

	{types::number, "number"},
	{types::scope, "scope"},
	{types::trigger, "trigger"},
	{types::effect, "effect"},

	{types::constant_number, "constant_number"},
	{types::compound_number, "compound_number"},
	{types::native_trigger, "native_trigger"},
	{types::compound_trigger, "compound_trigger"},
	{types::native_effect, "native_effect"},
	{types::compound_effect, "compound_effect"},
};

constexpr bool check_type(types check, types expected) noexcept {
	return (check & expected) == expected;
}

#define assert_type(check, expected) \
	(check_type((check), (expected)) \
	 || (log_error("Type error! Expected {}, got {}", types_name[(expected)], types_name[(check)]), false))

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
