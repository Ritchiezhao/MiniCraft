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
#include "KratosPrerequisites.h"

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
		
	static void		InitRecastLib(const STRING& sceneName);
	static void		DestroyRecastLib();
	static void		UpdateRecastLib(float dt);
	//���Ե���������������Ч��NavMesh��
	static bool		ClampPosToNavMesh(POS& wPos);

public:
	virtual void	Update(float dt) {}
	bool			UpdatePathFinding(float dt);
	void			StopAgent();
	POS				GetRandomPositionOnNavmesh();
	//����Ѱ·.bJustTryΪtrue��ֻ�ǳ���Ŀ����Ƿ��Ѱ·
	bool			FindPath(POS& destPos, bool bJustTry);
	//ֹͣѰ·
	bool			StopMove();
	const POS		GetAgentPos() const;
	void			SetDestPos(const POS& destPos);
	POS&			GetDestPos()	{ return m_destPos; }
	bool			IsMoving() const	{ return m_bIsMoving; }
	//����/�ر��谭���
	void			EnableObstcleAvoidance(bool bEnable);

private:
	static OgreRecast*			m_pRecast;
	static OgreDetourCrowd*		m_pDetour;
	static OgreDetourTileCache*	m_pDetourTileCache;

	dtCrowdAgent*		m_pAgent;
	int					m_agentID;
	POS					m_destPos;
	bool				m_bIsMoving;
};

#endif // PathComponent_h__