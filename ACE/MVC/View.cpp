/**
 * @file View.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"

#include "../ImGui/imgui_impl_opengl2.h"
#include "../ImGui/imgui_impl_win32.h"
#include "View.h"

namespace mvc
{
	View::View()
	{
	}

	/**
	 * @param hWnd A handle to Assault Cube's window.
	 */
	void View::Initialize(HWND hWnd)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplOpenGL2_Init();
	}

	/**
	 * @return `true` if interface is still open, `false` if interface is closed. 
	 */
	bool View::Show()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		bool bShowDemo;
		ImGui::ShowDemoWindow(&bShowDemo);

		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		return bShowDemo;
	}

	void View::Shutdown()
	{
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
} // namespace mvc
