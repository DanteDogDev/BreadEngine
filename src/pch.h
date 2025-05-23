/**
 * @file pch.h
 * @author Dante Harper
 * @date 16/05/25
 */

#pragma once

///
#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <memory>
#include <ranges>
#include <sstream>
#include <stdexcept>
///
#include <array>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
///

#if defined(_WIN32) || defined(_WIN64)
#define TOAST_API __declspec(dllexport)
#elif defined(__linux__)
#define TOAST_API __attribute__((visibility("default")))
#elif defined(__APPLE__)
#define TOAST_API __attribute__((visibility("default")))
#elif
#define TOAST_API
#endif

#if defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
#include <csignal>
#define DEBUG_BREAK() raise(SIGTRAP)
#else
#define DEBUG_BREAK() ((void)0)
#endif
