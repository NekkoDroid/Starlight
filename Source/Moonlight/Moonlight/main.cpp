#include "Starlight/Platform/Window.hpp"
#include "Starlight/Runtime/Application.hpp"

auto Star::AppMain([[maybe_unused]] std::span<const char*> args) -> std::unique_ptr<Main>
{
	auto app = std::make_unique<Application>();

	// NOLINTNEXTLINE(*-magic-numbers)
	app->Entities().CreateSingleton<Window>("Moonlight", glm::ivec2{1600, 900}, 0);

	return app;
}
