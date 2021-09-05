/**
 * @file Entity.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "Entity.h"

namespace re
{
	struct Traceresult
	{
		math::Vec3 end;
		bool bCollided;
	};

	bool Entity::IsEntityVisible(re::Entity* other) const
	{
		uintptr_t  traceFunction = 0x0048A310;
		Traceresult result{ {}, false };
		math::Vec3 start{ Head };
		math::Vec3 end{ other->Head };

		__asm
		{
			push 0; bSkipTags
			push 0; bCheckPlayers
			push this
			push end.z
			push end.y
			push end.x
			push start.z
			push start.y
			push start.x
			lea eax, [result]
			call traceFunction
			add esp, 36
		}

		return !result.bCollided;
	}

	bool Entity::IsAlive() const
	{
		return Health > 0 and Health <= 100;
	}
} // namespace re
