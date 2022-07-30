#pragma once

union SDL_Event;

namespace Star
{
	class Time;

	class Runtime
	{
	public:
		Runtime() = default;
		virtual ~Runtime() = default;

		Runtime(const Runtime&) = delete;
		Runtime(Runtime&&) = delete;

		auto operator=(const Runtime&) -> Runtime& = delete;
		auto operator=(Runtime&&) -> Runtime& = delete;

		static auto Initialize() -> bool;
		static auto Terminate() -> void;

		auto Run() -> void;

		auto RequestExit(bool force = false) -> void;
		[[nodiscard]] auto IsExitRequested() const -> bool;

	protected:
		virtual auto Update(const Time& time) -> void = 0;
		virtual auto OnExitRequested() -> bool;

	private:
		auto HandleEvent(const SDL_Event& event) -> void;

		bool m_ExitRequested{};
	};
} // namespace Star
