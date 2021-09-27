/**
 * @file Entity.h
 * @brief Reversed entity class.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once
#include "Padding.h"
#include "../Utility/Vec.h"
#include "Weapon.h"

namespace re
{
	/**
	 * @brief Reversed entity class of Assault Cube
	 */
	class Entity
	{
	public:
		union {
			DEFINE_MEMBER_N(math::Vec3, Head, 0x0004);
			DEFINE_MEMBER_N(math::Vec3, Position, 0x0034);
			DEFINE_MEMBER_N(math::Vec3, Angle, 0x0040);
			DEFINE_MEMBER_N(bool, bJump, 0x0069);
			DEFINE_MEMBER_N(int32_t, Health, 0x00F8);
			DEFINE_MEMBER_N(int32_t, Armor, 0x00FC);
			DEFINE_MEMBER_N(bool, bShoot, 0x0224);
			DEFINE_MEMBER_N(char, Name, 0x0225);
			DEFINE_MEMBER_N(int32_t, Team, 0x032C);
			DEFINE_MEMBER_N(Weapon*, Weapon, 0x0374);
		};

		/** @brief Check if @p other is visible
		 */
		bool IsEntityVisible(re::Entity* other) const;
		/** @brief Check if player is still alive
		 */
		bool IsAlive() const;
	};

	/**
	 * @brief Reversed entity list structure of Assault Cube
	 */
	class EntityList
	{
	public:
		static constexpr int MAX_ENTITIES{ 32 }; ///< The maximum number of entities
		Entity* entities[MAX_ENTITIES]; ///< The entity array
	};
} // namespace re
