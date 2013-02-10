#include "stdafx.h"
#include "AIComponent.h"
#include "OgreDetourCrowd.h"
#include "World.h"
#include "SelectableObject.h"


AiComponent::AiComponent(SelectableObject* pOwner)
:m_pOwner(pOwner)
,m_bExecuting(false)
,m_curState(eObjectState_Idle)
{
	m_states.push_back(new StateIdle);
	m_states.push_back(new StateProduce);
}

AiComponent::~AiComponent()
{
	for(size_t i=0; i<m_states.size(); ++i)
		delete m_states[i];
	m_states.clear();
}

void AiComponent::GiveCommand( Command& cmd )
{
	if(m_cmdQueue.size() < MAX_COMMAND_QUEUE_LEN)
	{
		cmd.Excute();
		m_cmdQueue.push_back(cmd);
	}
}

// void AiComponent::CancelCurCommand()
// {
// // 	if(!m_pCurCommand)
// // 		return;
// // 
// // 	m_pCurCommand->Cancel();
// // 	delete m_pCurCommand;
// // 	m_pCurCommand = nullptr;
// }
// 
void AiComponent::SetCurState(eObjectState state)
{
 	//�˳���ǰ״̬
 	m_states[m_curState]->Exit(m_pOwner);
	//������״̬
 	m_states[state]->Enter(m_pOwner);
	m_curState = state;
}

void AiComponent::Update( float dt )
{
	m_states[m_curState]->Update(dt, m_pOwner);
}

void AiComponent::_OnCommandFinished()
{
	//�������������������Ƴ�
	m_cmdQueue.pop_front();
}

//////////////////////////////////////////////////////////////////////////////
AiPath::AiPath( SelectableObject* pOwner )
:AiComponent(pOwner)
,m_pRecast(g_Environment.m_pRecast)
,m_pDetour(g_Environment.m_pCrowd)
,m_pAgent(nullptr)
,m_agentID(-1)
{
	//ȷ����Ⱦʵ���Ѵ���
	assert(pOwner->IsRenderableReady());

	//����Ѱ·����
	m_agentID = m_pDetour->addAgent(pOwner->GetPosition());
	m_pAgent = const_cast<dtCrowdAgent*>(m_pDetour->getAgent(m_agentID));
	assert(m_pAgent);

	// 	//����λ����������Recast��
	// 	float scale = m_pDetour->getAgentRadius() / m_pEntity->getBoundingRadius();
	// 	m_pNode->setScale(scale, scale, scale);
}

AiPath::~AiPath()
{
	if(m_pAgent)
	{
		m_pDetour->removeAgent(m_agentID);
		m_pAgent = nullptr;
	}
}

bool AiPath::FindPath( const Ogre::Vector3& destPos )
{
	Ogre::Vector3 beginPos(m_pOwner->GetPosition());
	World::GetSingleton().ClampPosToNavMesh(beginPos);

	Ogre::Vector3 adjustDestPos(destPos);
	World::GetSingleton().ClampPosToNavMesh(adjustDestPos);

	int ret = m_pRecast->FindPath(beginPos, adjustDestPos, 1, 1);
	if( ret >= 0)
	{
		m_pDetour->setMoveTarget(m_agentID, adjustDestPos, false);
		//����·����
		m_pRecast->CreateRecastPathLine(1);
	}

	return ret >= 0;
}

const POS AiPath::GetAgentPos() const
{
	assert(m_pAgent->active);
	POS agentPos;
	OgreRecast::FloatAToOgreVect3(m_pAgent->npos, agentPos);

	return agentPos;
}