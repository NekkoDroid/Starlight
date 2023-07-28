#include "System.hpp"

#include <algorithm>
#include <ranges>
#include <vector>

namespace Star
{
	auto operator<(const SystemKey& lhs, const SystemKey& rhs) -> bool
	{
		if (std::ranges::any_of(lhs.Precedes, [&](entt::id_type type) { return type == rhs.Type; }))
			return true;

		if (std::ranges::any_of(rhs.Succeeds, [&](entt::id_type type) { return type == lhs.Type; }))
			return true;

		return lhs.Type < rhs.Type;
	}

	auto SystemGroup::Update(EntityManager& entities) -> void
	{
		auto values = std::views::values(m_Systems);
		for (const auto& system : std::vector(values.begin(), values.end()))
			system->Update(entities);
	}
} //namespace Star
