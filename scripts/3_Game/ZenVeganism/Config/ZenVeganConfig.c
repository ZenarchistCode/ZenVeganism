ref ZenVeganConfig g_ZenVeganConfig;

static ZenVeganConfig GetZenVeganConfig()
{
	if (!g_ZenVeganConfig) GetZenConfigRegister().RegisterConfig(ZenVeganConfig);
	return g_ZenVeganConfig;
}

modded class ZenConfigRegister
{
	override void RegisterPreload()
	{
		super.RegisterPreload(); 
		RegisterType(ZenVeganConfig);
	}
}

class ZenVeganConfig_SyncPayload
{
	bool CanUseFruitOnTreeToVeganize;
	
	void ZenVeganConfig_SyncPayload()
	{
		CanUseFruitOnTreeToVeganize = false;
	}
}

class ZenVeganConfig : ZenConfigBase
{
	// -------------------------
	// CONFIG SETTINGS
	// -------------------------
	override void OnRegistered()
	{
		g_ZenVeganConfig = this;
	}
	
	override string    	GetCurrentVersion()   		{ return "1.29.1"; }
	override bool		ShouldLoadOnServer() 		{ return true; }
	override bool		ShouldSyncToClient()		{ return true; }
	
	override bool ReadJson(string path, out string err)
	{
		return JsonFileLoader<ZenVeganConfig>.LoadFile(path, this, err);
	}

	override bool WriteJson(string path, out string err)
	{
		return JsonFileLoader<ZenVeganConfig>.SaveFile(path, this, err);
	}
	
	override bool BuildSyncPayload(out string payload, out string err)
	{
		ZenVeganConfig_SyncPayload snap = new ZenVeganConfig_SyncPayload();

		snap.CanUseFruitOnTreeToVeganize = CanUseFruitOnTreeToVeganize;

		// Serialize payload only (NOT the whole config)
		return JsonFileLoader<ZenVeganConfig_SyncPayload>.MakeData(snap, payload, err, false);
	}

	override bool ApplySyncPayload(string payload, out string err)
	{
		ZenVeganConfig_SyncPayload snap = new ZenVeganConfig_SyncPayload();
		if (!JsonFileLoader<ZenVeganConfig_SyncPayload>.LoadData(payload, snap, err))
		{
			return false;
		}

		CanUseFruitOnTreeToVeganize = snap.CanUseFruitOnTreeToVeganize;
		
		return true;
	}
	
	// -------------------------
	// CONFIG VARIABLES
	// -------------------------
	float ChanceToSpawnAsVegan;
	float VeganStaminaRecoveryMulti;
	bool CanUseFruitOnTreeToVeganize;
	string NotifyVeganText;
	string NotifyCantEatText;
	ref array<string> CantEatList;

	// -------------------------
	// OVERRIDE FUNCTIONS
	// -------------------------
	override void SetDefaults()
	{
		ChanceToSpawnAsVegan = 0.1;
		VeganStaminaRecoveryMulti = 1.5;
		CanUseFruitOnTreeToVeganize = false;
		NotifyVeganText = "#STR_ZenVeganism_Notification";
		NotifyCantEatText = "#STR_ZenVeganism_Yuck";
		CantEatList = new array<string>;
		
		// Animals
		CantEatList.Insert("Meat");
		CantEatList.Insert("Lard");
		CantEatList.Insert("Guts");
		CantEatList.Insert("Milk");
		CantEatList.Insert("Beef");
		CantEatList.Insert("Cheese");
		CantEatList.Insert("Chicken");
		
		// Canned meats
		CantEatList.Insert("Crab");
		CantEatList.Insert("Pork");
		CantEatList.Insert("Bacon");
		CantEatList.Insert("CatFood");
		CantEatList.Insert("DogFood");
		CantEatList.Insert("UnknownFoodCan");
		CantEatList.Insert("Pajka");
		CantEatList.Insert("Pate_Opened");
		CantEatList.Insert("BrisketSpread");
		CantEatList.Insert("CookZ");
		
		// Fish
		CantEatList.Insert("Tuna");
		CantEatList.Insert("Sardine");
		CantEatList.Insert("Shrimp");
		CantEatList.Insert("Bitterlings");
		CantEatList.Insert("RedCaviar");
		CantEatList.Insert("Fillet");

		// Insects
		CantEatList.Insert("Worm");
		CantEatList.Insert("Honey");
	}
	
	// Convert all entries to lower-case in memory to make searching more robust (leave file untouched for readability)
	override void AfterLoad()
	{
		array<string> tempList = new array<string>;
		foreach (string s : CantEatList)
		{
			s.ToLower();
			
			if (tempList.Find(s) != -1)
				continue;
			
			tempList.Insert(s);
		}
		
		CantEatList.Clear();
		CantEatList.Copy(tempList);
		
		if (VeganStaminaRecoveryMulti == 1.0)
			VeganStaminaRecoveryMulti = 0;
	}
}