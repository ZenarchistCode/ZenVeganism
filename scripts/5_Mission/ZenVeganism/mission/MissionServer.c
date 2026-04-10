modded class MissionServer
{
	override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		super.OnClientNewEvent(identity, pos, ctx);
		
		if (m_player) m_player.RollDiceZenVegan();
		
		return m_player;
	}
}