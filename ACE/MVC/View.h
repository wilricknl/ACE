/**
 * @file View.h
 * @brief The graphical user interface of the program.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once
#include "Model.h"

namespace mvc
{
	/**
	 * @brief View takes care of the graphical user interface using ImGui.
	 */
	class View
	{
	public:
		View(Model& model);
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
		/** @brief Check if program should eject and exit.
		 */
		bool IsEject() const;
	private:
		/** @brief Show the graphical interface.
		 */
		void ShowWindow(bool* bShow);
		/** @brief Show the menu bar of the graphical interface.
		 */
		void ShowMenuBar(bool* bShow);
		/** @brief Show the tab bar of the graphical interface.
		 */
		void ShowTabs();
		/** @brief Show the general settings of the program.
		 */
		void ShowGeneralTab();
		/** @brief Show the aim assist settings of the program.
		 */
		void ShowAimAssistTab();
		/** @brief Show the ESP settings of the program.
		 */
		void ShowESPTab();
		/** @brief Show my ASCII logo.
		 */
		void ShowLogo(bool bCentered = false);
	private:
		bool bDemo = false; ///< Show demo window status (`true` = show and `false` = hide)
		bool bEject = false; ///< Ejection status
		Model& model; ///< The data storage of the graphical interface.
	};
} // namespace mvc
