#pragma once

#include "Starlight/Core/Logging.hpp"
#include "Starlight/Runtime.hpp"

namespace Star
{
	class Editor final : public Runtime
	{
	public:
		static auto Log(LogLevel level, std::string_view message) -> void;

	protected:
		auto Update(const Time& time) -> void override;
	};
} // namespace Star
