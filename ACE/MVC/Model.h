/**
 * @file Model.h
 * @brief The backbone of View containing all data.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once
#include "../ReClass/Entity.h"
#include "../Utility/Draw.h"
#include "Widgets.h"

namespace mvc
{
	typedef int(__cdecl* tGetEntityAtCrosshair)(); ///< Assault Cube function to trace entity at crosshair position

	class Model
	{
	public:
		Model();
		virtual ~Model() = default;
		/** @brief Initialize the model.
		 */
		bool Initialize();
		/** @brief Keep data and game modifications updated.
		 */
		void Execute();
		/** @brief Check initialization status.
		 */
		bool IsInitialized() const;
		/** @brief Get access to the local player's health.
		 */
		CheckSliderInt32& GetHealth();
		/** @brief Get access to the local player's armor.
		 */
		CheckSliderInt32& GetArmor();
		/** @brief Get access to the local player's ammunition.
		 */
		CheckSliderInt32& GetAmmunition();
		/** @brief Get access to the local player's jump status.
		 */
		Checkbox& GetJump();
		/** @brief Get access to the triggerbot data
		*/
		Checkbox& GetTriggerbot();
		/** @brief Get access to the no recoil data
		*/
		Patchbox& GetNoRecoil();
		/** @brief Get access to aimbot data
		 */
		Checkbox& GetAimbot();
		/** @brief Get access to ESP data
		 */
		Checkbox& GetESP();
		/** @brief Get access to the teleport data
		 */
		CheckSliderInt32& GetTeleport();
		/** @brief Get access to auto shoot
		 */
		Checkbox& GetAutoShoot();
		/** @brief Get the in-game view matrix
		 */
		float* GetViewMatrix() const;
	private:
		/** @brief Get the base address of Assault Cube.
		 */
		bool GetModuleBaseAddress();
		/** @brief Call all freezes
		 */
		void Freeze();
		/** @brief Freeze function for CheckSliders
		 */
		template<typename T>
		void Freeze(CheckSlider<T>& data)
		{
			if (data.checkbox.bEnabled)
			{
				data.Update();
			}
		}
		/** @brief Freeze function Freezebox
		 */
		void Freeze(Freezebox& data);
		/** @brief Triggerbot logic
		 */
		void Triggerbot() const;
		/** @brief Aimbot logic
		 */
		void Aimbot() const;
		/** @brief ESP drawing
		 */
		void ESP();
		/** @brief Teleport enemies
		 */
		void Teleport(float distance = 1.f);
		/** @brief Get number of players in-game
		 */
		int32_t GetNumberOfPlayers() const;
		/** @brief Get entity list
		 */
		re::EntityList* GetEntityList() const;
		/** @brief Get the game mode
		 */
		int32_t GetGameMode() const;
		/** @brief Check if in team game
		 */
		bool IsTeamGame(int32_t gameMode) const;
		/** @brief Check if entity is an enemy
		 */
		bool IsEnemy(re::Entity* entity) const;
	private:
		uintptr_t moduleBaseAddress; ///< Base address of Assault Cube executable.
		re::Entity* localPlayer; ///< Pointer to local player memory region.
		tGetEntityAtCrosshair GetEntityAtCrosshair; ///< Function pointer to `GetCrosshairEntity` function
		draw::Draw draw; ///< Drawing operations
		bool bInitialized; ///< Initialization status.
		CheckSliderInt32 health; ///< Local player health data.
		CheckSliderInt32 armor; ///< Local player armor data.
		CheckSliderInt32 ammunition; ///< Local player ammunition data.
		Freezebox jump; ///< Local player jump status.
		Freezebox triggerbot; ///< Triggerbot
		Patchbox noRecoil; ///< No recoil and no spread
		Freezebox aimbot; ///< Aimbot
		Freezebox esp; ///< ESP
		CheckSliderInt32 teleport; ///< Teleport
		Freezebox autoShoot; ///< Automatic shooting
	};
} // namespace mvc
