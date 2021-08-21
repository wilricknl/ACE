/**
 * @file Model.h
 * @brief The backbone of View containing all data.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once
#include "../ReClass/Entity.h"
#include "Widgets.h"

namespace mvc
{
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
				data.slider.Update();
			}
		}
	private:
		uintptr_t moduleBaseAddress; ///< Base address of Assault Cube executable.
		re::Entity* localPlayer; ///< Pointer to local player memory region.
		bool bInitialized; ///< Initialization status.
		CheckSliderInt32 health; ///< Local player health data.
		CheckSliderInt32 armor; ///< Local player armor data.
		CheckSliderInt32 ammunition; ///< Local player ammunition data.
		Checkbox jump; ///< Local player jump status.
	};
} // namespace mvc