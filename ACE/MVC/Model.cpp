/**
 * @file Model.cpp
 * @author wilricknl
 * @see https://github.com/wilricknl/ACE
 */
#include "../pch.h"
#include "../ReClass/Weapon.h"
#include "../Memory/Memory.h"
#include "../Utility/Math.h"
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
			if (localPlayer) localPlayer->Health = value;
		},
		1337),
	armor(
		"Armor",
		0,
		9999,
		[this](int value)
		{
			if (localPlayer) localPlayer->Armor = value;
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
		1337
	),
	jump("Jump", [this] { localPlayer->bJump = true; }),
	triggerbot("Triggerbot", [this] { Triggerbot(); }),
	noRecoil(
		"No Recoil/Spread", 
		[this]
		{
			memory::Nop((BYTE*)(moduleBaseAddress + 0x63786), 10);
		}, 
		[this]
		{
			memory::Patch((BYTE*)(moduleBaseAddress + 0x63786), 
					(BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
		}
	),
	aimbot("Aimbot", [this] { Aimbot(); }),
	esp("ESP", [this]() { ESP(); }),
	teleport("Teleport", 0, 100, [this](int value) { Teleport((float)value);  }, 5),
	autoShoot("Auto Shoot", [this] { if (localPlayer) localPlayer->bShoot = true;  })
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

	CheckSliderInt32& Model::GetTeleport()
	{
		return teleport;
	}

	Checkbox& Model::GetAutoShoot()
	{
		return autoShoot;
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
		Freeze(teleport);
		Freeze(autoShoot);
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
				if (IsEnemy(entity) and entity->IsAlive())
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
				and IsEnemy(entity)
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
					draw.Entity2D(entity, IsEnemy(entity));
				}
			}
			draw.Restore2D();
		}
	}

	/**
	 * @p distance Teleport distance from local player
	 */
	void Model::Teleport(float distance)
	{
		auto entityList{ GetEntityList() };
		if (entityList)
		{
			auto view{ localPlayer->Angle };
			math::Vec3 normal{
				std::cos(math::DegreesToRadians(view.x - 90.f)) * distance,
				std::sin(math::DegreesToRadians(view.x - 90.f)) * distance,
				std::sin(math::DegreesToRadians(view.y)) * distance
			};

			for (int i{ 0 }; i < GetNumberOfPlayers(); ++i)
			{
				auto entity = entityList->entities[i];
				if (entity
					and localPlayer
					and localPlayer != entity
					and entity->IsAlive()
					and IsEnemy(entity))
				{
					entity->Position = localPlayer->Position + normal;
				}
			}
		}
	}

	/**
	 * @return Number of players
	 */
	int32_t Model::GetNumberOfPlayers() const
	{
		return *(int32_t*)(moduleBaseAddress + 0x10F500);
	}

	/**
	 * @return Pointer to entity list
	 */
	re::EntityList* Model::GetEntityList() const
	{
		return *(re::EntityList**)(moduleBaseAddress + 0x10F4F8);
	}

	/** @return Game mode
	 */
	int32_t Model::GetGameMode() const
	{
		return *(int32_t*)(moduleBaseAddress + 0x10F49C);
	}

	/**
	 * @p gameMode Game mode id
	 *
	 * @return `true` if in team game, else `false`
	 */
	bool Model::IsTeamGame(int32_t gameMode) const
	{
		return gameMode == 0
			or gameMode == 4
			or gameMode == 5
			or gameMode == 7
			or gameMode == 11
			or gameMode == 13
			or gameMode == 14
			or gameMode == 16
			or gameMode == 17
			or gameMode == 20
			or gameMode == 21;
	}

	/**
	 * @p entity Entity to check
	 *
	 * @return `true` if entity is enemy, else `false`
	 */
	bool Model::IsEnemy(re::Entity* entity) const
	{
		if (IsTeamGame(GetGameMode()))
		{
			return localPlayer->Team != entity->Team;
		}
		return true;
	}
} // namespace mvc
