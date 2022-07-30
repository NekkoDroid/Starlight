#pragma once

#include <fmt/chrono.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>

namespace Star
{
	enum class LogLevel
	{
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Fatal,
	};

	using LogCallback = void (*)(LogLevel, std::string_view);

	auto SetLogCallback(LogCallback callback) -> void;

	auto GetLogCallback() -> LogCallback;

	template <typename... TArgs>
	auto Log(const LogLevel level, const fmt::format_string<TArgs...> format, TArgs&&... args) -> void
	{
		if (auto callback = GetLogCallback())
			callback(level, fmt::format(format, std::forward<TArgs>(args)...));
	}

	template <typename... TArgs>
	auto LogTrace(const fmt::format_string<TArgs...> format, TArgs&&... args) -> void
	{
		Log(LogLevel::Trace, format, std::forward<TArgs>(args)...);
	}

	template <typename... TArgs>
	auto LogDebug(const fmt::format_string<TArgs...> format, TArgs&&... args) -> void
	{
		Log(LogLevel::Debug, format, std::forward<TArgs>(args)...);
	}

	template <typename... TArgs>
	auto LogInfo(const fmt::format_string<TArgs...> format, TArgs&&... args) -> void
	{
		Log(LogLevel::Info, format, std::forward<TArgs>(args)...);
	}

	template <typename... TArgs>
	auto LogWarn(const fmt::format_string<TArgs...> format, TArgs&&... args) -> void
	{
		Log(LogLevel::Warn, format, std::forward<TArgs>(args)...);
	}

	template <typename... TArgs>
	auto LogError(const fmt::format_string<TArgs...> format, TArgs&&... args) -> void
	{
		Log(LogLevel::Error, format, std::forward<TArgs>(args)...);
	}

	template <typename... TArgs>
	auto LogFatal(const fmt::format_string<TArgs...> format, TArgs&&... args) -> void
	{
		Log(LogLevel::Fatal, format, std::forward<TArgs>(args)...);
	}
} // namespace Star
