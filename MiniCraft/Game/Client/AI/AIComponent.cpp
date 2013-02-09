#include "stdafx.h"
#include "AIComponent.h"
#include "OgreDetourCrowd.h"
#include "Command.h"
#include "World.h"
#include "SelectableObject.h"


AiComponent::AiComponent(SelectableObject* pOwner)
:m_pOwner(pOwner)
,m_bExecuting(false)
//,m_pCurState(nullptr)
{
	
}

void AiComponent::GiveCommand( const CommandBase& cmd )
{
	//if (!m_bExecuting && m_cmdQueue.empty())
	{
		cmd.Excute();
		m_bExecuting = true;
	}
	if(m_cmdQueue.size() < MAX_COMMAND_QUEUE_LEN)
		m_cmdQueue.push_back(&cmd);
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
// void AiComponent::SetState( eUnitState state )
// {
// // 	//�˳���ǰ״̬
// // 	if(m_pCurState)
// // 	{
// // 		m_pCurState->Exit();
// // 		delete m_pCurState;
// // 	}
// // 	//������״̬
// // 	switch (state)
// // 	{
// // 	case eUnitState_Idle:		m_pCurState = new IdleState(this); break;
// // 	case eUnitState_Move:		m_pCurState = new MoveState(this); break;
// // 	case eUnitState_Attack:		m_pCurState = new AttackState(this); break;
// // 	case eUnitState_Build:		m_pCurState = new BuildState(this); break;
// // 	case eUnitState_Collect:	m_pCurState = new CollectResState(this); break;
// // 	case eUnitState_Return:		m_pCurState = new ReturnResState(this); break;
// // 	default:					assert(0);
// // 	}
// // 
// // 	m_pCurState->Enter();
// }

void AiComponent::Update( float dt )
{

	//m_pCurState->Update(dt);
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