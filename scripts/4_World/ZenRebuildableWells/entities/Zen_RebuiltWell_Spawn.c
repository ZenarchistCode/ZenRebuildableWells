class Zen_RebuiltWell_Spawn extends ItemBase
{
	override void DeferredInit()
	{
		super.DeferredInit();

		if (GetGame().IsDedicatedServer())
		{
			SetScale(0.01);
			SetAllowDamage(false);

			if (GetEconomyProfile().GetLifetime() == 1800) // default persistence = no types.xml entry?
			{
				SetLifetimeMax(99999);
				SetLifetime(GetLifetimeMax());
			}

			SpawnZenWell();
		}
	}

	void SpawnZenWell()
	{
		vector pos = GetPosition();
		vector ori = GetOrientation();

		EntityAI newObj = EntityAI.Cast(GetGame().CreateObject(GetZenRebuildableWellsConfig().BuiltWellType, vector.Zero));
		if (!newObj)
		{
			Error("Failed to spawn well " + GetZenRebuildableWellsConfig().BuiltWellType);
			return;
		}

		newObj.SetPosition(pos + GetZenRebuildableWellsConfig().BuiltWellOffset);
		newObj.SetOrientation(ori);
		newObj.Update();

		Print("[ZenRebuildableWells] Spawned " + newObj.GetType() + " @ " + newObj.GetPosition() + " - lifetime=" + newObj.GetLifetime());
	}

	override bool CanPutInCargo(EntityAI parent)
	{
		return false;
	}

	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}

	override bool IsTakeable()
	{
		return false;
	}

	override bool IsInventoryVisible()
	{
		return false;
	}

	override bool CanDisplayCargo()
	{
		return false;
	}

	override bool DisableVicinityIcon()
	{
		return true;
	}
}