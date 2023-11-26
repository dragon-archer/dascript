/* SPDX-License-Identifier: MIT */
/**
 * @file      global.hpp
 * @brief     Global objects
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_GLOBAL_HPP_
#define _DA_SCRIPT_GLOBAL_HPP_

#include "config.hpp"
#include "log.hpp"
#include "object.hpp"

DA_BEGIN_SCRIPT

inline size_t random_id() noexcept {
	static std::mt19937_64 engine(std::time(nullptr));
	return engine();
}

inline auto& get_global_object_store() noexcept {
	static std::unordered_map<size_t, object_ptr> instance;
	return instance;
}

inline object_ptr get_global_object(size_t id) {
	auto it = get_global_object_store().find(id);
	if(it == get_global_object_store().end()) {
		return nullptr;
	} else {
		return it->second;
	}
}

template<typename T, typename... Args>
inline auto create_global_object_with_id(size_t id, Args&&... args) {
	auto ptr          = std::make_shared<T>(std::forward<Args>(args)...);
	auto [_, success] = get_global_object_store().try_emplace(id, ptr);
	DA_IFUNLIKELY(!success) {
		log_error({"Failed create global object, id: {}"}, id);
	}
	return std::pair{ptr, id};
}

template<typename T, typename... Args>
inline auto create_global_object(Args&&... args) {
	return create_global_object_with_id(random_id(), std::forward<Args>(args)...);
}

inline auto& get_global_string_store() noexcept {
	static std::unordered_set<std::string> instance;
	return instance;
}

inline std::string_view create_global_string(std::string&& s) {
	auto [iter, _] = get_global_string_store().insert(std::move(s));
	return *iter;
}

DA_END_SCRIPT

#endif // _DA_SCRIPT_GLOBAL_HPP_
