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
				SetLifetimeMax(999999);
				SetLifetime(999999);
			}

			SpawnZenWell();
		}
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);

		if (GetGame().IsDedicatedServer())
		{
			EntityAI newObj = EntityAI.Cast(GetGame().CreateObject(ZenRebuildableWellsConfig.WELL_REBUILDABLE_TYPE, vector.Zero));
			if (!newObj)
			{
				Error("Failed to spawn well!");
				return;
			}

			newObj.SetPosition(GetPosition());
			newObj.SetOrientation(GetOrientation());
			newObj.Update();
		}
	}

	void SpawnZenWell()
	{
		vector pos = GetPosition();
		vector ori = GetOrientation();

		EntityAI newObj = EntityAI.Cast(GetGame().CreateObject(ZenRebuildableWellsConfig.WELL_BUILT_TYPE, vector.Zero));
		if (!newObj)
		{
			Error("Failed to spawn well " + ZenRebuildableWellsConfig.WELL_BUILT_TYPE);
			return;
		}

		newObj.SetPosition(pos + ZenRebuildableWellsConfig.WELL_OFFSET);
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