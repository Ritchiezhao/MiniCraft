/********************************************************************
	created:	21:1:2013   23:36
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\AI\AIComponent.h
	author:		maval
	
	purpose:	AI���,��������ͨ�����ʹ�ø���
*********************************************************************/

#ifndef AIComponent_h__
#define AIComponent_h__

#include "UnitState.h"
#include "GameDefine.h"

class CommandBase;
class OgreRecast;
class OgreDetourCrowd;
class UnitState;
struct dtCrowdAgent;
class RenderableObject;

class AIComponent
{
public:
	AIComponent(RenderableObject* pOwner);
	~AIComponent();

public:
	void			Update(float dt);
	//ָ��һ��ִ������
	void			GiveCommand(const CommandBase& cmd);
	//��ȡ��ǰ����
	CommandBase*	GetCurCommand() const { return m_pCurCommand; }
	//ȡ����ǰ����
	void			CancelCurCommand();
	//���õ�ǰ״̬
	void			SetState(eUnitState state);
	//��ȷѰ·
	bool			FindPath(const Ogre::Vector3& destPos);
	UnitState*		GetCurState() const { return m_pCurState; }
	const POS		GetAgentPos() const;

private:
	RenderableObject*	m_pOwner;		//�������������
	OgreRecast*			m_pRecast;
	OgreDetourCrowd*	m_pDetour;
	dtCrowdAgent*		m_pAgent;
	int					m_agentID;
	CommandBase*		m_pCurCommand;	//��ǰ����
	UnitState*			m_pCurState;	//��λ��ǰ״̬(�߼�״̬��)
};

#endif // AIComponent_h__