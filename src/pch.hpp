/* SPDX-License-Identifier: MIT */
/**
 * @file      pch.hpp
 * @brief     Pre-compile header for script
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023-2025 dragon-archer
 */

#ifndef _DA_SCRIPT_PCH_HPP_
#define _DA_SCRIPT_PCH_HPP_

#ifdef DASCRIPT_USE_STD_FORMAT
	#define SPDLOG_USE_STD_FORMAT
	#define DA_USE_STD_FORMAT
#endif

#include <da/config.hpp>
#include <da/preprocessor/enum.hpp>
#include <da/utility/hash.hpp>
#include <da/utility/number.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <random>
#include <source_location>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#endif // _DA_SCRIPT_PCH_HPP_
