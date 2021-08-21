/**
 * @file Memory.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "Memory.h"

namespace memory
{
	/**
	 * Copy @p size bytes from @p destination to @p source. 
	 *
	 * @pre Destination is at least @p size in length.
	 *
	 * @param destination The address to which the bytes will be copied.
	 * @param source The address from which the bytes will be copied.
	 * @param size The number of bytes that will be copied.
	 *
	 * @return `true` if patch succeeded, else `false`.
	 */
	bool Patch(BYTE* source, BYTE* destination, unsigned int size)
	{
		DWORD oldProtection;
		if (VirtualProtect(destination, size, PAGE_EXECUTE_READWRITE, &oldProtection))
		{
			memcpy(destination, source, size);
			return VirtualProtect(destination, size, oldProtection, &oldProtection) != 0;
		}
		return false;
	}

	/**
	 * The relative address between @p hook and @p jump gets calculated. Then
	 * a jump to this relative address will be written at the location of @p hook.
	 * 
	 * @pre The detour requires 5 bytes to succeed, exceeding bytes get NOPed. 
	 *
	 * @param hook Address where the detour will be written.
	 * @param jump Address of location where program should continue.
	 * @param length Number of bytes that need to be overwritten.
	 *
	 * @return `true` if detour succeeded, else `false`.
	 */
	bool Detour32(BYTE* hook, BYTE* jump, const uintptr_t length)
	{
		if (length < 5)
		{
			return false;
		}

		DWORD oldProtection;
		if (VirtualProtect(hook, length, PAGE_EXECUTE_READWRITE, &oldProtection))
		{
			if (length > 5)
			{
				memset((void*)(hook + 5), 0x90, length - 5);
			}

			uintptr_t relativeAddress = jump - hook - 5;
			*hook = 0xE9;
			*(uintptr_t*)(hook + 1) = relativeAddress;

			return VirtualProtect(hook, length, oldProtection, &oldProtection) != 0;
		}
		
		return false;
	}

	/**
	 * The trampoline hook writes a jump to a custom function at a hook address. 
	 * Next our custom function gets executed followed by a gateway. The gateway
	 * executes the bytes stolen by the jump. Now that the program is restored, it
	 * will continue right after the jump location.
	 *
	 * For more information check the comments in the definition and refer
	 * @ref https://guidedhacking.com/threads/x86-trampoline-hook-source-code-swapbuffers-hook.14414/
	 * 
	 * @pre @p hook and @p jump must have same function signature and @p length 
	 * should be at least 5 bytes.
	 *
	 * @param hook Address of the function that will be hooked.
	 * @param jump Custom function to which @p hook will jump.
	 * @param length Number of bytes that need to be overwritten.
	 *
	 * @return Address to the gateway if hook succeeded, else `nullptr`.
	 */
	BYTE* TrampolineHook32(BYTE* hook, BYTE* jump, const uintptr_t length)
	{
		if (length < 5)
		{
			return nullptr;
		}

		// Allocate the gateway
		auto* gateway = static_cast<BYTE*>(VirtualAlloc(nullptr, length + 5, 
			MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
		if (gateway)
		{
			// Copy bytes at hook address to gateway
			memcpy_s(gateway, length, hook, length);

			// Calculate relative address from gateway to right after the hook address.
			// This where the program will continue after the custom function and
			// gateway are done.
			uintptr_t relativeAddress = hook - gateway - 5;

			// Write the jump to this location at the end of the gateway.
			*(gateway + length) = 0xE9;
			*(uintptr_t*)((uintptr_t)gateway + length + 1) = relativeAddress;

			// Write the jump to our custom function at the hook address
			if (Detour32(hook, jump, length))
			{
				// Return the address of the gateway, such that the custom function
				// can use it.
				return gateway;
			}
			// TODO: If this fails, there is a memory leak of gateway.
		}

		return nullptr;
	}
} // namespace memory