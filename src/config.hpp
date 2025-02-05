/* SPDX-License-Identifier: MIT */
/**
 * @file      config.hpp
 * @brief     Config for script
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023-2025 dragon-archer
 */

#ifndef _DA_SCRIPT_CONFIG_HPP_
#define _DA_SCRIPT_CONFIG_HPP_

#include "pch.hpp"

#define DA_BEGIN_SCRIPT \
	DA_BEGIN_NAMESPACE  \
	namespace script {
#define DA_END_SCRIPT \
	}                 \
	DA_END_NAMESPACE
#define DA_SCRIPT ::da::script

#define DA_BEGIN_SCANNER \
	DA_BEGIN_SCRIPT      \
	namespace scanner {
#define DA_END_SCANNER \
	}                  \
	DA_END_SCRIPT
#define DA_SCANNER ::da::script::scanner

DA_BEGIN_SCRIPT
using namespace std::literals;
DA_END_SCRIPT

#endif // _DA_SCRIPT_CONFIG_HPP_
