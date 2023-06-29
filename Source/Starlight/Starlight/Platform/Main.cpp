#include "Main.hpp"

#include <SDL2/SDL.h>

#include <cstdlib>

#define NOOP ((void)0)

auto main(int argc, char* argv[]) -> int
{
	using namespace Star;

	if (SDL_Init(SDL_INIT_EVENTS) < 0)
	{
		NOOP; // TODO: Log[Fatal] {{SDL_Init}} failed: {SDL_GetError()}
		return EXIT_FAILURE;
	}

	if (std::atexit(SDL_Quit) != 0)
		NOOP; // TODO: Log[Warn] {{SDL_Quit}} will not be called at exit

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
	auto appMain = AppMain(std::span{const_cast<const char**>(argv), static_cast<size_t>(argc)});
	if (!appMain)
	{
		NOOP; // TODO: Log[Fatal] {{AppMain}} returned no main instance
		return EXIT_FAILURE;
	}

	while (!appMain->ExitRequested())
	{
		if (!Main::ProcessEvents())
			appMain->RequestExit(EXIT_SUCCESS);

		appMain->Update();
	}

	return appMain->ExitCode();
}

namespace Star
{
	auto Main::ExitRequested() const -> bool
	{
		return m_ExitCode.has_value();
	}

	auto Main::RequestExit(int exitCode) -> void
	{
		if (ExitRequested())
			return;

		if (!OnExitRequested())
			return;

		m_ExitCode = exitCode;
	}

	auto Main::ExitCode() const -> int
	{
		return m_ExitCode.value_or(0);
	}

	auto Main::ProcessEvents() -> bool
	{
		SDL_Event event{};
		while (SDL_PollEvent(&event) == 1)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return false;
			}
		}

		return true;
	}

	auto Main::OnExitRequested() -> bool
	{
		return true;
	}
} //namespace Star
