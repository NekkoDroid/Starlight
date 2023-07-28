#pragma once

#include "Starlight/Platform/Main.hpp"
#include "Starlight/Runtime/Entity.hpp"
#include "Starlight/Runtime/System.hpp"

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

		/// @brief Get the system manager.
		/// @return A reference to the system manager.
		[[nodiscard]] auto Systems() -> SystemManager&;

		/// @brief Get the system manager.
		/// @return A reference to the system manager.
		[[nodiscard]] auto Systems() const -> const SystemManager&;

	private:
		EntityManager m_Entities{};
		SystemManager m_Systems{};
	};
} //namespace Star
