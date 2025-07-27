class ZenRebuildableWellsConfig
{
	// Static constant config version (is NOT saved to json)
	static const string CONFIG_VERSION = "1";

	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\";
	private const static string zenConfigName = "ZenRebuildableWellsConfig.json";

	// Main config data
	string ConfigVersion = "";
	string DefunctWellType;
	string RebuildableWellType;
	string BuiltWellType;
	vector BuiltWellOffset;
	int DamageTool;
	int SecsTilDespawn;
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
		DefunctWellType = "misc_well.p3d";
		RebuildableWellType = "Zen_RebuildableWell";
		BuiltWellType = "Zen_RebuiltWell";
		BuiltWellOffset = "0 0.9 0";
		DamageTool = 100;
		SecsTilDespawn = 0;
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