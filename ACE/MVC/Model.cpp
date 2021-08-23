/**
 * @file Model.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "../ReClass/Weapon.h"
#include "../Memory/Memory.h"
#include "Model.h"

namespace mvc
{
	Model::Model()
		:
	moduleBaseAddress(0),
	localPlayer(nullptr),
	GetEntityAtCrosshair(nullptr),
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
	jump("Jump", [this] { localPlayer->bJump = true; }),
	triggerbot("Triggerbot", [this]
	{
		if (GetEntityAtCrosshair)
		{
			auto* entity = (re::Entity*)GetEntityAtCrosshair();
			if (entity)
			{
				if (entity->Team != localPlayer->Team && entity->Health != 0)
				{
					localPlayer->bShoot = true;
				}
				else
				{
					localPlayer->bShoot = false;
				}
			}
			else
			{
				localPlayer->bShoot = false;
			}
		}
	}),
	noRecoil("No Recoil/Spread", [this]
	{
		memory::Nop((BYTE*)(moduleBaseAddress + 0x63786), 10);
	}, [this]
	{
		memory::Patch((BYTE*)(moduleBaseAddress + 0x63786), 
			(BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
	})
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
			GetEntityAtCrosshair = (tGetEntityAtCrosshair)0x4607C0;
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
	 * @return Reference to @ref triggerbot
	 */
	Checkbox& Model::GetTriggerbot()
	{
		return triggerbot;
	}

	/**
	 * @return Reference to @ref noRecoil
	 */
	Patchbox& Model::GetNoRecoil()
	{
		return noRecoil;
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
		Freeze(jump);
		Freeze(triggerbot);
	}

	void Model::Freeze(Freezebox& data)
	{
		if (data.bEnabled)
		{
			data.freeze();
		}
	}
} // namespace mvc
