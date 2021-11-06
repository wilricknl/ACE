/**
 * @file View.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "../version.h"
#include "../ImGui/imgui_impl_opengl2.h"
#include "../ImGui/imgui_impl_win32.h"
#include "Widgets.h"
#include "View.h"

namespace mvc
{
	View::View(Model& model)
		: model(model)
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

		if (bDemo)
		{
			ImGui::ShowDemoWindow(&bDemo);
		}
		
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

		if (ImGui::Begin(("Assault Cube Enhancement (" + version::version + ")").c_str(), bShow, window_flags))
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
				ImGui::MenuItem("Demo", nullptr, &bDemo);
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
			ShowAimAssistTab();
			ShowESPTab();
			ImGui::EndTabBar(); // Tabs
		} 
	}

	void View::ShowGeneralTab()
	{
		if (ImGui::BeginTabItem("General"))
		{
			if (ImGui::BeginTable("General", 2, ImGuiTableFlags_Borders))
			{
				ImGui::TableSetupColumn("Freeze");
				ImGui::TableSetupColumn("Amount");
				ImGui::TableHeadersRow();

				ShowCheckSliderInt32(model.GetHealth());
				ShowCheckSliderInt32(model.GetArmor());
				ShowCheckSliderInt32(model.GetAmmunition());
				ShowCheckbox(model.GetJump());

				ImGui::EndTable(); // General
			}
			
			ShowLogo(true);
			
			ImGui::EndTabItem(); // General
		}
	}

	void View::ShowAimAssistTab()
	{
		if (ImGui::BeginTabItem("Aim Assist"))
		{
			if (ImGui::BeginTable("Aim Assist", 1, ImGuiTableFlags_Borders))
			{
				ImGui::TableSetupColumn("Assistance");
				ImGui::TableHeadersRow();

				ShowCheckbox(model.GetTriggerbot());
				ShowPatchbox(model.GetNoRecoil());
				ShowCheckbox(model.GetAimbot());
				ShowCheckbox(model.GetAutoShoot());

				ImGui::EndTable(); // Aim Assist
			}
			ImGui::EndTabItem(); // Aim Assist
		}
	}

	void View::ShowESPTab()
	{
		if (ImGui::BeginTabItem("ESP"))
		{
			if (ImGui::BeginTable("ESP Table", 2, ImGuiTableFlags_Borders))
			{
				ImGui::TableSetupColumn("Toggle");
				ImGui::TableSetupColumn("Amount");
				ImGui::TableHeadersRow();

				ShowCheckbox(model.GetESP());
				ImGui::TableNextColumn();
				ShowCheckSliderInt32(model.GetTeleport());

				ImGui::EndTable(); // ESP Table
			}
			ImGui::EndTabItem(); // ESP
		}
	}

	/**
	 * @param bCentered Center text if `true`, else align left.
	 */
	void View::ShowLogo(bool bCentered)
	{
		const std::string logo{
				"          _ _      _      _          _ \n"
				"__      _(_) |_ __(_) ___| | ___ __ | |\n"
				"\\ \\ /\\ / / | | '__| |/ __| |/ / '_ \\| |\n"
				" \\ V  V /| | | |  | | (__|   <| | | | |\n"
				"  \\_/\\_/ |_|_|_|  |_|\\___|_|\\_\\_| |_|_|\n"
				"                                       \n"
				"   https://github.com/wilricknl/ACE/   "};
		// Idea taken from https://stackoverflow.com/a/67855985
		if (bCentered)
		{
			auto windowWidth = ImGui::GetWindowSize().x;
			auto textWidth = ImGui::CalcTextSize(logo.substr(0, 39).c_str()).x;
			ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		}
		ImGui::Text(logo.c_str());
	}
} // namespace mvc
