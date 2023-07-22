#include "Entity.hpp"

namespace Star
{
	auto EntityManager::Create() -> Entity
	{
		return create();
	}

	auto EntityManager::Destroy(Entity entity) -> void
	{
		destroy(entity);
	}

	auto EntityManager::Valid(Entity entity) const -> bool
	{
		return valid(entity);
	}
} //namespace Star
