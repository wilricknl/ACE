/**
 * @file Widgets.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "../ImGui/imgui.h"
#include "Widgets.h"

namespace mvc
{
	/**
	 * @pre The function should be called within `ImGui::BeginTable`. For optimal display use 2 columns.
	 *
	 * @param data The data class used displaying and updating the slider
	 */
	void ShowCheckSliderInt32(CheckSliderInt32& data)
	{
		ImGui::TableNextColumn();
		ImGui::Checkbox(data.checkbox.label.c_str(), &data.checkbox.bEnabled);
		ImGui::SameLine();
		ImGui::TableNextColumn();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::SliderInt(
			data.slider.label.c_str(), 
			&data.slider.value, 
			data.slider.GetMinimum(), 
			data.slider.GetMaximum(), 
			"%d", 
			ImGuiSliderFlags_AlwaysClamp);
		if (ImGui::IsItemEdited())
		{
			data.slider.Update();
		}
	}
} // namespace mvc
