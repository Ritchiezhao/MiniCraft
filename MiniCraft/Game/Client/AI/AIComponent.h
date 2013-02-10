/********************************************************************
	created:	21:1:2013   23:36
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\AI\AiComponent.h
	author:		maval
	
	purpose:	AI���,�߼�����ͨ�����ʹ�ø���
*********************************************************************/

#ifndef AIComponent_h__
#define AIComponent_h__

#include "GameDefine.h"
#include "Command.h"
#include "ObjectState.h"

class OgreRecast;
class OgreDetourCrowd;
struct dtCrowdAgent;
class SelectableObject;

///AI�������
class AiComponent
{
public:
	AiComponent(SelectableObject* pOwner);
	virtual ~AiComponent();

public:
	void			Update(float dt);
	void			GiveCommand(Command& cmd);
	void			SetCurState(eObjectState state);
	eObjectState	GetCurState() const { return m_curState; }

	//��ǰ�������,�ӵ�֪ͨ
	void			_OnCommandFinished();

protected:
	typedef std::vector<ObjectState*>	StateLib;
	StateLib			m_states;		//״̬����.ÿ��״ֻ̬����һ��ʵ���洢�����﹩ȡ��

	typedef std::list<Command> CommandQueue;
	CommandQueue		m_cmdQueue;		//�������

	SelectableObject*	m_pOwner;		//�������������
	bool				m_bExecuting;	//��ǰ�Ƿ���ִ������
	eObjectState		m_curState;		//����ǰ����״̬
};

///Ѱ·AI���
class AiPath : public AiComponent
{
public:
	AiPath(SelectableObject* pOwner);
	~AiPath();

public:
	bool			FindPath(const Ogre::Vector3& destPos);
	const POS		GetAgentPos() const;

private:
	OgreRecast*			m_pRecast;
	OgreDetourCrowd*	m_pDetour;
	dtCrowdAgent*		m_pAgent;
	int					m_agentID;
};

#endif // AIComponent_h__