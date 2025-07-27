class Zen_RebuildableWell extends ItemBase
{
	static const int ZEN_WELL_COUNT_PLANKS = 4;
	static const int ZEN_WELL_COUNT_STONES = 4;
	static const int ZEN_WELL_COUNT_NAILS = 50;
	static const int ZEN_WELL_COUNT_WIRE = 1;
	static const int ZEN_WELL_COUNT_PIPE = 1;

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
		}
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

	bool ZenWell_HasMaterials()
	{
		ItemBase planks = ItemBase.Cast(FindAttachmentBySlotName("ZenWells_WoodenPlanks"));
		if (!planks || planks.GetQuantity() != ZEN_WELL_COUNT_PLANKS)
			return false;

		ItemBase stones = ItemBase.Cast(FindAttachmentBySlotName("ZenWells_Stones"));
		if (!stones || stones.GetQuantity() != ZEN_WELL_COUNT_STONES)
			return false;

		ItemBase nails = ItemBase.Cast(FindAttachmentBySlotName("ZenWells_Nails"));
		if (!nails || nails.GetQuantity() != ZEN_WELL_COUNT_NAILS)
			return false;

		ItemBase wire = ItemBase.Cast(FindAttachmentBySlotName("Material_MetalWire"));
		if (ZEN_WELL_COUNT_WIRE > 0 && !wire)
			return false;

		ItemBase pipe = ItemBase.Cast(FindAttachmentBySlotName("ZenWells_Pipe"));
		if (ZEN_WELL_COUNT_PIPE > 0 && !pipe)
			return false;

		return true;
	}
}