/**
 * @mainpage Assault Cube Enhancement
 * An open source cheat for Assault Cube.
 *
 * @author wilricknl
 * @date 17 August 2021
 * @version 0.3.1
 * @see https://github.com/wilricknl/ACE
 */
/**
 * @file version.h
 * @brief Current version and history of the program.
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#pragma once

namespace version
{
	/// Current version number
	extern std::string version;
} // namespace version

/**
 * Version History
 *
 * 0.3.1
 * [+] Teleport of enemies
 * [+] Auto shoot
 *
 * Release version 0.3.0
 *
 * 0.2.2
 * [+] 2D ESP for entities
 * [!] After ejecting text is bugged when reinjecting and game is not restarted
 *
 * 0.2.1
 * [+] OpenGL line, outline, rectangle, bar, and text drawing
 * [+] World to screen calculation
 * [!] Aimbot ignores half of the enemies in solo games
 *
 * Release version 0.2.0
 *
 * 0.1.2
 * [+] Add aimbot
 * [+] Add math functions and Vec3
 * [+] Add head location, angles and bShoot to Entity class
 *
 * 0.1.1
 * [+] Refactor widgets
 * [+] Add Aim Assist tab
 * [+] Add triggerbot
 * [+] Add no recoil/spread
 *
 * Release version 0.1.0
 *
 * 0.0.3
 * [+] Change health, armor, and ammunition
 * [+] Freeze health, armor, ammunition and jump
 *
 * 0.0.2
 * [+] Custom window and menu bar
 * [+] Eject button
 * [+] Demo window button
 * [+] Create custom check slider widgets
 * [+] Add logo
 * [+] Add interface for general settings
 * [!] Sometimes unknown access violation when ejecting the DLL; try to debug it later.
 *
 * 0.0.1
 * [+] Hook wglSwapBuffers and Window Procedure
 * [+] Add ImGui
 * [+] Add controller and view
 * [+] Show a demo window by pressing INSERT
 * [+] Exit cheat by pressing END
 * 
 */
