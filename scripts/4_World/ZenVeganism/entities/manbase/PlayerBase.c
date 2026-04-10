modded class PlayerBase
{
	protected ref Timer m_ZenVeganNotifierTimer;
	protected bool m_IsZenVegan;
	
	void RollDiceZenVegan()
	{
		SetIsZenVegan(false);
		
		#ifdef ZenModPack
		if (!ZenModEnabled("ZenVeganism"))
			return;
		#endif
		
		float dice = Math.RandomFloat01();

		if (dice > GetZenVeganConfig().ChanceToSpawnAsVegan)
			return;

		SetIsZenVegan(true);

		if (GetZenVeganConfig().NotifyVeganText == "")
			return;
		
		if (!m_ZenVeganNotifierTimer)
			m_ZenVeganNotifierTimer = new Timer();
		
		m_ZenVeganNotifierTimer.Run(12, this, "NotifyZenVegan");
	}
	
	void NotifyZenVegan()
	{
		Zen_SendMessage(GetZenVeganConfig().NotifyVeganText);
	}
	
	void RefreshZenVeganStamina()
	{
		#ifdef ZenModPack
		if (!ZenModEnabled("ZenVeganism"))
			return;
		#endif
		
		if (!g_Game.IsDedicatedServer() || GetZenVeganConfig().VeganStaminaRecoveryMulti <= 0)
			return;
		
		StaminaHandler handler = GetStaminaHandler();
		if (!handler)
			return;

		if (m_IsZenVegan)
		{
			handler.ActivateRecoveryModifier(ZenVegan_EStaminaMultiplierTypes.VEGAN);
		} else
		{
			handler.DeactivateRecoveryModifier(ZenVegan_EStaminaMultiplierTypes.VEGAN);
		}
	}
	
	void SetIsZenVegan(bool state)
	{
		m_IsZenVegan = state;
		RefreshZenVeganStamina();
	}
	
	bool IsZenVegan()
	{
		return m_IsZenVegan;
	}
	
	override void DeferredInit()
	{
		super.DeferredInit();
		
		if (g_Game.IsDedicatedServer())
		{
			#ifdef ZenModPack
			if (!ZenModEnabled("ZenVeganism"))
				m_IsZenVegan = false;
			#endif
			
			SyncZenVeganStatusToClient();
		}
		
		RefreshZenVeganStamina();
	}
	
	void SyncZenVeganStatusToClient()
	{
		#ifdef ZenModPack
		if (!ZenModEnabled("ZenVeganism"))
			return;
		#endif
		
		Param1<bool> configParams = new Param1<bool>(m_IsZenVegan);
		GetRPCManager().SendRPC("RPC_ZenVeganism", "RPC_ReceiveZenIsVeganOnClientRPC", configParams, true, GetIdentity());
	}
	
	override bool Consume(PlayerConsumeData data)
	{
		if (!IsZenVegan() || !data || !data.m_Source)
			return super.Consume(data);

		ItemBase source = ItemBase.Cast(data.m_Source);
		if (!source)
			return super.Consume(data);
	
		string foodType = source.GetType();
		foodType.ToLower();
		
		foreach (string s : GetZenVeganConfig().CantEatList)
		{
			if (foodType.Contains(s) || source.IsKindOf(s))
			{
				SymptomBase symptom = GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
				if (symptom)
				{
					CachedObjectsParams.PARAM1_FLOAT.param1 = 0.01; //percentage of stomach
					symptom.SetParam(CachedObjectsParams.PARAM1_FLOAT);	
					Zen_SendMessage(GetZenVeganConfig().NotifyCantEatText);
				}
				
				return false;
			}
		}

		return super.Consume(data);
	}
	
	// USE CF_Load/Save because this will NOT break server persistence if the mod is added/removed mid-wipe.
	// NOTE: storage[] must refer to this mod's CfgMods classname EXACTLY or this won't work.
	
	override void CF_OnStoreSave(CF_ModStorageMap storage)
	{
		super.CF_OnStoreSave(storage);

		auto ctx = storage["ZenVeganism"];
		if (!ctx) return;
		
		ctx.Write(m_IsZenVegan);
	}

	override bool CF_OnStoreLoad(CF_ModStorageMap storage)
	{
		if (!super.CF_OnStoreLoad(storage)) return false;

		auto ctx = storage["ZenVeganism"];
		if (!ctx) return true;

		if (ctx.GetVersion() >= 1)
		{
			if (!ctx.Read(m_IsZenVegan)) return false;
		}

		return true;
	}
}