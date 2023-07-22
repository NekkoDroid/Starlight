#pragma once

#include <entt/entity/registry.hpp>

namespace Star
{
	/// @brief Entity handle.
	class Entity
	{
	public:
		/// @brief Underlying entity handle type.
		using entity_type = entt::id_type; // NOLINT(readability-identifier-naming)

		/// @brief Construct an entity from a specific handle.
		/// @param handle Underlying entity handle.
		constexpr explicit Entity(entity_type handle = entt::null) :
			m_Handle{handle}
		{
		}

		/// @brief Get the underlying entity handle.
		/// @return Underlying entity handle.
		[[nodiscard]] constexpr explicit operator entity_type() const
		{
			return m_Handle;
		}

		/// @brief Check if the entity handle is valid.
		/// @return @c true if valid, @c false otherwise.
		[[nodiscard]] constexpr explicit operator bool() const
		{
			return *this != Entity{};
		}

		/// @brief 3-way comparison operator.
		/// @param lhs Left comparison instance.
		/// @param rhs Right comparison instance.
		/// @return Relative ordering of @c lhs compared to @c rhs.
		[[nodiscard]] friend auto constexpr operator<=>(Entity lhs, Entity rhs) = default;

	private:
		entity_type m_Handle{};
	};

	template <typename, typename>
	class EntityView;

	/// @brief A list of component types.
	/// @tparam TComponents Component types.
	template <typename... TComponents>
	class ComponentList
	{
	};

	/// @brief Entity and component manager.
	class EntityManager : entt::basic_registry<Entity>
	{
	public:
		/// @brief Storage type used for a specific component.
		/// @tparam TType Component type.
		template <typename TType>
		using Storage = storage_for_type<TType>;

		/// @brief Create a new entity.
		/// @return A valid entity handle.
		[[nodiscard]] auto Create() -> Entity;

		/// @brief Destroy an entity.
		/// @param entity A valid entity handle.
		auto Destroy(Entity entity) -> void;

		/// @brief Check if an entity is valid.
		/// @param entity An entity handle.
		/// @return @c true if the entity is valid, @c false otherwise.
		[[nodiscard]] auto Valid(Entity entity) const -> bool;

		/// @brief Create a component on an entity.
		/// @tparam TType Component type.
		/// @tparam TArgs Component constructor argument types.
		/// @param entity Valid entity handle.
		/// @param args Component constructor arguments.
		/// @return A reference to the created component.
		template <typename TType, typename... TArgs>
		auto CreateComponent(Entity entity, TArgs&&... args) -> TType&
		{
			return emplace_or_replace<TType>(entity, std::forward<TArgs>(args)...);
		}

		/// @brief Destroy a component on an entity.
		/// @tparam TType Component type.
		/// @param entity Valid entity handle.
		/// @return @c true if the component was destroyed, @c false otherwise.
		template <typename TType>
		auto DestroyComponent(Entity entity) -> bool
		{
			return remove<TType>(entity) > 0;
		}

		/// @brief Check if a component exists on an entity.
		/// @tparam TType Component type.
		/// @param entity Valid entity handle.
		/// @return @c true if the component exists, @c false otherwise.
		template <typename TType>
		[[nodiscard]] auto HasComponent(Entity entity) const -> bool
		{
			return all_of<TType>(entity);
		}

		/// @brief Get a component on an entity.
		/// @tparam TType Component type.
		/// @param entity Valid entity handle.
		/// @return A reference to the component.
		template <typename TType>
		[[nodiscard]] auto GetComponent(Entity entity) -> TType&
		{
			return get<TType>(entity);
		}

		/// @brief Get a component on an entity.
		/// @tparam TType Component type.
		/// @param entity Valid entity handle.
		/// @return A reference to the component.
		template <typename TType>
		[[nodiscard]] auto GetComponent(Entity entity) const -> const TType&
		{
			return get<TType>(entity);
		}

		/// @brief Clear a component on all entities.
		/// @tparam TType Component type.
		template <typename TType>
		auto ClearComponent() -> void
		{
			clear<TType>();
		}

		/// @brief Create a singleton.
		/// @tparam TType Singleton type.
		/// @tparam TArgs Singleton constructor argument types.
		/// @param args Singleton constructor arguments.
		/// @return A reference to the created singleton.
		template <typename TType, typename... TArgs>
		auto CreateSingleton(TArgs&&... args) -> TType&
		{
			return ctx().insert_or_assign(TType(std::forward<TArgs>(args)...));
		}

		/// @brief Destroy a singleton.
		/// @tparam TType Singleton type.
		/// @return @c true if the singleton was destroyed, @c false otherwise.
		template <typename TType>
		auto DestroySingleton() -> bool
		{
			return ctx().erase<TType>();
		}

		/// @brief Check if a singleton exists.
		/// @tparam TType Singleton type.
		/// @return @c true if the singleton exists, @c false otherwise.
		template <typename TType>
		[[nodiscard]] auto HasSingleton() const -> bool
		{
			return ctx().contains<TType>();
		}

		/// @brief Get a singleton.
		/// @tparam TType Singleton type.
		/// @return A reference to the singleton.
		template <typename TType>
		[[nodiscard]] auto GetSingleton() -> TType&
		{
			return ctx().get<TType>();
		}

		/// @brief Get a singleton.
		/// @tparam TType Singleton type.
		/// @return A reference to the singleton.
		template <typename TType>
		[[nodiscard]] auto GetSingleton() const -> const TType&
		{
			return ctx().get<TType>();
		}

		/// @brief Create a view on entities with specific components.
		/// @tparam TIncludes Component types to include in the view.
		/// @tparam TExcludes Component types to exclude from the view.
		/// @param includes Component types to include in the view.
		/// @param excludes Component types to exclude from the view.
		/// @return A view on the selected entities.
		template <typename... TIncludes, typename... TExcludes>
		[[nodiscard]] auto View(
			[[maybe_unused]] ComponentList<TIncludes...> includes,
			[[maybe_unused]] ComponentList<TExcludes...> excludes
		) -> EntityView<ComponentList<TIncludes...>, ComponentList<TExcludes...>>
		{
			return {view<TIncludes...>(entt::exclude<TExcludes...>)};
		}

		/// @brief Create a view on entities with specific components.
		/// @tparam TIncludes Component types to include in the view.
		/// @tparam TExcludes Component types to exclude from the view.
		/// @param includes Component types to include in the view.
		/// @param excludes Component types to exclude from the view.
		/// @return A view on the selected entities.
		template <typename... TIncludes, typename... TExcludes>
		[[nodiscard]] auto View(
			[[maybe_unused]] ComponentList<TIncludes...> includes,
			[[maybe_unused]] ComponentList<TExcludes...> excludes
		) const -> EntityView<ComponentList<const TIncludes...>, ComponentList<const TExcludes...>>
		{
			return {view<TIncludes...>(entt::exclude<TExcludes...>)};
		}
	};

	/// @brief A view on entities with certain components.
	/// @tparam TIncludes Component types to include in the view.
	/// @tparam TExcludes Component types to exclude in the view.
	template <typename... TIncludes, typename... TExcludes>
	class EntityView<ComponentList<TIncludes...>, ComponentList<TExcludes...>>
	{
	public:
		/// @brief Component list of types included in the view.
		using Includes = ComponentList<TIncludes...>;

		/// @brief Component list of types excluded in the view.
		using Excludes = ComponentList<TExcludes...>;

		/// @brief Construct a new entity view.
		/// @tparam TArgs Constructor argument types.
		/// @param args Constructor arguments.
		template <typename... TArgs>
		EntityView(TArgs&&... args) :
			m_View{std::forward<TArgs>(args)...}
		{
		}

		/// @brief Check if the view handle is valid.
		/// @return @c true if valid, @c false otherwise.
		[[nodiscard]] explicit operator bool() const
		{
			return static_cast<bool>(m_View);
		}

		/// @brief Get an iterator for the start of the view.
		/// @return Iterator to the first entity.
		[[nodiscard]] auto begin() const // NOLINT(readability-identifier-naming)
		{
			return m_View.begin();
		}

		/// @brief Get an iterator for the end of the view.
		/// @return Iterator past the last entity.
		[[nodiscard]] auto end() const // NOLINT(readability-identifier-naming)
		{
			return m_View.end();
		}

		/// @brief Get a component on an entity.
		/// @tparam TType Component type.
		/// @param entity Valid entity handle.
		/// @return A reference to the component.
		template <typename TType>
		[[nodiscard]] auto Get(Entity entity) const -> decltype(auto)
		{
			return m_View.template get<TType>(entity);
		}

		/// @brief Check if an entity is contained in the view.
		/// @param entity Valid entity handle.
		/// @return @c true if the entity is contained, @c false otherwise.
		[[nodiscard]] auto Contains(Entity entity) const -> bool
		{
			return m_View.contains(entity);
		}

	private:
		entt::basic_view<
			entt::get_t<EntityManager::Storage<TIncludes>...>,
			entt::exclude_t<EntityManager::Storage<TExcludes>...>>
			m_View{};
	};
} //namespace Star
