/********************************************************************
	created:	14:2:2013   13:13
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\AI\PathComponent.h
	author:		maval
	
	purpose:	Ѱ·���,�߼�����ͨ�����ʹ�ø���
*********************************************************************/

#ifndef PathComponent_h__
#define PathComponent_h__

#include "GameDefine.h"
#include "Command.h"
#include "ObjectState.h"

class OgreRecast;
class OgreDetourCrowd;
struct dtCrowdAgent;
class SelectableObject;

///Ѱ·AI���
class PathComponent
{
public:
	PathComponent(SelectableObject* pOwner);
	~PathComponent();

public:
	//����Ѱ·.bJustTryΪtrue��ֻ�ǳ���Ŀ����Ƿ��Ѱ·
	bool			FindPath(const Ogre::Vector3& destPos, bool bJustTry);
	//ֹͣѰ·
	bool			StopMove();
	const POS		GetAgentPos() const;

private:
	SelectableObject*	m_pOwner;		//�������������
	OgreRecast*			m_pRecast;
	OgreDetourCrowd*	m_pDetour;
	dtCrowdAgent*		m_pAgent;
	int					m_agentID;
};

#endif // PathComponent_h__