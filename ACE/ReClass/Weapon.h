/**
 * @file Entity.h
 * @brief Reversed weapon class.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once
#include "Padding.h"

namespace re
{
	class Weapon
	{
	public:
		union {
			DEFINE_MEMBER_N(int32_t*, Clip, 0x0014);
		};
	};
} // namespace re

