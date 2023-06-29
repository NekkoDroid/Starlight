#pragma once

#include <memory>
#include <optional>
#include <span>

namespace Star
{
	/// @brief Application main loop.
	class Main
	{
	public:
		/// @brief Virtual destructor.
		virtual ~Main() = default;

		/// @brief Advance the application state.
		virtual auto Update() -> void = 0;

		/// @brief Check if an exit has been requested.
		/// @return Status of the exit request.
		[[nodiscard]] auto ExitRequested() const -> bool;

		/// @brief Request the main loop to stop.
		/// @param exitCode Exit code to return to the operating system.
		auto RequestExit(int exitCode) -> void;

		/// @brief Get the exit code to be returned to the operating system.
		/// @return Value containing the exit code.
		[[nodiscard]] auto ExitCode() const -> int;

		/// @brief Process all pending platform events.
		/// @return Value indicating if the program should continue updating.
		static auto ProcessEvents() -> bool;

	protected:
		/// @brief Intercept exit requests.
		/// @return @c false to prevent exiting, @c true otherwise.
		virtual auto OnExitRequested() -> bool;

	private:
		std::optional<int> m_ExitCode{};
	};

	/// @brief Application entry point.
	/// @param args Command line arguments.
	/// @return Application main loop.
	extern auto AppMain(std::span<const char*> args) -> std::unique_ptr<Main>;
} //namespace Star
