#include "Editor.hpp"

#include <array>
#include <iostream>

template <>
struct fmt::formatter<Star::LogLevel> : fmt::formatter<std::string_view>
{
	template <typename TFormatContext>
	auto format(Star::LogLevel level, TFormatContext& ctx)
	{
		static constexpr std::array levelNames{"TRC", "DBD", "INF", "WRN", "ERR", "FTL"};
		return fmt::formatter<std::string_view>::format(levelNames.at(static_cast<uint8_t>(level)), ctx);
	}
};

namespace Star
{
	auto Editor::Log(LogLevel level, std::string_view message) -> void
	{
		auto& stream = level >= LogLevel::Error ? std::cerr : std::cout;
		fmt::print(stream, "[{}] <{}> {}", std::chrono::system_clock::now(), level, message);
		stream << std::endl;
	}

	auto Editor::Update(const Time& time) -> void
	{
	}
} // namespace Star
