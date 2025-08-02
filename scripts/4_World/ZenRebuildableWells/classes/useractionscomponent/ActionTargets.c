modded class ActionTargets
{
	override private bool IsObstructedEx(Object object, IsObjectObstructedCache cache)
	{
		if (super.IsObstructedEx(object, cache))
		{
			if (object && (object.IsKindOf(ZenRebuildableWellsConfig.WELL_REBUILDABLE_TYPE) || object.IsKindOf(ZenRebuildableWellsConfig.WELL_BUILT_TYPE)))
			{
				return false;
			}

			return true;
		}

		return false;
	}
}