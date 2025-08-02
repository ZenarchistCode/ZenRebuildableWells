class ActionZenBuildWellCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.BASEBUILDING_CONSTRUCT_SLOW);
	}
}

class ActionZenBuildWell: ActionContinuousBase
{
	void ActionZenBuildWell()
	{
		m_CallbackClass = ActionZenBuildWellCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_MINEROCK;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_Text = "#build";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem		= new CCINonRuined();
		m_ConditionTarget	= new CCTNone();
	}

	override bool CanBeUsedLeaning()
	{
		return false;
	}
	
	override bool CanBeUsedInFreelook()
	{
		return false;
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (player.IsPlacingLocal() || player.IsPlacingServer())
			return false;
		
		if (player.GetBrokenLegs() == eBrokenLegs.BROKEN_LEGS)
			return false;

		Object obj = target.GetObject();
		if (!obj)
			return false;

		Zen_RebuildableWell rebuildableWell = Zen_RebuildableWell.Cast(obj);
		if (!rebuildableWell)
			return false;

		return rebuildableWell.ZenWell_HasMaterials();
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{
		Object obj = action_data.m_Target.GetObject();
		if (!obj)
			return;

		Zen_RebuildableWell rebuildableWell = Zen_RebuildableWell.Cast(obj);
		if (!rebuildableWell)
			return;

		vector pos = rebuildableWell.GetPosition();
		vector ori = rebuildableWell.GetOrientation();

		EntityAI newObj = EntityAI.Cast(GetGame().CreateObject(ZenRebuildableWellsConfig.WELL_SPAWNER_TYPE, vector.Zero));
		if (!newObj)
		{
			Error("Failed to spawn well " + ZenRebuildableWellsConfig.WELL_SPAWNER_TYPE);
			return;
		}

		newObj.SetPosition(pos);
		newObj.SetOrientation(ori);
		newObj.Update();
		
		rebuildableWell.DeleteSafe();

		action_data.m_MainItem.AddHealth(GetZenRebuildableWellsConfig().DamageTool * -1.0);

		Print("[ZenRebuildableWells] Player " + action_data.m_Player.GetIdentity().GetId() + " rebuilt well @ " + newObj.GetPosition() + " - lifetime: " + newObj.GetLifetime());
	}
	
	override string GetSoundCategory(ActionData action_data)
    {
        return "Base_building";
    }
	
	override bool SetupAction(PlayerBase player, ActionTarget target, ItemBase item, out ActionData action_data, Param extra_data = NULL)
	{	
		if (super.SetupAction(player, target, item, action_data, extra_data))
		{
			ZenSetBuildingAnimation(item);
			return true;
		}
		
		return false;
	}

	protected void ZenSetBuildingAnimation(ItemBase item)
	{
		switch (item.Type())
		{
			case Pickaxe:
			case Shovel:
			case FarmingHoe:
			case FieldShovel:
				m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DIG;
				break;
			case Pliers:
				m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
				break;
			case SledgeHammer:
				m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_MINEROCK;
				break;
			default:
				m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_ASSEMBLE;
				break;
		}
	}
}