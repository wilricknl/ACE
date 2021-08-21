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

	/**
	 * @brief Slider is a generic class to store data for ImGui sliders
	 */
	template<typename T>
	class Slider
	{
	public:
		Slider(std::function<void(T)> save, T minimum, T maximum, std::string label, T value = (T)100)
			: save(save), minimum(minimum), maximum(maximum), label(label), value(value)
		{}

		/**
		 * @brief Send `value` elsewhere in the program using `save`
		 */
		void Update()
		{
			save(value);
		}

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
		std::function<void(T)> save; ///< A function to send `value` to elsewhere in the program
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
		CheckSlider(std::string label, T minimum, T maximum, std::function<void(T)> save, T value = (T)100)
			: checkbox(label), slider(save, minimum, maximum, "##" + label, value)
		{}
		
		Checkbox checkbox; ///< Checkbox data
		Slider<T> slider; ///< Slider data
	};

	typedef CheckSlider<int32_t> CheckSliderInt32; ///< Int32 Checkslider

	/**
	 * @brief Display a CheckSliderInt32
	 */
	void ShowCheckSliderInt32(CheckSliderInt32& data);
} // namespace mvc
