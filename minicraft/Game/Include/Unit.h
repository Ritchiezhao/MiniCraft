#ifndef UNIT_H
#define UNIT_H


enum QueryFlags {
	DEFAULT_MASK = 1u<<0,
	NAVMESH_MASK = 1u<<1,
	OBSTACLE_MASK= 1u<<2
};

class CommandBase;
class OgreRecast;
class OgreDetourCrowd;
class UnitState;
struct dtCrowdAgent;

/************************************************************************/
/*							��Ϸ��λ��	                                */
/************************************************************************/

class Unit
{
public:
	Unit(Ogre::Entity* pEnt, Ogre::SceneNode* pNode, OgreRecast* pRecast, OgreDetourCrowd* pDetour);
	~Unit() {}
public:
	Ogre::SceneNode*	GetSceneNode() { return m_pNode; }
	Ogre::Entity*	GetEntity() { return m_pEntity; }
	//ָ��һ��ִ������
	void			GiveCommand(const CommandBase& cmd);
	//��ȡ��ǰ����
	CommandBase*	GetCurCommand() const { return m_pCurCommand; }
	//ȡ����ǰ����
	void			CancelCurCommand();
	//���õ�ǰ״̬
	void			SetState(const UnitState& newState);
	//���µ�λ
	void			Update(float dt);
	//����Ѱ·
	bool			FindPath(const Ogre::Vector3& destPos);
	
	void			MoveTo(const Ogre::Vector3& destPos);
	dtCrowdAgent*	GetAgent() { return m_pAgent; }

private:
	Ogre::Entity*		m_pEntity;
	Ogre::SceneNode*	m_pNode;
	OgreRecast*			m_pRecast;
	OgreDetourCrowd*	m_pDetour;
	dtCrowdAgent*		m_pAgent;		//Ѱ·����
	int					m_agentID;
	CommandBase*		m_pCurCommand;	//��ǰ����
	UnitState*			m_pCurState;	//��λ��ǰ״̬(�߼�״̬��)
};


#endif