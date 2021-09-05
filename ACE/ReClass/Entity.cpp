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
		uintptr_t localAddress{ (uintptr_t)this };
		Traceresult result{ {}, false };
		math::Vec3 start{ Head };
		math::Vec3 end{ other->Head };

		__asm
		{
			push 0
			push 0
			push localAddress
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
} // namespace re
