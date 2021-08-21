/**
 * @file Controller.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "../ImGui/imgui.h"
#include "../Memory/Memory.h"
#include "Controller.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace mvc
{
	Controller& Controller::GetController()
	{
		static Controller controller;
		return controller;
	}

	/**
	 * Initialize ImGui and perform the hooks on Assault Cube.
	 *
	 * @return `true` if initialization succeeded, else `false`.
	 */
	bool Controller::Initialize()
	{
		HWND hWnd = FindWindow(nullptr, TEXT("AssaultCube"));
		if (not hWnd or not GetSDLShowCursor(SDLShowCursor))
		{
			return false;
		}
		
		view.Initialize(hWnd);
		Hook(hWnd);
		return true;
	}

	void Controller::Execute()
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			bShowWindow = !bShowWindow;
		}
		
		if (bShowWindow)
		{
			SDLShowCursor(1);
			bShowWindow = view.Show();
		}
		else
		{
			SDLShowCursor(0);
		}

		model.Execute();
		
		if (view.IsEject() || GetAsyncKeyState(VK_END) & 1)
		{
			Shutdown();
			bFinished = true;
		}
	}

	void Controller::Shutdown()
	{
		Unhook();
		view.Shutdown();
		SDLShowCursor(0);
	}

	/**
	 * @return Function pointer to the gateway.
	 */
	twglSwapBuffers Controller::GetGateway() const
	{
		return gateway;
	}

	/**
	 * @return A `WNDPROC` to Assault Cube's window.
	 */
	WNDPROC Controller::GetOriginalWindowProcedure() const
	{
		return originalWindowProcedure;
	}

	/**
	 * @return `true` if window is shown, else `false`.
	 */
	bool Controller::IsShowWindow() const
	{
		return bShowWindow;
	}
	
	/**
	 * @return `true` if program is finished, else `false`.
	 */
	bool Controller::IsFinished() const
	{
		return bFinished;
	}

	Controller::Controller()
		: gateway(nullptr), originalWindowProcedure(nullptr), SDLShowCursor(nullptr),
		view(model),bShowWindow(false), bFinished(false)
	{}

	/**
	 * @param hWnd A handle to Assault Cube's window.
	 */
	void Controller::Hook(HWND hWnd)
	{
		HookSwapBuffers();
		HookWindowProcedure(hWnd);
	}

	void Controller::HookSwapBuffers()
	{
		gateway = (twglSwapBuffers)memory::TrampolineHook32(
			(BYTE*)GetSwapBuffers(), (BYTE*)CustomWglSwapBuffers, 5);
	}

	/**
	 * @param hWnd A handle to Assault Cube's window.
	 */
	void Controller::HookWindowProcedure(HWND hWnd)
	{
		originalWindowProcedure = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)CustomWndProc);
	}

	void Controller::Unhook() const
	{
		UnhookSwapBuffers();
		UnhookWindowProcedure();
	}

	void Controller::UnhookSwapBuffers() const
	{
		memory::Patch((BYTE*)gateway, (BYTE*)GetSwapBuffers(), 5);
	}

	void Controller::UnhookWindowProcedure() const
	{
		SetWindowLongPtr(FindWindowA(nullptr, "AssaultCube"), GWLP_WNDPROC,
			(LONG_PTR)originalWindowProcedure);
	}

	/**
	 * @return A function pointer to OpenGL `wglSwapBuffers`.
	 */
	twglSwapBuffers GetSwapBuffers()
	{
		return (twglSwapBuffers)GetProcAddress(
			GetModuleHandle(TEXT("opengl32.dll")), "wglSwapBuffers");
	}

	/**
	 * @param outSDL_ShowCursor Return the found function pointer to `SDL_ShowCursor`.
	 *
	 * @return `true` if `SDL_ShowCursor` is found, else `false`.
	 */
	bool GetSDLShowCursor(tSDL_ShowCursor& outSDL_ShowCursor)
	{
		const auto showCursorAddress = (uintptr_t)GetProcAddress(GetModuleHandle(L"SDL.dll"), "SDL_ShowCursor");
		if (showCursorAddress)
		{
			outSDL_ShowCursor = (tSDL_ShowCursor)showCursorAddress;
			return true;
		}
		return false;
	}

	/**
	 * @param hDc Handle to OpenGL device context.
	 * 
	 * @return `TRUE` if succeeded, else `FALSE`.
	 */
	BOOL __stdcall CustomWglSwapBuffers(HDC hDc)
	{
		Controller& controller = Controller::GetController();
		controller.Execute();
		return controller.GetGateway()(hDc);
	}

	/**
	 * @see https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-callwindowproca
	 */
	LRESULT __stdcall CustomWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Controller& controller = Controller::GetController();
		if (controller.IsShowWindow())
		{
			if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			{
				return true;
			}

			ImGuiIO& io = ImGui::GetIO();
			switch (uMsg)
			{
			case WM_LBUTTONDOWN:
				io.MouseDown[1] = !io.MouseDown[0];
				return 0;
			case WM_RBUTTONDOWN:
				io.MouseDown[1] = !io.MouseDown[1];
				return 0;
			case WM_MBUTTONDOWN:
				io.MouseDown[2] = !io.MouseDown[2];
				return 0;
			case WM_MOUSEWHEEL:
				return 0;
			case WM_MOUSEMOVE:
				io.MousePos.x = (signed short)(lParam);
				io.MousePos.y = (signed short)(lParam >> 16);
				return 0;
			}
		}
		
		return CallWindowProc(controller.GetOriginalWindowProcedure(),
			hWnd, uMsg, wParam, lParam);
	}
} // namespace mvc
