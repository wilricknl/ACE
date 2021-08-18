/**
 * @file View.h
 * @brief The graphical user interface of the program.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once

namespace mvc
{
	/**
	 * @brief View takes care of the graphical user interface using ImGui.
	 */
	class View
	{
	public:
		View();
		~View() = default;
		View(const View& view) = delete;
		View(View&& view) = delete;
		View& operator=(const View& gui) = delete;
		View& operator=(View&& gui) = delete;

		/** @brief Initialize ImGui context.
		 */
		void Initialize(HWND hWnd);
		/** @brief Show the ImGui interface.
		 */
		bool Show();
		/** @brief Destroy the ImGui context.
		 */
		void Shutdown();
	};
} // namespace mvc
