#include "stdafx.h"
#include "UnitState.h"
#include "Unit.h"
#include "Command.h"



void IdleState::Enter()
{
	//�������ж���
	m_pIdleAnim = m_pOwner->GetEntity()->getAnimationState("IdleTop");
	assert(m_pIdleAnim);
	m_pIdleAnim->setEnabled(true);
	m_pIdleAnim->setTimePosition(0);
	m_pIdleAnim->setLoop(true);
}

void IdleState::Exit()
{
	m_pIdleAnim->setEnabled(false);
}

void IdleState::Update(float dt)
{
	m_pIdleAnim->addTime(dt);
}

MoveState::MoveState( Unit* pOwner )
:UnitState(pOwner)
,m_destPos(-1,-1,-1)
,m_pRunBaseAnim(nullptr)
,m_pRunTopAnim(nullptr)
{
	m_type = eUnitState_Move;
}

void MoveState::Enter()
{
	/// TODO:��λ״̬Ӧ�ò�����Command,��Ϊ״̬�仯��һ������Command�����
	MoveCommand* pCmd = dynamic_cast<MoveCommand*>(m_pOwner->GetCurCommand());
	assert(pCmd);
	m_destPos = pCmd->GetDestPos();

	if(!m_pOwner->FindPath(m_destPos))
	{
		//Ѱ·ʧ��,ת�����״̬
		m_pOwner->SetState(IdleState(m_pOwner));
		return;
	}

	//���ܶ���
	m_pRunBaseAnim = m_pOwner->GetEntity()->getAnimationState("RunBase");
	m_pRunTopAnim = m_pOwner->GetEntity()->getAnimationState("RunTop");
	assert(m_pRunBaseAnim && m_pRunTopAnim);

	m_pRunBaseAnim->setEnabled(true);
	m_pRunBaseAnim->setTimePosition(0);
	m_pRunBaseAnim->setLoop(true);

	m_pRunTopAnim->setEnabled(true);
	m_pRunTopAnim->setTimePosition(0);
	m_pRunTopAnim->setLoop(true);
}

void MoveState::Update( float dt )
{
	//���¶���
	m_pRunBaseAnim->addTime(dt);
	m_pRunTopAnim->addTime(dt);

	if(m_pOwner->GetAgent()->active) 
	{
		Ogre::Vector3 agentPos;
		OgreRecast::FloatAToOgreVect3(m_pOwner->GetAgent()->npos, agentPos);

		agentPos.y = m_pOwner->GetSceneNode()->_getDerivedPosition().y;
		//����Ѱ·
		m_pOwner->MoveTo(agentPos);

		//�Ƿ��ѵ���Ŀ�ĵ�
		if (agentPos.positionEquals(m_destPos, 1))
			m_pOwner->SetState(IdleState(m_pOwner));
	}
}

void MoveState::Exit()
{
	if(m_pRunBaseAnim)
		m_pRunBaseAnim->setEnabled(false);
	if(m_pRunTopAnim)
		m_pRunTopAnim->setEnabled(false);
}

