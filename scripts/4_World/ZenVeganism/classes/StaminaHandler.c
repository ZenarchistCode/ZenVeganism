enum ZenVegan_EStaminaMultiplierTypes : EStaminaMultiplierTypes
{
    VEGAN = -69312469
}

modded class StaminaHandler
{
    override void Init()
    {
        super.Init();

		if (!g_Game.IsDedicatedServer())
			return;
		
		if (GetZenVeganConfig().VeganStaminaRecoveryMulti > 0)
		{
			m_RegisteredRecoveryModifiers.Insert(ZenVegan_EStaminaMultiplierTypes.VEGAN, GetZenVeganConfig().VeganStaminaRecoveryMulti);
		}
    }
}
