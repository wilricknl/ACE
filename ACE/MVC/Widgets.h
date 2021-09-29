/**
 * @file Widgets.h
 * @brief Custom ImGui widgets and data classes.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once

namespace mvc
{
	/**
	 * @brief Checkbox holds data required for `ImGui::Checkbox()`
	 */
	class Checkbox
	{
	public:
		Checkbox(std::string label)
			: label(std::move(label))
		{}
		
		bool bEnabled = false; ///< Status of check box (`true` is enabled, `false` disabled)
		const std::string label; ///< Label to be displayed next to checkbox
	};

	/** @brief Display a Checkbox
	 */
	void ShowCheckbox(Checkbox& data);

	/**
	 * @brief Freezebox continuously writes to memory when enabled.
	 */
	class Freezebox : public Checkbox
	{
	public:
		Freezebox(std::string label, std::function<void(void)> freeze)
			: Checkbox(std::move(label)), freeze(std::move(freeze))
		{}

		const std::function<void(void)> freeze; ///< Custom freeze action.
	};

	/**
	 * @brief Patchbox changes memory upon enabling or disabling.
	 */
	class Patchbox : public Checkbox
	{
	public:
		Patchbox(std::string label, std::function<void(void)> patch, std::function<void(void)> restore)
			: Checkbox(std::move(label)), patch(std::move(patch)), restore(std::move(restore))
		{}

		/**
		 * @brief Patch if `bEnabled = true`, else restore the patch.
		 */
		void Toggle()
		{
			if (bEnabled)
			{
				patch();
			}
			else
			{
				restore();
			}
		}
	private:
		const std::function<void(void)> patch; ///< Custom patch function.
		const std::function<void(void)> restore; ///< Custom restore function.
	};

	/** @brief Display a Patchbox
	 */
	void ShowPatchbox(Patchbox& data);

	/**
	 * @brief Slider is a generic class to store data for ImGui sliders
	 */
	template<typename T>
	class Slider
	{
	public:
		Slider(T minimum, T maximum, std::string label, T value = (T)100)
			: minimum(minimum), maximum(maximum), value(value), label(label)
		{}

		/**
		 * @brief Get the minimum
		 * @return `minimum`
		 */
		T GetMinimum() { return minimum; }
		
		/**
		 * @brief Get the maximum
		 * @return `maximum`
		 */
		T GetMaximum() { return maximum; }
	private:
		T minimum; ///< The minimum value the slider can have
		T maximum; ///< The maximum value the slider can have
	public:
		T value; ///< The current value of the slider
		const std::string label; ///< The label of the slider
	};

	/**
	 * @brief Generic class to combine a checkbox with a slider.
	 */
	template<typename T>
	class CheckSlider
	{
	public:
		CheckSlider(std::string label, T minimum, T maximum, std::function<void(T)> action, T value = (T)100)
			: checkbox(label), slider(minimum, maximum, "##" + label, value), action(std::move(action))
		{}

		/**
		 * @brief Send `value` elsewhere in the program using `save`
		 */
		void Update()
		{
			action(slider.value);
		}

		Checkbox checkbox; ///< Checkbox data
		Slider<T> slider; ///< Slider data
	private:
		std::function<void(T)> action; ///< A function to send `slider.value` to elsewhere in the program
	};

	typedef CheckSlider<int32_t> CheckSliderInt32; ///< Int32 Checkslider

	/** @brief Display a CheckSliderInt32
	 */
	void ShowCheckSliderInt32(CheckSliderInt32& data);
} // namespace mvc
