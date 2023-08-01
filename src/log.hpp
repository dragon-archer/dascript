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

template<typename... Args>
struct fmt_loc {
	fmt::format_string<Args...> format;
	spdlog::source_loc          location;

	template<typename String>
	consteval fmt_loc(const String& s, const std::source_location& loc = std::source_location::current()) noexcept
		: format{s}
		, location{get_source_loc(loc)} { }
};

using on_log_handler = std::function<void()>;

inline on_log_handler default_on_log_handler = []() {};

inline on_log_handler _on_log_handlers[spdlog::level::n_levels];

inline on_log_handler set_on_log_handler(spdlog::level::level_enum lvl, const on_log_handler& handler) noexcept {
	return std::exchange(_on_log_handlers[lvl], handler);
}

template<typename... Args>
inline void log(const fmt_loc<Args...>& s, spdlog::level::level_enum lvl, Args&&... args) {
	spdlog::default_logger_raw()->log(s.location,
									  lvl,
									  s.format,
									  std::forward<Args>(args)...);
	_on_log_handlers[lvl]();
}

template<typename... Args>
inline void log_trace(const fmt_loc<Args...>& s, Args&&... args) {
	log(s, spdlog::level::trace, std::forward<Args>(args)...);
}

template<typename... Args>
inline void log_debug(const fmt_loc<Args...>& s, Args&&... args) {
	log(s, spdlog::level::debug, std::forward<Args>(args)...);
}

template<typename... Args>
inline void log_info(const fmt_loc<Args...>& s, Args&&... args) {
	log(s, spdlog::level::info, std::forward<Args>(args)...);
}

template<typename... Args>
inline void log_warning(const fmt_loc<Args...>& s, Args&&... args) {
	log(s, spdlog::level::warn, std::forward<Args>(args)...);
}

template<typename... Args>
inline void log_error(const fmt_loc<Args...>& s, Args&&... args) {
	log(s, spdlog::level::err, std::forward<Args>(args)...);
}

template<typename... Args>
inline void log_critical(const fmt_loc<Args...>& s, Args&&... args) {
	log(s, spdlog::level::critical, std::forward<Args>(args)...);
}

#define daassert(expr) \
	(void)(!!(expr) || (log_error({"Assert \"{}\" failed!"}, #expr), true))

inline void log_begin(spdlog::level::level_enum log_level     = spdlog::level::trace,
					  std::string_view          file_name     = log_file_name,
					  bool                      should_rotate = true) {
	for(auto& h : _on_log_handlers) {
		h = default_on_log_handler;
	}

	std::vector<spdlog::sink_ptr> sinks;
	sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	if(should_rotate) {
		sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
			std::string(file_name), max_log_file_size, max_log_file_count, true));
	} else {
		sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::string(file_name)));
	}
	sinks[0]->set_pattern("[%T.%e][%^%l%$][%s:%#]: %v");
	sinks[1]->set_pattern("[%T.%e][%l][%s:%#]: %v");

	auto logger = std::make_shared<spdlog::logger>("", begin(sinks), end(sinks));
	logger->flush_on(spdlog::level::err);
	spdlog::flush_every(std::chrono::seconds(1));
	spdlog::set_default_logger(logger);
	logger->set_level(log_level);

	log_info({"dascript start"});
}

inline void log_begin_test() {
	for(auto& h : _on_log_handlers) {
		h = default_on_log_handler;
	}

	auto sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
	sink->set_pattern("[%T.%e][%l][%s:%#]: %v");

	auto logger = std::make_shared<spdlog::logger>("", sink);
	logger->flush_on(spdlog::level::err);
	spdlog::flush_every(std::chrono::seconds(1));
	spdlog::set_default_logger(logger);
	logger->set_level(spdlog::level::warn);

	log_info({"dascript test start"});
}

inline void log_end() {
	log_info({"dascript exit"});
	spdlog::shutdown();
}

DA_END_SCRIPT

#endif // _DA_SCRIPT_LOG_HPP_
