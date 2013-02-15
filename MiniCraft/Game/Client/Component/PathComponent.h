/********************************************************************
	created:	14:2:2013   13:13
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\AI\PathComponent.h
	author:		maval
	
	purpose:	Ѱ·���,�߼�����ͨ�����ʹ�ø���
*********************************************************************/

#ifndef PathComponent_h__
#define PathComponent_h__

#include "GameDefine.h"
#include "Component.h"

class OgreRecast;
class OgreDetourCrowd;
struct dtCrowdAgent;
class SelectableObject;

///Ѱ·AI���
class PathComponent : public Component
{
public:
	PathComponent(SelectableObject* pOwner);
	~PathComponent();

public:
	virtual void	Update(float dt) {}
	bool			_UpdatePathFinding(float dt);
	//����Ѱ·.bJustTryΪtrue��ֻ�ǳ���Ŀ����Ƿ��Ѱ·
	bool			FindPath(const POS& destPos, bool bJustTry);
	//ֹͣѰ·
	bool			StopMove();
	const POS		GetAgentPos() const;
	void			SetDestPos(const POS& destPos);
	const POS&		GetDestPos() const	{ return m_destPos; }
	bool			IsMoving() const	{ return m_bIsMoving; }
	//����/�ر��谭���
	void			EnableObstcleAvoidance(bool bEnable);

private:
	OgreRecast*			m_pRecast;
	OgreDetourCrowd*	m_pDetour;
	dtCrowdAgent*		m_pAgent;
	int					m_agentID;
	POS					m_destPos;
	bool				m_bIsMoving;
};

#endif // PathComponent_h__