#include "Application.hpp"

namespace Star
{
	auto Application::Update() -> void
	{
		Systems().Update(Entities());
	}

	auto Application::Entities() -> EntityManager&
	{
		return m_Entities;
	}

	auto Application::Entities() const -> const EntityManager&
	{
		return m_Entities;
	}

	auto Application::Systems() -> SystemManager&
	{
		return m_Systems;
	}

	auto Application::Systems() const -> const SystemManager&
	{
		return m_Systems;
	}
} //namespace Star
