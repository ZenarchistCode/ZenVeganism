class ActionZenVeganizeCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.BASEBUILDING_REPAIR_FAST * 5);
	}
}

class ActionZenVeganize : ActionContinuousBase
{
	void ActionZenVeganize()
	{
		m_CallbackClass = ActionZenVeganizeCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_FullBody = true;
		m_Text = "#STR_ZenVeganism_TurnVegan";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursorNoRuinCheck(UAMaxDistances.SMALL);
	}
	
	override bool CanBeUsedInFreelook()
	{
		return false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (player.IsZenVegan())
			return false; 
		
		if (!GetZenVeganConfig().CanUseFruitOnTreeToVeganize)
			return false;
		
		Object targetObject = target.GetObject();
		return targetObject != null && targetObject.IsTree();
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{
		action_data.m_Player.SetIsZenVegan(true);
		action_data.m_Player.NotifyZenVegan();
		action_data.m_Player.SyncZenVeganStatusToClient();
	}
}