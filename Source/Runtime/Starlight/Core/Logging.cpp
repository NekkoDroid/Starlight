#include "Logging.hpp"

namespace Star
{
	static LogCallback Callback{}; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

	auto SetLogCallback(const LogCallback callback) -> void
	{
		Callback = callback;
	}

	auto GetLogCallback() -> LogCallback
	{
		return Callback;
	}
} // namespace Star
