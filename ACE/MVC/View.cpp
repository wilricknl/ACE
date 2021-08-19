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

		bool bShow = true;
		ShowWindow(&bShow);

		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		return bShow;
	}

	void View::Shutdown()
	{
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	/**
	 * @return `true` if program should eject and exit, else `false`.
	 */
	bool View::IsEject() const
	{
		return bEject;
	}

	/**
	 * @param bShow Out boolean to store if window should still be shown `true`, or not `false`.
	 */
	void View::ShowWindow(bool* bShow)
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
		ImGui::SetNextWindowPos(ImVec2(50, 20), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Assault Cube Enhancement", bShow, window_flags))
		{
			ShowMenuBar(bShow);
			ShowTabs();
		}
		ImGui::End();
	}

	/**
	 * @param bShow Out boolean to store if window should still be shown `true`, or not `false`.
	 */
	void View::ShowMenuBar(bool* bShow)
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("Eject", nullptr, &bEject);

				if (ImGui::MenuItem("Close", nullptr))
				{
					*bShow = !*bShow;
				}
				
				ImGui::EndMenu(); // File
			}
			ImGui::EndMenuBar();
		}
	}

	void View::ShowTabs()
	{
		if (ImGui::BeginTabBar("Tabs", ImGuiTabBarFlags_None))
		{
			ShowGeneralTab();
			ImGui::EndTabBar(); // Tabs
		} 
	}

	void View::ShowGeneralTab()
	{
		if (ImGui::BeginTabItem("General"))
		{
			ImGui::EndTabItem(); // General
		}
	}
} // namespace mvc
