modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		#ifdef ZENMODPACK
		if (!ZenModEnabled("ZenRebuildableWells"))
			return;
		#endif

		GetZenRebuildableWellsConfig();
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();

		#ifdef ZENMODPACK
		if (!ZenModEnabled("ZenRebuildableWells"))
			return;
		#endif

		if (GetZenRebuildableWellsConfig().RespawnRebuildableWells || GetZenRebuildableWellsConfig().DeleteRebuildableWells)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DumpZenWellRuins, 20000, false);
		}
	}

	void DumpZenWellRuins()
	{
		Print("[ZenRebuildableWells] Start object dump.");

		vector centerPos = GetGame().ConfigGetVector(string.Format("CfgWorlds %1 centerPosition", GetGame().GetWorldName()));

		// Get all objects on the map in a 20km radius from the center of that 20km radius (enough for most maps?)
		array<Object> objectsOnMap = new array<Object>;
		GetGame().GetObjectsAtPosition3D(centerPos, 20000, objectsOnMap, NULL);
		int newObjCount = 0;
		int oldObjCount = 0;

		// Cycle through all map objects
		for (int x = 0; x < objectsOnMap.Count(); x++)
		{
			// Prepare classname(s)
			string debugName = "";
			string className = "";

			// Get classname(s)
			debugName = objectsOnMap[x].GetDebugNameNative();
			className = objectsOnMap[x].ClassName();

			// Convert to lower
			debugName.ToLower();
			className.ToLower();

			string checkName = ZenRebuildableWellsConfig.WELL_STATIC_P3D;
			checkName.ToLower();

			// If map object is what we're looking for, add it to the array
			if (debugName.Contains(checkName) || className.Contains(checkName))
			{
				vector pos = objectsOnMap[x].GetPosition();
				vector ori = objectsOnMap[x].GetOrientation();

				array<Object> objectsNearWell = new array<Object>;
				GetGame().GetObjectsAtPosition3D(pos, 1, objectsNearWell, NULL);
				bool foundWell = false;

				for (int i = 0; i < objectsNearWell.Count(); i++)
				{
					Object objNearWell = objectsNearWell.Get(i);
					if (objNearWell.IsKindOf(ZenRebuildableWellsConfig.WELL_REBUILDABLE_TYPE))
					{
						oldObjCount++;
						foundWell = true;
						EntityAI oldObj = EntityAI.Cast(objNearWell);
						if (oldObj)
						{
							if (GetZenRebuildableWellsConfig().DeleteRebuildableWells)
							{
								oldObj.DeleteSafe();
								Print("[ZenRebuildableWells] Deleted existing well @ " + pos);
							}
							else
							{
								Print("[ZenRebuildableWells] Detecting existing well @ " + pos + " lifetime=" + oldObj.GetLifetime());
							}
						}
					}
				}

				if (foundWell || !GetZenRebuildableWellsConfig().RespawnRebuildableWells)
				{
					// Skip this loop - a persistent well already exists here.
					continue;
				}

				if (!SpawnZenRebuildableWell(pos, ori))
				{
					continue;
				}

				newObjCount++;
			}
		}

		if (GetZenRebuildableWellsConfig().DeleteRebuildableWells)
		{
			Print("[ZenRebuildableWells] Deleted " + oldObjCount + " rebuildable wells.");
		}
		else
		{
			Print("[ZenRebuildableWells] Spawned " + newObjCount + " new rebuildable wells, detected " + oldObjCount + " existing wells.");
		}

		GetZenRebuildableWellsConfig().RespawnRebuildableWells = false;
		GetZenRebuildableWellsConfig().DeleteRebuildableWells = false;
		GetZenRebuildableWellsConfig().Save();
	}

	bool SpawnZenRebuildableWell(vector pos, vector ori)
	{
		EntityAI newObj = EntityAI.Cast(GetGame().CreateObject(ZenRebuildableWellsConfig.WELL_REBUILDABLE_TYPE, pos));
		if (!newObj)
		{
			Error("Failed to spawn " + ZenRebuildableWellsConfig.WELL_REBUILDABLE_TYPE);
			return false;
		}

		newObj.SetPosition(pos);
		newObj.SetOrientation(ori);
		newObj.SetScale(0.01); // tiny, this obj is just for vicinity icon.
		newObj.Update();

		Print("[ZenRebuildableWells] Spawned " + newObj.GetType() + " @ " + pos + " lifetime=" + newObj.GetLifetime());

		return true;
	}
}