#include "stdafx.h"
#include "HarvestComponent.h"
#include "PathComponent.h"
#include "SelectableObject.h"
#include "Resource.h"
#include "Unit.h"
#include "World.h"
#include "Faction.h"
#include "Building.h"
#include "OgreManager.h"
#include "AnimatedComponent.h"
#include "ObjectState.h"
#include "AIComponent.h"

HarvestComponent::HarvestComponent( SelectableObject* pOwner )
:Component(pOwner)
,m_pTarget(nullptr)
,m_bCarried(false)
,m_curStage(eHarvestStage_None)
,m_fGatherTime(0)
{
	assert(m_pOwner->IsRenderableReady());

	m_pCrystal = RenderManager.CreateEntityWithTangent("Crystal_0.mesh", RenderManager.m_pSceneMgr);
	assert(m_pCrystal);
	Ogre::SceneNode* pNode = m_pOwner->GetSceneNode()->createChildSceneNode(POS(0, 0, 0.3f));
	pNode->setScale(2,2,2);
	pNode->attachObject(m_pCrystal);
	m_pCrystal->setVisible(false);
}

void HarvestComponent::Update( float dt )
{
	if(m_pOwner->GetAi()->GetCpuControl() || m_curStage == eHarvestStage_None)
		return;

	assert(m_pTarget);

	if (m_bCarried && m_curStage != eHarvestStage_Return)
		m_curStage = eHarvestStage_Return;

	//逻辑处理
	PathComponent* path = m_pOwner->GetPath();
	if (m_curStage == eHarvestStage_ToRes)
	{
		if (!path->IsMoving())
		{
			//向资源移动
			const POS& destPos = m_pTarget->GetPosition();
			path->SetDestPos(destPos);

			StateMove tmpState;
			tmpState.Enter(m_pOwner);
		}
		else if (path->UpdatePathFinding(dt))
		{
			//到达目的点
			m_pOwner->GetAnim()->PlayAnimation(eAnimation_Gather, true);
			m_fGatherTime = 0;
			SetCurStage(eHarvestStage_Gather);
		}
	}
	else if (m_curStage == eHarvestStage_Gather)
	{
		//更新采集阶段
		m_fGatherTime += dt;
		const float GATHER_TIME = 4;
		if (m_fGatherTime > GATHER_TIME)
		{
			//减少目标资源剩余数量
			m_pTarget->DecreaseRes(m_pTarget->GetGatherOnceNum());

			m_pCrystal->setVisible(true);
			m_bCarried = true;
			SetCurStage(eHarvestStage_Return);
		}
	}
	else/* if(m_curStage == eHarvestStage_Return)*/
	{
		int race = Ogre::StringConverter::parseInt(m_pOwner->getParameter("race"));
		Faction* player = World::GetSingleton().GetFaction((eGameRace)race);

		if(!path->IsMoving())
		{
			//向基地移动
			POS destPos = player->GetBase()->GetPosition();
			PathComponent::ClampPosToNavMesh(destPos);
			path->SetDestPos(destPos);

			StateMove tmpState;
			tmpState.Enter(m_pOwner);
		}
		else if(path->UpdatePathFinding(dt))	//到达目的点
		{
			//返还资源
			player->AddMineral(m_pTarget->GetGatherOnceNum());

			m_pCrystal->setVisible(false);
			m_bCarried = false;
			//循环状态
			SetCurStage(eHarvestStage_ToRes);
		}
	}
}

void HarvestComponent::SetResVisible( bool bVisible )
{
	m_pCrystal->setVisible(bVisible);
}
