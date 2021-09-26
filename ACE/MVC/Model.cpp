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
	draw(*this),
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
	triggerbot("Triggerbot", [this] { Triggerbot(); }),
	noRecoil("No Recoil/Spread", [this]
	{
		memory::Nop((BYTE*)(moduleBaseAddress + 0x63786), 10);
	}, [this]
	{
		memory::Patch((BYTE*)(moduleBaseAddress + 0x63786), 
			(BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
	}),
	aimbot("Aimbot", [this] { Aimbot(); }),
	esp("ESP", [this]() { ESP(); })
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
	 * @return Reference to @ref aimbot
	 */
	Checkbox& Model::GetAimbot()
	{
		return aimbot;
	}

	Checkbox& Model::GetESP()
	{
		return esp;
	}

	/**
	 * @return View matrix
	 */
	float* Model::GetViewMatrix() const
	{
		return (float*)(moduleBaseAddress + 0x101AE8);
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
		Freeze(aimbot);
		Freeze(esp);
	}

	void Model::Freeze(Freezebox& data)
	{
		if (data.bEnabled)
		{
			data.freeze();
		}
	}

	void Model::Triggerbot() const
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
	}

	void Model::Aimbot() const
	{
		auto entityList{ GetEntityList() };
		if (!entityList)
		{
			return;
		}

		re::Entity* closestEntity{ nullptr };
		double closestDistance{ 9999999999.0 };
		for (int i{ 0 }; i < GetNumberOfPlayers(); ++i)
		{
			auto entity{ entityList->entities[i] };
			if (entity 
				and localPlayer != entity 
				and localPlayer->Team != entity->Team
				and entity->IsAlive()
				and localPlayer->IsEntityVisible(entity))
			{
				const auto distance{ localPlayer->Head.DistanceSquared(entity->Head) };
				if (distance < closestDistance)
				{
					closestEntity = entity;
					closestDistance = distance;
				}
			}
		}

		if (closestEntity)
		{
			localPlayer->Angle = localPlayer->Head.Angle(closestEntity->Head);
			localPlayer->bShoot = true;
		}
		else
		{
			localPlayer->bShoot = false;
		}
	}

	void Model::ESP()
	{
		auto entityList{ GetEntityList() };
		if (entityList)
		{
			draw.Setup2D();
			for (int i{ 0 }; i < GetNumberOfPlayers(); ++i)
			{
				auto entity = entityList->entities[i];
				if (entity and entity->IsAlive() and localPlayer)
				{
					draw.Entity2D(entity, localPlayer->Team != entity->Team);
				}
			}
			draw.Restore2D();
		}
	}

	/**
	 * @return Number of players
	 */
	int32_t Model::GetNumberOfPlayers() const
	{
		return *(int32_t*)(moduleBaseAddress + 0x10F500);
	}

	re::EntityList* Model::GetEntityList() const
	{
		return *(re::EntityList**)(moduleBaseAddress + 0x10F4F8);
	}
} // namespace mvc
