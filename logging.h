#pragma once

#include <fmt/format.h>

template <typename... Args>
void PrintLog(const char* log_level, unsigned int line_num, const char* function,
              const char* format, const Args&... args) {
    fmt::print("fios2.cpp:{} <{}>", line_num, log_level, function,
               fmt::vformat(format, fmt::make_format_args(args...)));
}

#define LOG_DEBUG(...) PrintLog("Debug", __LINE__, __func__, __VA_ARGS__)
#define LOG_INFO(...) PrintLog("Info", __LINE__, __func__, __VA_ARGS__)
#define LOG_WARNING(...) PrintLog("Warning", __LINE__, __func__, __VA_ARGS__)
#define LOG_ERROR(...) PrintLog("Error", __LINE__, __func__, __VA_ARGS__)
#define LOG_CRITICAL(...) PrintLog("Critical", __LINE__, __func__, __VA_ARGS__)