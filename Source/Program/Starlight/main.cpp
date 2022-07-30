#include "Starlight/Editor/Editor.hpp"

#include <cstdlib>

auto main() -> int
{
	Star::SetLogCallback(Star::Editor::Log);

	if (!Star::Editor::Initialize())
		return EXIT_FAILURE;

	if (std::atexit(Star::Editor::Terminate) != 0)
		Star::LogWarn("{{Star::Editor::Terminate}} will not be called at exit");

	Star::Editor{}.Run();
}
