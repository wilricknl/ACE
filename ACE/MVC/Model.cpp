/**
 * @file Model.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "../ReClass/Weapon.h"
#include "Model.h"

namespace mvc
{
	Model::Model()
		:
	moduleBaseAddress(0),
	localPlayer(nullptr),
	bInitialized(false),
	health(
		"Health",
		0,
		9999,
		[this](int value)
		{
			if (localPlayer)
			{
				localPlayer->Health = value;
			}
		},
		1337),
	armor(
		"Armor",
		0,
		9999,
		[this](int value)
		{
			if (localPlayer)
			{
				localPlayer->Armor = value;
			}
		},
		1337),
	ammunition(
		"Ammunition",
		0,
		9999,
		[this](int value)
		{
			if (localPlayer)
			{
				auto const clip = localPlayer->Weapon->Clip;
				if (clip)
				{
					*clip = value;
				}
			}
		},
		1337),
	jump("Jump")
	{
		Initialize();
	}

	/**
	 * @return `true` if initialization succeeded, else `false`.
	 */
	bool Model::Initialize()
	{
		if (GetModuleBaseAddress())
		{
			localPlayer = *(re::Entity**)(moduleBaseAddress + 0x10F4F4);
			bInitialized = true;
		}
		else
		{
			bInitialized = false;
		}
		
		return bInitialized;
	}

	void Model::Execute()
	{
		Freeze();
	}

	/**
	 * @return `true` if initialized, else `false`.
	 */
	bool Model::IsInitialized() const
	{
		return bInitialized;
	}

	/**
	 * @return Reference to @ref health
	 */
	CheckSliderInt32& Model::GetHealth()
	{
		return health;
	}

	/**
	 * @return Reference to @ref armor
	 */
	CheckSliderInt32& Model::GetArmor()
	{
		return armor;
	}

	/**
	 * @return Reference to @ref ammunition
	 */
	CheckSliderInt32& Model::GetAmmunition()
	{
		return ammunition;
	}

	/**
	 * @return Reference to @ref jump
	 */
	Checkbox& Model::GetJump()
	{
		return jump;
	}

	/**
	 * @return `true` if succeeded, else `false`.
	 */
	bool Model::GetModuleBaseAddress()
	{
		auto mHandle = GetModuleHandle(L"ac_client.exe");
		if (mHandle)
		{
			moduleBaseAddress = (uintptr_t)mHandle;
			return true;
		}
		return false;
	}

	void Model::Freeze()
	{
		Freeze(health);
		Freeze(armor);
		Freeze(ammunition);

		if (jump.bEnabled)
		{
			localPlayer->bJump = true;
		}
	}
} // namespace mvc
