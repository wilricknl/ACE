/**
 * @file Memory.h
 * @brief Functions to modify and interact with process memory
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once

namespace memory
{
	/** @brief Copy @p size bytes from @p source to @p destination
	 */
	bool Patch(BYTE* source, BYTE* destination, unsigned int size);

	/** @brief Nop @p size bytes at @p destination
	 */
	bool Nop(BYTE* destination, unsigned int size);

	/** @brief Jump from @p hook to @p jump
	 */
	bool Detour32(BYTE* hook, BYTE* jump, const uintptr_t length);

	/** @brief Create a trampoline hook from @p hook to @p jump
	 */
	BYTE* TrampolineHook32(BYTE* hook, BYTE* jump, const uintptr_t length);
} // namespace memory
