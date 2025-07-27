modded class ActionTargets
{
	override private bool IsObstructedEx(Object object, IsObjectObstructedCache cache)
	{
		if (super.IsObstructedEx(object, cache))
		{
			if (object && (object.IsInherited(Zen_RebuildableWell) || object.IsInherited(Zen_RebuiltWell)))
			{
				return false;
			}

			return true;
		}

		return false;
	}
}