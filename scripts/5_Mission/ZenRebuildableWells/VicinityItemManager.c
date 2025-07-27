modded class VicinityItemManager
{
	override bool IsObstructed(Object filtered_object)
	{
		if (super.IsObstructed(filtered_object))
		{
			// The well object this is spawned on can obstruct its inventory view. Override that.
			if (filtered_object && filtered_object.IsInherited(Zen_RebuildableWell))
			{
				return false;
			}

			return true;
		}

		return false;
	}
}