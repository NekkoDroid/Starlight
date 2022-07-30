#include "Runtime.hpp"

#include "Starlight/Core/Logging.hpp"
#include "Starlight/Core/Time.hpp"

#include <cassert>
#include <mutex>

#include <SDL2/SDL.h>

namespace Star
{
	auto Runtime::Initialize() -> bool
	{
		LogTrace("Initializing {{Runtime}}");
		if (SDL_Init(SDL_INIT_EVENTS) != 0)
		{
			LogError("Failed to initialize {{Runtime}}");
			return false;
		}
		LogTrace("Initialized {{Runtime}}");
		return true;
	}

	auto Runtime::Terminate() -> void
	{
		LogTrace("Terminating {{Runtime}}");
		SDL_Quit();
		LogTrace("Terminated {{Runtime}}");
	}

	auto Runtime::Run() -> void
	{
		static std::mutex running{};
		const std::unique_lock lock{running, std::try_to_lock};
		assert(lock.owns_lock() && "Multiple games should not be running simultaneously");

		Time time{};

		m_ExitRequested = false;
		while (!IsExitRequested())
		{
			SDL_Event event{};
			while (SDL_PollEvent(&event) == 1)
				HandleEvent(event);

			Update(time);
			time.Update();
		}
	}

	auto Runtime::RequestExit(const bool force) -> void
	{
		if (IsExitRequested())
			return;

		m_ExitRequested = force || OnExitRequested();
	}

	auto Runtime::IsExitRequested() const -> bool
	{
		return m_ExitRequested;
	}

	auto Runtime::OnExitRequested() -> bool
	{
		return true;
	}

	auto Runtime::HandleEvent(const SDL_Event& event) -> void
	{
		switch (event.type)
		{
		case SDL_QUIT:
			RequestExit();
			break;
		}
	}
} // namespace Star
