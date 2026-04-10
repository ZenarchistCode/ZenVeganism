modded class IngameHud
{
	protected ImageWidget m_ZenVeganIcon;

	// Create or turn on/off vegan V icon near hunger apple icon
	void UpdateZenVeganIcon(bool show)
	{
		if (m_ZenVeganIcon != null)
		{
			m_ZenVeganIcon.Show(show);
			return;
		}
		else
		{
			if (!show)
				return;
		}
		
		Widget hungryRoot = m_Notifiers.FindAnyWidget("Hungry");
		if (!hungryRoot || hungryRoot.FindAnyWidget("IconHungryV"))
			return;

		Widget overlayRoot = g_Game.GetWorkspace().CreateWidgets("ZenVeganism/gui/layouts/hunger_v_overlay.layout", hungryRoot);
		if (!overlayRoot)
			return;

		m_ZenVeganIcon = ImageWidget.Cast(overlayRoot.FindAnyWidget("IconHungryV"));
		if (!m_ZenVeganIcon)
			return;

		m_ZenVeganIcon.LoadImageFile(0, "ZenVeganism/gui/textures/icon_v.paa");
		m_ZenVeganIcon.SetImage(0);
		m_ZenVeganIcon.SetSort(hungryRoot.GetSort());
		m_ZenVeganIcon.Show(true);
	}

	// Mirror vanilla hunger color/blink onto the vegan icon
	override void DisplayTendencyNormal(int key, int tendency, int status)
	{
		super.DisplayTendencyNormal(key, tendency, status);

		if (key != NTFKEY_HUNGRY || !m_ZenVeganIcon)
			return;

		float alpha = m_ZenVeganIcon.GetAlpha();

		switch (status)
		{
			case 3:
				m_ZenVeganIcon.SetColor(ARGB(alpha * 255, 220, 220, 0));
				m_TendencyStatusCritical.Remove(m_ZenVeganIcon);
				break;

			case 4:
				m_ZenVeganIcon.SetColor(ARGB(alpha * 255, 220, 0, 0));
				m_TendencyStatusCritical.Remove(m_ZenVeganIcon);
				break;

			case 5:
				if (!m_TendencyStatusCritical.Contains(m_ZenVeganIcon))
					m_TendencyStatusCritical.Insert(m_ZenVeganIcon, ARGB(alpha * 255, 220, 0, 0));
				break;

			default:
				m_ZenVeganIcon.SetColor(ARGB(alpha * 255, 220, 220, 220));
				m_TendencyStatusCritical.Remove(m_ZenVeganIcon);
				break;
		}
	}
}
