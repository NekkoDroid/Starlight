#pragma once

#include "Starlight/Platform/Main.hpp"

namespace Star
{
	/// @brief Application runtime.
	class Application : public Main
	{
	public:
		auto Update() -> void override;
	};
} //namespace Star
