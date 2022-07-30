#include "Time.hpp"

#include <cassert>

namespace Star
{
	auto Time::Update() -> void
	{
		const auto lastFrameEndTime = m_FrameEndTime;
		const auto targetFrameEndTime = lastFrameEndTime + GetTargetFrameTime();

		do // Busy-wait until target frame time has been reached
		{
			m_FrameEndTime = Clock::now();
		} while (m_FrameEndTime < targetFrameEndTime);
		m_DeltaTime = m_FrameEndTime - lastFrameEndTime;

		if (GetMaximumDeltaTime() > Duration::zero() && m_DeltaTime > GetMaximumDeltaTime())
			m_DeltaTime = GetMaximumDeltaTime();

		m_CurrentMaximumDeltaTime = m_BufferedMaximumDeltaTime;
		m_CurrentTargetFrameTime = m_BufferedTargetFrameTime;
	}

	auto Time::GetDeltaTime() const -> Duration
	{
		return m_DeltaTime;
	}

	Time::operator Duration() const
	{
		return GetDeltaTime();
	}

	auto Time::GetMaximumDeltaTime() const -> Duration
	{
		return m_CurrentMaximumDeltaTime;
	}

	auto Time::SetMaximumDeltaTime(const Duration maximumDeltaTime) const -> void
	{
		assert(maximumDeltaTime >= Duration::zero() && "{maximumDeltaTime} should not be less than 0");
		m_BufferedMaximumDeltaTime = maximumDeltaTime;
	}

	auto Time::GetTargetFrameTime() const -> Duration
	{
		return m_CurrentTargetFrameTime;
	}

	auto Time::SetTargetFrameTime(const Duration targetFrameTime) const -> void
	{
		assert(targetFrameTime >= Duration::zero() && "{targetFrameTime} should not be less than 0");
		m_BufferedTargetFrameTime = targetFrameTime;
	}
} // namespace Star
