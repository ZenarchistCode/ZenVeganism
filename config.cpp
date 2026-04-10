/*
	(c) 2026 | ZenVeganism | Zenarchist
*/

class CfgPatches
{
	class ZenVeganism
	{
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"ZenModCore"
		};
	};
};

class CfgMods
{
	class ZenVeganism
	{
		author = "Zenarchist";
		type = "mod";
		version = "1.0";
		storageVersion = 1; // CF storage
		defines[]=
		{
			//"ZenVeganismDebug"
		};
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = 
				{ 
					"ZenVeganism/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value = "";
				files[] = 
				{ 
					"ZenVeganism/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] = 
				{ 
					"ZenVeganism/scripts/5_Mission"
				};
			};
		};
	};
};
