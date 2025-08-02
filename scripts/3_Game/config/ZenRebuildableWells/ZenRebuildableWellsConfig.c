class ZenRebuildableWellsConfig
{
	// Static constant config version (is NOT saved to json)
	static const string CONFIG_VERSION = "1";

	static const string WELL_STATIC_P3D = "misc_well.p3d";
	static const string WELL_REBUILDABLE_TYPE = "Zen_RebuildableWell";
	static const string WELL_SPAWNER_TYPE = "Zen_RebuiltWell_Spawn";
	static const string WELL_BUILT_TYPE = "Zen_RebuiltWell";
	static const vector WELL_OFFSET = "0 0.9 0";

	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\";
	private const static string zenConfigName = "ZenRebuildableWellsConfig.json";

	// Main config data
	string ConfigVersion = "";
	int DamageTool;
	bool RespawnRebuildableWells;
	bool DeleteRebuildableWells;

	void Load()
	{
		if (!GetGame().IsDedicatedServer())
			return;

		if (FileExist(zenModFolder + zenConfigName))
		{
			JsonFileLoader<ZenRebuildableWellsConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			if (ConfigVersion != CONFIG_VERSION)
			{
				JsonFileLoader<ZenRebuildableWellsConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				return;
			}
		}

		ConfigVersion = CONFIG_VERSION;
		DamageTool = 100;
		RespawnRebuildableWells = true;
		DeleteRebuildableWells = false;

		Save();
	}

	void Save()
	{
		if (!GetGame().IsDedicatedServer())
			return;

		if (!FileExist(zenModFolder))
		{
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<ZenRebuildableWellsConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}
}

// Save config data
ref ZenRebuildableWellsConfig m_ZenRebuildableWellsConfig;

// Helper function to return Config data storage object
static ZenRebuildableWellsConfig GetZenRebuildableWellsConfig()
{
	if (!m_ZenRebuildableWellsConfig)
	{
		Print("[ZenRebuildableWellsConfig] Init");
		m_ZenRebuildableWellsConfig = new ZenRebuildableWellsConfig();
		m_ZenRebuildableWellsConfig.Load();
	}

	return m_ZenRebuildableWellsConfig;
}