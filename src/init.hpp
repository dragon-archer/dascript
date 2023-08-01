/* SPDX-License-Identifier: MIT */
/**
 * @file      init.hpp
 * @brief     init functions
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_INIT_HPP_
#define _DA_SCRIPT_INIT_HPP_

#include "config.hpp"
#include "function.hpp"
#include "global.hpp"
#include "log.hpp"
#include "number.hpp"
#include "scope.hpp"

DA_BEGIN_SCRIPT

inline void create_plain_function(std::string_view name, const plain_function_impl& func) {
	size_t id = hash(name);
	create_global_object_with_id<plain_function>(id, func);
}

inline void init_plain_functions() {
	log_info({"Start init plain functions"});
	create_plain_function("value", [](scope_ptr, object_ptr p, object_ptr r) {
		auto rn = object_cast<plain_number>(r);
		auto pn = object_cast<number>(p);
		rn->set_value(pn->get_value());
	});
	create_plain_function("add", [](scope_ptr, object_ptr p, object_ptr r) {
		auto rn = object_cast<plain_number>(r);
		auto pn = object_cast<number>(p);
		rn->set_value(rn->get_value() + pn->get_value());
	});
	create_plain_function("subtract", [](scope_ptr, object_ptr p, object_ptr r) {
		auto rn = object_cast<plain_number>(r);
		auto pn = object_cast<number>(p);
		rn->set_value(rn->get_value() - pn->get_value());
	});
	create_plain_function("multiply", [](scope_ptr, object_ptr p, object_ptr r) {
		auto rn = object_cast<plain_number>(r);
		auto pn = object_cast<number>(p);
		rn->set_value(rn->get_value() * pn->get_value());
	});
	create_plain_function("divide", [](scope_ptr, object_ptr p, object_ptr r) {
		auto rn = object_cast<plain_number>(r);
		auto pn = object_cast<number>(p);
		rn->set_value(rn->get_value() / pn->get_value());
	});
	create_plain_function("min", [](scope_ptr, object_ptr p, object_ptr r) {
		auto rn = object_cast<plain_number>(r);
		auto pn = object_cast<number>(p);
		rn->set_value(std::min(rn->get_value(), pn->get_value()));
	});
	create_plain_function("max", [](scope_ptr, object_ptr p, object_ptr r) {
		auto rn = object_cast<plain_number>(r);
		auto pn = object_cast<number>(p);
		rn->set_value(std::max(rn->get_value(), pn->get_value()));
	});
	log_info({"Plain functions inited."});
}

DA_END_SCRIPT

#endif // _DA_SCRIPT_INIT_HPP_
