modded class Edible_Base
{
	override void SetActions()
	{
		super.SetActions();

		if (IsFruit() || IsMushroom())
		{
			AddAction(ActionZenVeganize);
		}
	}
}
