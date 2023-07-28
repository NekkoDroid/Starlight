#pragma once

#include "Starlight/Runtime/Entity.hpp"

#include <array>
#include <concepts>
#include <map>
#include <memory>
#include <span>

namespace Star
{
	/// @brief A behavioral system base.
	class System
	{
	public:
		/// @brief Destructor.
		virtual ~System() = default;

		/// @brief Update the system.
		/// @param entities Entities on which the system should operate.
		virtual auto Update(EntityManager& entities) -> void = 0;
	};

	/// @brief A list of system type indices.
	/// @tparam TSystems System types.
	template <std::derived_from<System>... TSystems>
	struct SystemList
	{
		/// @brief System type indices.
		static constexpr auto Hashes =
			std::array<entt::id_type, sizeof...(TSystems)>{entt::type_hash<TSystems>::value()...};
	};

	/// @brief Check if a type is a system list.
	/// @tparam T Type to check.
	template <typename T>
	struct IsSystemList : std::false_type
	{
	};

	/// @brief Check if a type is a system list.
	/// @tparam TSystems System types.
	template <std::derived_from<System>... TSystems>
	struct IsSystemList<SystemList<TSystems...>> : std::true_type
	{
	};

	/// @brief A list of systems this system should update before.
	/// @tparam TType System type.
	template <std::derived_from<System> TType>
	struct SystemTraitPrecedes
	{
		/// @brief System type indices.
		static constexpr auto Hashes = std::array<entt::id_type, 0>{};
	};

	/// @brief A list of systems this system should update before.
	/// @tparam TType System type.
	template <std::derived_from<System> TType>
	requires requires { typename TType::Precedes; }
	struct SystemTraitPrecedes<TType>
	{
		/// @brief System type indices.
		static constexpr auto Hashes = TType::Precedes::Hashes;
		static_assert(IsSystemList<typename TType::Precedes>{});
	};

	/// @brief A list of systems this system should update after.
	/// @tparam TType System type.
	template <std::derived_from<System> TType>
	struct SystemTraitSucceeds
	{
		/// @brief System type indices.
		static constexpr auto Hashes = std::array<entt::id_type, 0>{};
	};

	/// @brief A list of systems this system should update after.
	/// @tparam TType System type.
	template <std::derived_from<System> TType>
	requires requires { typename TType::Succeed; }
	struct SystemTraitSucceeds<TType>
	{
		/// @brief System type indices.
		static constexpr auto Hashes = TType::Succeed::Hashes;
		static_assert(IsSystemList<typename TType::Succeed>{});
	};

	/// @brief Key to organize and identify system order.
	struct SystemKey
	{
		/// @brief System type hash.
		entt::id_type Type{};

		/// @brief Type hashes for systems this system should update before.
		std::span<const entt::id_type> Precedes{};

		/// @brief Type hashes for systems this system should update after.
		std::span<const entt::id_type> Succeeds{};

		/// @brief Create a system key for a specific type.
		/// @tparam TType System type.
		/// @return System key for the specified system type.
		template <std::derived_from<System> TType>
		[[nodiscard]] static constexpr auto Value() -> SystemKey
		{
			return SystemKey{
				.Type = entt::type_hash<TType>::value(),
				.Precedes = SystemTraitPrecedes<TType>::Hashes,
				.Succeeds = SystemTraitSucceeds<TType>::Hashes,
			};
		}
	};

	/// @brief Check if a system key is before another system key.
	/// @param lhs Left hand side system key.
	/// @param rhs Right hand side system key.
	/// @return @c true if @c lhs should sort before @c rhs, @c false otherwise.
	[[nodiscard]] auto operator<(const SystemKey& lhs, const SystemKey& rhs) -> bool;

	/// @brief A system with an ordered map of nested subsystems.
	class SystemGroup : public System
	{
	public:
		auto Update(EntityManager& entities) -> void override;

		/// @brief Create a system.
		/// @tparam TType System type.
		/// @tparam TArgs System constructor argument types.
		/// @param args System constructor arguments.
		/// @return A reference to the system.
		template <std::derived_from<System> TType, typename... TArgs>
		auto CreateSystem(TArgs&&... args) -> TType&
		{
			auto system = std::make_shared<TType>(std::forward<TArgs>(args)...);
			m_Systems.insert_or_assign(SystemKey::Value<TType>(), system);
			return *system;
		}

		/// @brief Destroy a system.
		/// @tparam TType System type.
		/// @return @c true if the system was destroyed, @c false otherwise.
		template <std::derived_from<System> TType>
		auto DestroySystem() -> bool
		{
			return m_Systems.erase(SystemKey::Value<TType>()) > 0;
		}

		/// @brief Check if a system exists.
		/// @tparam TType System type.
		/// @return @c true if the system exists, @c false otherwise.
		template <std::derived_from<System> TType>
		[[nodiscard]] auto HasSystem() const -> bool
		{
			return m_Systems.contains(SystemKey::Value<TType>());
		}

		/// @brief Get a system.
		/// @tparam TType system type.
		/// @return A reference to the system.
		template <std::derived_from<System> TType>
		[[nodiscard]] auto GetSystem() -> TType&
		{
			return static_cast<TType&>(*m_Systems.at(SystemKey::Value<TType>()));
		}

		/// @brief Get a system.
		/// @tparam TType system type.
		/// @return A reference to the system.
		template <std::derived_from<System> TType>
		[[nodiscard]] auto GetSystem() const -> const TType&
		{
			return static_cast<const TType&>(*m_Systems.at(SystemKey::Value<TType>()));
		}

	private:
		std::map<SystemKey, std::shared_ptr<System>> m_Systems{};
	};

	/// @brief Type of system group this system should update in.
	/// @tparam TType System type.
	template <std::derived_from<System> TType>
	requires requires { typename TType::UpdateIn; }
	using SystemTraitUpdateIn = typename TType::UpdateIn;

	/// @brief System manager organizing subsystems in a tree structure.
	class SystemManager : SystemGroup
	{
	public:
		using SystemGroup::Update;

		template <std::derived_from<System> TType, typename... TArgs>
		requires std::same_as<SystemTraitUpdateIn<TType>, SystemManager>
		auto CreateSystem(TArgs&&... args) -> TType&
		{
			return SystemGroup::CreateSystem<TType>(std::forward<TArgs>(args)...);
		}

		template <std::derived_from<System> TType, typename... TArgs>
		requires std::derived_from<SystemTraitUpdateIn<TType>, SystemGroup>
		auto CreateSystem(TArgs&&... args) -> TType&
		{
			using Group = SystemTraitUpdateIn<TType>;
			return GetSystem<Group>().template CreateSystem<TType>(std::forward<TArgs>(args)...);
		}

		template <std::derived_from<System> TType>
		requires std::same_as<SystemTraitUpdateIn<TType>, SystemManager>
		auto DestroySystem() -> bool
		{
			return SystemGroup::DestroySystem<TType>();
		}

		template <std::derived_from<System> TType>
		requires std::derived_from<SystemTraitUpdateIn<TType>, SystemGroup>
		auto DestroySystem() -> bool
		{
			using Group = SystemTraitUpdateIn<TType>;
			return HasSystem<Group>() && GetSystem<Group>().template DestroySystem<TType>();
		}

		template <std::derived_from<System> TType>
		requires std::same_as<SystemTraitUpdateIn<TType>, SystemManager>
		[[nodiscard]] auto HasSystem() const -> bool
		{
			return SystemGroup::HasSystem<TType>();
		}

		template <std::derived_from<System> TType>
		requires std::derived_from<SystemTraitUpdateIn<TType>, SystemGroup>
		[[nodiscard]] auto HasSystem() const -> bool
		{
			using Group = SystemTraitUpdateIn<TType>;
			return HasSystem<Group>() && GetSystem<Group>().template HasSystem<TType>();
		}

		template <std::derived_from<System> TType>
		requires std::same_as<SystemTraitUpdateIn<TType>, SystemManager>
		[[nodiscard]] auto GetSystem() -> TType&
		{
			return SystemGroup::GetSystem<TType>();
		}

		template <std::derived_from<System> TType>
		requires std::derived_from<SystemTraitUpdateIn<TType>, SystemGroup>
		[[nodiscard]] auto GetSystem() -> TType&
		{
			using Group = SystemTraitUpdateIn<TType>;
			return GetSystem<Group>().template GetSystem<TType>();
		}

		template <std::derived_from<System> TType>
		requires std::same_as<SystemTraitUpdateIn<TType>, SystemManager>
		[[nodiscard]] auto GetSystem() const -> const TType&
		{
			return SystemGroup::GetSystem<TType>();
		}

		template <std::derived_from<System> TType>
		requires std::derived_from<SystemTraitUpdateIn<TType>, SystemGroup>
		[[nodiscard]] auto GetSystem() const -> const TType&
		{
			using Group = SystemTraitUpdateIn<TType>;
			return GetSystem<Group>().template GetSystem<TType>();
		}
	};
} //namespace Star
