#pragma once

#include "Starlight/Platform/Main.hpp"
#include "Starlight/Runtime/Entity.hpp"

namespace Star
{
	/// @brief Application runtime.
	class Application : public Main
	{
	public:
		auto Update() -> void override;

		/// @brief Get the entity manager.
		/// @return A reference to the entity manager.
		[[nodiscard]] auto Entities() -> EntityManager&;

		/// @brief Get the entity manager.
		/// @return A reference to the entity manager.
		[[nodiscard]] auto Entities() const -> const EntityManager&;

	private:
		EntityManager m_Entities{};
	};
} //namespace Star
