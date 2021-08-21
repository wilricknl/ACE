/**
 * @file Entity.h
 * @brief Reversed entity class.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once
#include "Padding.h"
#include "Weapon.h"

namespace re
{
	class Entity
	{
	public:
		union {
			DEFINE_MEMBER_N(bool, bJump, 0x0069);
			DEFINE_MEMBER_N(int32_t, Health, 0x00F8);
			DEFINE_MEMBER_N(int32_t, Armor, 0x00FC);
			DEFINE_MEMBER_N(Weapon*, Weapon, 0x0374);
		};
	};
} // namespace re
