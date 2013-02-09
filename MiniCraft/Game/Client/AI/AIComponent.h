/********************************************************************
	created:	21:1:2013   23:36
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\AI\AiComponent.h
	author:		maval
	
	purpose:	AI���,�߼�����ͨ�����ʹ�ø���
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
class SelectableObject;

///AI�������
class AiComponent
{
public:
	AiComponent(SelectableObject* pOwner);
	virtual ~AiComponent() {}

public:
	void			Update(float dt);
	void			GiveCommand(const CommandBase& cmd);

// 	void			SetState(eUnitState state);
// 	UnitState*		GetCurState() const { return m_pCurState; }

protected:
	SelectableObject*	m_pOwner;		//�������������

	typedef std::list<const CommandBase*> CommandQueue;
	CommandQueue		m_cmdQueue;		//�������
	bool				m_bExecuting;	//��ǰ�Ƿ���ִ������
	//UnitState*			m_pCurState;	//��λ��ǰ״̬(�߼�״̬��)
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