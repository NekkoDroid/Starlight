#include "Application.hpp"

namespace Star
{
	auto Application::Update() -> void
	{
	}

	auto Application::Entities() -> EntityManager&
	{
		return m_Entities;
	}

	auto Application::Entities() const -> const EntityManager&
	{
		return m_Entities;
	}
} //namespace Star
