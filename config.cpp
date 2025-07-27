class CfgPatches
{
	class ZenRebuildableWells
	{
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Gear_Tools",
			"DZ_Gear_Consumables"
		};
	};
};

class CfgMods
{
	class ZenRebuildableWells
	{
		dir = "ZenRebuildableWells";
		name = "Zen's Rebuildable Wells";
		author = "Zenarchist";
		credits = "";
		version = "1.0";
		type = "mod";
		dependencies[] = 
		{ 
			"Game", 
			"World", 
			"Mission" 
		};
		class defs
		{
			class imageSets
			{
				files[] =
				{
					"ZenRebuildableWells/data/gui/pipe.imageset"
				};
			};
			class engineScriptModule
			{
				files[]=
				{
					//"ZenRebuildableWells/scripts/1_Core",
					"ZenRebuildableWells/scripts/Common"
				};
			};
			class gameLibScriptModule
			{
				files[]=
				{
					//"ZenRebuildableWells/scripts/2_GameLib",
					"ZenRebuildableWells/scripts/Common"
				};
			};
			class gameScriptModule
			{
				files[] = 
				{ 
					"ZenRebuildableWells/scripts/Common",
					"ZenRebuildableWells/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				files[] = 
				{ 
					"ZenRebuildableWells/scripts/Common",
					"ZenRebuildableWells/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				files[] = 
				{ 
					"ZenRebuildableWells/scripts/Common",
					"ZenRebuildableWells/scripts/5_mission"
				};
			};
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class HouseNoDestruct;

	class WoodenPlank: Inventory_Base
	{
		inventorySlot[] +=
		{
			"ZenWells_WoodenPlanks"
		};
	};

	class Nail: Inventory_Base
	{
		inventorySlot[] +=
		{
			"ZenWells_Nails"
		};
	};

	class Stone: Inventory_Base
	{
		inventorySlot[] +=
		{
			"ZenWells_Stones"
		};
	};

	class Pipe: Inventory_Base
	{
		inventorySlot[] +=
		{
			"ZenWells_Pipe"
		};
	};

	class Zen_RebuildableWell : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_CfgVehicles_ZenRebuildableWell0";
		descriptionShort = "$STR_CfgVehicles_ZenRebuildableWell1";
		weight = 100000;
		physLayer="item_small";
		model = "DZ\structures\residential\misc\misc_well.p3d";
		itemSize[] = { 10,10 };
		attachments[]=
		{
			"ZenWells_WoodenPlanks",
			"ZenWells_Nails",
			"ZenWells_Stones",
			"Material_MetalWire",
			"ZenWells_Pipe"
		};
	};

	class Zen_RebuiltWell_Spawn : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_CfgVehicles_ZenRebuildableWell0";
		descriptionShort = "$STR_CfgVehicles_ZenRebuildableWell1";
		weight = 100000;
		physLayer="item_small";
		model = "DZ\structures\residential\misc\misc_well.p3d";
		itemSize[] = { 10,10 };
	};

	class Land_Misc_Well_Pump_Yellow;
	class Zen_RebuiltWell: HouseNoDestruct
	{
		scope=1;
		model="\DZ\structures\Residential\Misc\Misc_Well_Pump_Yellow.p3d";
		class AnimationSources
		{
			class Arm
			{
				source="user";
				initPhase=0;
				animPeriod=0.80000001;
			};
		};
	};
};

class CfgSlots
{
	class Slot_ZenWells_WoodenPlanks
	{
		name="ZenWells_WoodenPlanks";
		displayName="#STR_CfgPlanks0";
		ghostIcon="set:dayz_inventory image:planks";
		stackMax=4;
	};
	class Slot_ZenWells_Nails
	{
		name="ZenWells_Nails";
		displayName="#STR_CfgNails0";
		ghostIcon="set:dayz_inventory image:nails";
		stackMax=50;
	};
	class Slot_ZenWells_Stones
	{
		name="ZenWells_Stones";
		displayName="#STR_CfgStones0";
		ghostIcon="set:dayz_inventory image:stones";
		stackMax=4;
	};
	class Slot_ZenWells_Pipe
	{
		name="ZenWells_Pipe";
		displayName="#STR_CfgVehicles_Pipe0";
		ghostIcon="set:zenpipe image:zenpipe";
		stackMax=1;
	};
};