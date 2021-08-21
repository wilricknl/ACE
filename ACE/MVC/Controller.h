/**
 * @file Controller.h
 * @brief Control of the program's life cycle.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once
#include "Model.h"
#include "View.h"

namespace mvc
{
	typedef BOOL(__stdcall* twglSwapBuffers)(HDC hDc); ///< `wglSwapBuffers` function signature.
	typedef int(__cdecl* tSDL_ShowCursor)(int); ///< `SDL_ShowCursor` function signature.

	/**
	 * @brief Controller takes care of the program's initialization, execution, and shutdown.
	 */
	class Controller
	{
	public:
		~Controller() = default;
		Controller(const Controller & controller) = delete;
		Controller(Controller && controller) = delete;
		Controller& operator=(const Controller & controller) = delete;
		Controller& operator=(Controller && controller) = delete;

		/** @brief Get access to the only instance of Controller.
		 */
		static Controller& GetController();
		/** @brief Hook Assault Cube and initialize ImGui.
		 */
		bool Initialize();
		/** @brief Handle input and update both the model and gui.
		 */
		void Execute();
		/** @brief Unhook from Assault Cube and clean up changes.
		 */
		void Shutdown();
		/** @brief Get a pointer to the gateway.
		 */
		twglSwapBuffers GetGateway() const;
		/** @brief Get callback function to Assault Cube window.
		 */
		WNDPROC GetOriginalWindowProcedure() const;
		/** @brief Check if ImGui window is shown.
		 */
		bool IsShowWindow() const;
		/** @brief Check if the user wants to quit.
		 */
		bool IsFinished() const;
	protected:
		Controller();
	private:
		/** @brief Execute all hooks.
		 */
		void Hook(HWND hWnd);
		/** @brief Hook OpenGL `wglSwapBuffers`.
		 */
		void HookSwapBuffers();
		/** @brief Hook the Assault Cube window.
		 */
		void HookWindowProcedure(HWND hWnd);
		/** @brief Restore all hooks.
		 */
		void Unhook() const;
		/** @brief Restore  OpenGL `wglSwapBuffers` to execute normally.
		 */
		void UnhookSwapBuffers() const;
		/** @brief Restore the Window Procedure.
		 */
		void UnhookWindowProcedure() const;
	private:
		twglSwapBuffers gateway; ///< Pointer to gateway for trampoline hook.
		WNDPROC originalWindowProcedure; ///< Pointer to Assault Cube's Window Procedure.
		tSDL_ShowCursor SDLShowCursor; ///< Pointer to `SDL_ShowCursor` function.

		Model model; ///< The data management of the program.
		View view; ///< The GUI of the program.

		bool bShowWindow; ///< `bool` to keep track if the view is shown (`true`) or not (`false`).
		bool bFinished; ///< `bool` to keep track if the program can quit (`true`) or not (`false`).
	};

	/** @brief Get a function pointer to OpenGL `wglSwapBuffers`.
	 */
	twglSwapBuffers GetSwapBuffers();
	/** @brief Get a function pointer to SDL `SDL_ShowCursor`.
	 */
	bool GetSDLShowCursor(tSDL_ShowCursor& outSDL_ShowCursor);
	/** @brief Custom code that will be executed every time OpenGL `wglSwapBuffers` gets called.
	 */
	BOOL __stdcall CustomWglSwapBuffers(HDC hDc);
	/** @brief Custom Window Procedure to get access to Assault Cube's mouse input.
	 */
	LRESULT __stdcall CustomWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
} // namespace mvc
