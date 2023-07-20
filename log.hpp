/* SPDX-License-Identifier: MIT */
/**
 * @file      log.hpp
 * @brief     Wrapper of spdlog
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_LOG_HPP_
#define _DA_SCRIPT_LOG_HPP_

#include "config.hpp"

DA_BEGIN_SCRIPT

static constexpr size_t           max_log_file_size  = 1024 * 1024 * 5; // 5MB
static constexpr size_t           max_log_file_count = 5;
static constexpr std::string_view log_file_name      = "script.log";

[[nodiscard]] constexpr auto get_source_loc(const std::source_location& loc) {
	return spdlog::source_loc{loc.file_name(),
							  static_cast<int>(loc.line()),
							  loc.function_name()};
}

struct fmt_loc {
	std::string_view   format;
	spdlog::source_loc location;

	template<typename String>
	constexpr fmt_loc(const String& s, const std::source_location& loc = std::source_location::current()) noexcept
		: format{s}
		, location{get_source_loc(loc)} { }
};

template<typename... Args>
inline void log(fmt_loc s, spdlog::level::level_enum lvl, Args&&... args) {
	spdlog::default_logger_raw()->log(s.location,
									  lvl,
									  fmt::runtime(s.format),
									  std::forward<Args>(args)...);
}

template<typename... Args>
inline void log_trace(fmt_loc s, Args&&... args) {
	log(s, spdlog::level::trace, std::forward<Args>(args)...);
}

template<typename... Args>
inline void log_debug(fmt_loc s, Args&&... args) {
	log(s, spdlog::level::debug, std::forward<Args>(args)...);
}

template<typename... Args>
inline void log_info(fmt_loc s, Args&&... args) {
	log(s, spdlog::level::info, std::forward<Args>(args)...);
}

template<typename... Args>
inline void log_warn(fmt_loc s, Args&&... args) {
	log(s, spdlog::level::warn, std::forward<Args>(args)...);
}

template<typename... Args>
inline void log_error(fmt_loc s, Args&&... args) {
	log(s, spdlog::level::err, std::forward<Args>(args)...);
}

template<typename... Args>
inline void log_critical(fmt_loc s, Args&&... args) {
	log(s, spdlog::level::critical, std::forward<Args>(args)...);
}

inline int _run_before_main_log = []() {
	std::shared_ptr<spdlog::logger> logger = nullptr;
	std::vector<spdlog::sink_ptr>   sinks;

	sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
		std::string(log_file_name), max_log_file_size, max_log_file_count, true));

	sinks[0]->set_pattern("[%T.%e][%^%l%$][%s:%#]: %v");
	sinks[1]->set_pattern("[%T.%e][%l][%s:%#]: %v");

	logger = std::make_shared<spdlog::logger>("", begin(sinks), end(sinks));
	logger->flush_on(spdlog::level::err);
	spdlog::flush_every(std::chrono::seconds(1));
	spdlog::set_default_logger(logger);
	logger->set_level(spdlog::level::trace);

	return 0;
}();

DA_END_SCRIPT

#endif // _DA_SCRIPT_LOG_HPP_
