#pragma once

#include <chrono>

namespace Star
{
	using Clock = std::chrono::steady_clock;

	using Duration = std::chrono::duration<double>;

	using TimePoint = Clock::time_point;

	class Time
	{
	public:
		auto Update() -> void;

		[[nodiscard]] auto GetDeltaTime() const -> Duration;
		[[nodiscard]] explicit operator Duration() const;

		[[nodiscard]] auto GetMaximumDeltaTime() const -> Duration;
		auto SetMaximumDeltaTime(Duration maximumDeltaTime) const -> void;

		[[nodiscard]] auto GetTargetFrameTime() const -> Duration;
		auto SetTargetFrameTime(Duration targetFrameTime) const -> void;

	private:
		TimePoint m_FrameEndTime{Clock::now()};
		Duration m_DeltaTime{};

		Duration m_CurrentMaximumDeltaTime{};
		mutable Duration m_BufferedMaximumDeltaTime{};

		Duration m_CurrentTargetFrameTime{};
		mutable Duration m_BufferedTargetFrameTime{};
	};
} // namespace Star
