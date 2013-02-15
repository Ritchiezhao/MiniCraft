#include "stdafx.h"
#include "HarvestComponent.h"
#include "PathComponent.h"
#include "SelectableObject.h"
#include "Resource.h"
#include "Unit.h"
#include "World.h"
#include "Faction.h"
#include "Building.h"

HarvestComponent::HarvestComponent( SelectableObject* pOwner )
:Component(pOwner)
,m_pTarget(nullptr)
,m_bCarried(false)
,m_curStage(eHarvestStage_None)
,m_fGatherTime(0)
{
	assert(m_pOwner->IsRenderableReady());

	m_pCrystal = g_Environment.m_pSceneMgr->createEntity("Crystal_0.mesh");
	assert(m_pCrystal);
	Ogre::SceneNode* pNode = m_pOwner->GetSceneNode()->createChildSceneNode(POS(0, 0, 0.3f));
	pNode->setScale(2,2,2);
	pNode->attachObject(m_pCrystal);
	m_pCrystal->setVisible(false);
}

void HarvestComponent::Update( float dt )
{
	if(m_curStage == eHarvestStage_None)
		return;

	assert(m_pTarget);

	if (m_bCarried && m_curStage != eHarvestStage_Return)
		m_curStage = eHarvestStage_Return;

	//�߼�����
	PathComponent* path = m_pOwner->GetPath();
	if (m_curStage == eHarvestStage_ToRes)
	{
		if (!path->IsMoving())
		{
			//����Դ�ƶ�
			const POS& destPos = m_pTarget->GetPosition();
			path->SetDestPos(destPos);

			StateMove tmpState;
			tmpState.Enter(m_pOwner);
		}
		else if (path->_UpdatePathFinding(dt))
		{
			//����Ŀ�ĵ�
			Unit* pUnit = dynamic_cast<Unit*>(m_pOwner);
			pUnit->PlayAnimation(eAnimation_Gather, true);
			m_fGatherTime = 0;
			SetCurStage(eHarvestStage_Gather);
		}
	}
	else if (m_curStage == eHarvestStage_Gather)
	{
		//���²ɼ��׶�
		m_fGatherTime += dt;
		const float GATHER_TIME = 4;
		if (m_fGatherTime > GATHER_TIME)
		{
			//����Ŀ����Դʣ������
			m_pTarget->DecreaseRes(m_pTarget->GetGatherOnceNum());

			m_pCrystal->setVisible(true);
			m_bCarried = true;
			SetCurStage(eHarvestStage_Return);
		}
	}
	else/* if(m_curStage == eHarvestStage_Return)*/
	{
		const STRING& unitName = m_pOwner->getParameter("unitName");
		SUnitData* unitData = &GameDataDefManager::GetSingleton().m_unitData[unitName];
		Faction* player = World::GetSingleton().GetFaction(unitData->m_race);

		if(!path->IsMoving())
		{
			//������ƶ�
			POS destPos = player->GetBase()->GetPosition();
			World::GetSingleton().ClampPosToNavMesh(destPos);
			path->SetDestPos(destPos);

			StateMove tmpState;
			tmpState.Enter(m_pOwner);
		}
		else if(path->_UpdatePathFinding(dt))	//����Ŀ�ĵ�
		{
			//������Դ
			player->AddMineral(m_pTarget->GetGatherOnceNum());

			m_pCrystal->setVisible(false);
			m_bCarried = false;
			//ѭ��״̬
			SetCurStage(eHarvestStage_ToRes);
		}
	}
}
