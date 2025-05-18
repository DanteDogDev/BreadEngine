/**
 * @file pch.h
 * @author Dante Harper
 * @date 16/05/25
 */

#pragma once

#include <any>
#include <fstream>
#include <functional>
#include <iomanip>
#include <map>
#include <memory>
#include <queue>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeindex>

using RenderID = unsigned int;

#if defined(_WIN32) || defined(_WIN64)
#define TOAST_API __declspec(dllexport)
#elif defined(__linux__)
#define TOAST_API __attribute__((visibility("default")))
#elif defined(__APPLE__)
#define TOAST_API __attribute__((visibility("default")))
#endif

#if defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
#include <csignal>
#define DEBUG_BREAK() raise(SIGTRAP)
#else
#define DEBUG_BREAK() ((void)0)
#endif
