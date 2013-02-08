#include "stdafx.h"
#include "AIComponent.h"
#include "OgreDetourCrowd.h"
#include "Command.h"
#include "World.h"
#include "ObjectBase.h"


AIComponent::AIComponent(RenderableObject* pOwner)
:m_pOwner(pOwner)
,m_pRecast(g_Environment.m_pRecast)
,m_pDetour(g_Environment.m_pCrowd)
,m_pCurState(nullptr)
,m_pCurCommand(nullptr)
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

AIComponent::~AIComponent()
{
	if(m_pAgent)
	{
		m_pDetour->removeAgent(m_agentID);
		m_pAgent = nullptr;
	}
}

void AIComponent::GiveCommand( const CommandBase& cmd )
{
// 	//ֹͣ��ǰ����
// 	if (m_pCurCommand)
// 		CancelCurCommand();
// 
// 	//����������
// 	switch (cmd.GetType())
// 	{
// 	case eCommandType_Move:		m_pCurCommand = new MoveCommand; break;
// 	case eCommandType_Attack:	m_pCurCommand = new AttackCommand; break;
// 	case eCommandType_Build:	m_pCurCommand = new BuildCommand; break;
// 	case eCommandType_Harvest:	m_pCurCommand = new HarvestCommand; break;
// 	}
// 	m_pCurCommand->Clone(cmd);
// 
// 	//ִ��������
// 	m_pCurCommand->Excute();
}

void AIComponent::CancelCurCommand()
{
// 	if(!m_pCurCommand)
// 		return;
// 
// 	m_pCurCommand->Cancel();
// 	delete m_pCurCommand;
// 	m_pCurCommand = nullptr;
}

void AIComponent::SetState( eUnitState state )
{
// 	//�˳���ǰ״̬
// 	if(m_pCurState)
// 	{
// 		m_pCurState->Exit();
// 		delete m_pCurState;
// 	}
// 	//������״̬
// 	switch (state)
// 	{
// 	case eUnitState_Idle:		m_pCurState = new IdleState(this); break;
// 	case eUnitState_Move:		m_pCurState = new MoveState(this); break;
// 	case eUnitState_Attack:		m_pCurState = new AttackState(this); break;
// 	case eUnitState_Build:		m_pCurState = new BuildState(this); break;
// 	case eUnitState_Collect:	m_pCurState = new CollectResState(this); break;
// 	case eUnitState_Return:		m_pCurState = new ReturnResState(this); break;
// 	default:					assert(0);
// 	}
// 
// 	m_pCurState->Enter();
}

void AIComponent::Update( float dt )
{
	m_pCurState->Update(dt);
}

bool AIComponent::FindPath( const Ogre::Vector3& destPos )
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

const POS AIComponent::GetAgentPos() const
{
	assert(m_pAgent->active);
	POS agentPos;
	OgreRecast::FloatAToOgreVect3(m_pAgent->npos, agentPos);

	return agentPos;
}


