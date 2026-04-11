modded class MissionBase
{
	void MissionBase()
    {
        GetRPCManager().AddRPC("RPC_ZenVeganism", "RPC_ReceiveZenIsVeganOnClientRPC", this, SingeplayerExecutionType.Client);
    }
	
	void RPC_ReceiveZenIsVeganOnClientRPC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
		if (!g_Game)
			return;
		
        Param1<bool> data;

        // If data fails to read, stop here.
        if (!ctx.Read(data))
        {
            Error("IMPORTANT ERROR: RPC_ReceiveZenIsVeganOnClientRPC failed! Please tell Zenarchist he fucked up!");
            return;
        }

		Mission mission = g_Game.GetMission();
		IngameHud hud = IngameHud.Cast(mission.GetHud());
		PlayerBase pb = PlayerBase.Cast(g_Game.GetPlayer());
		
		if (!hud || !pb)
			return;
	
		pb.SetIsZenVegan(data.param1);
		hud.UpdateZenVeganIcon(data.param1);
    }
}
