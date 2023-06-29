#include "Starlight/Runtime/Application.hpp"

auto Star::AppMain([[maybe_unused]] std::span<const char*> args) -> std::unique_ptr<Main>
{
	return std::make_unique<Application>();
}
