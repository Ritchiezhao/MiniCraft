#include "stdafx.h"
#include "Building.h"
#include "World.h"
#include "GUIManager.h"


const STRING Building::sNamePrefix = "EntBuilding";

Building::Building()
:SelectableObject()
,m_buildingName("")
{
	memset(m_pAbilitySlots, 0, MAX_ABILITY_SLOT * sizeof(SAbilityData*));
}

void Building::OnSelected( bool bSelected )
{
	//�����������
	if (bSelected)
	{
		const auto& selObjs = World::GetSingleton().GetSelectedObjects();
		//TODO: ��ѡ״̬���������Ӧ������?
		if(selObjs.size() > 1)
			return;
		
		//����UIͼ��
		for(int i=0; i<MAX_ABILITY_SLOT; ++i)
		{
			if(m_pAbilitySlots[i])
				CGUIManager::GetSingleton().GetCommandPanel()->CEGUI_SetAbilitySlot(i, eSlotState_Normal, m_pAbilitySlots[i]->m_iconName);
		}
	}
	else
	{
		//���UIͼ��
		for(int i=0; i<MAX_ABILITY_SLOT; ++i)
		{
			if(m_pAbilitySlots[i])
				CGUIManager::GetSingleton().GetCommandPanel()->CEGUI_SetAbilitySlot(i, eSlotState_Empty);
		}
	}
}

void Building::SetAbility( int slotIndex, const SAbilityData* pData )
{
	assert(slotIndex>=0 && slotIndex < MAX_ABILITY_SLOT);
	m_pAbilitySlots[slotIndex] = (SAbilityData*)pData;
}
