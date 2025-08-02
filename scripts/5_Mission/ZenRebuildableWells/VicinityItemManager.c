modded class VicinityItemManager
{
	override bool IsObstructed(Object filtered_object)
	{
		if (super.IsObstructed(filtered_object))
		{
			// The well object this is spawned on can obstruct its inventory view. Override that.
			if (filtered_object && filtered_object.IsKindOf(ZenRebuildableWellsConfig.WELL_REBUILDABLE_TYPE))
			{
				return false;
			}

			return true;
		}

		return false;
	}
}