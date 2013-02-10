#include "stdafx.h"
#include "ObjectState.h"
#include "GUIManager.h"
#include "SelectableObject.h"
#include "AIComponent.h"
#include "Building.h"
#include "ObjectManager.h"

void StateProduce::Enter(SelectableObject* pOwner)
{
	UiInfoPanel* panel = CGUIManager::GetSingleton().GetInfoPanel();
	panel->ShowInfoIcon(true, pOwner->GetActiveAbility()->m_iconName);
	panel->ShowProgressQueue(true);
}

void StateProduce::Update( float dt, SelectableObject* pOwner )
{
	Building* pObj = dynamic_cast<Building*>(pOwner);
	float fProgress = pObj->GetCurProgress();
	SUnitData* unitData = &GameDataDefManager::GetSingleton().m_unitData[pOwner->GetActiveAbility()->m_param];

	if (fProgress > unitData->m_fTimeCost)
	{
		//�������
		pOwner->GetAiComponent()->SetCurState(eObjectState_Idle);
		//�ʻ�ĵ�λ��¯��
		Object* pUnit = ObjectManager::GetSingleton().CreateObject(eObjectType_Unit);
		pUnit->setParameter("meshname", unitData->m_meshname);
		pUnit->setParameter("position", /*pOwner->getParameter("position")*/"0 0 0");
		pUnit->setParameter("scale", "5 5 5");
	}
}

void StateProduce::Exit(SelectableObject* pOwner)
{
	pOwner->_OnCommandFinished(eCommandType_Produce);
	UiInfoPanel* panel = CGUIManager::GetSingleton().GetInfoPanel();
	panel->SetVisible(false);
}
