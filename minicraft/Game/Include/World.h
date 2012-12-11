#ifndef WORLD_H
#define WORLD_H

#include "Singleton.h"


enum eQueryType
{
	eQueryType_Default	=	1<<0,
	eQueryType_WorldGeometry	=	1<<1,
	eQueryType_Unit		=	1<<2
};

namespace OgreBites
{
	class SdkCameraMan;
}

class Unit;
class OgreRecast;
class OgreDetourCrowd;

typedef	std::vector<Unit*>	UnitContainer;
/************************************************************************/
/*								���������                                */
/************************************************************************/

class World : public CSingleton<World>
{
	World();
	~World() {}
	DECLEAR_SINGLETON(World);
public:
	void	Init();
	void	Update(float dt);
	void	Shutdown();

	Ogre::Camera*	GetCamera()	{ return m_pCamera; }
	Unit*			CreateUnit(const Ogre::Vector3& pos);
	Unit*			GetUnitFromID(int ID);
	const Ogre::AxisAlignedBox&	GetResAABB() const { return m_pGold->getWorldBoundingBox(); }
	Ogre::Vector3	GetRandomPositionOnNavmesh();

	void			EnableFreeCamera(bool bEnable);
	bool			IsFreeCameraEnabled() { return m_bFreeCamMode; }
	OgreBites::SdkCameraMan*	GetCameraMan()	{ return m_cameraMan; }

	//����AABB������ѯ��������
	void			GetAABBSceneQueryResult(const Ogre::AxisAlignedBox& box, 
		std::vector<Ogre::MovableObject*>& result, int queryMask = 0xffffffff);
	//�������߳�����ѯ���ĵ�1������
	Ogre::MovableObject*	GetRaySceneQueryResult(const Ogre::Ray& ray, int queryMask = 0xffffffff);

	//���Ե���������������Ч��NavMesh��
	bool			ClampPosToNavMesh(Ogre::Vector3& wPos);

	//���õ�λΪѡ��״̬
	void			SetUnitSelected(int ID);
	//�������ѡ��״̬
	void			ClearAllUnitSelected();

	const UnitContainer&	GetAllUnitSelected() { return m_vecSelectUnis; }

private:
	UnitContainer				m_vecUnits;			//�����е����е�λ
	UnitContainer				m_vecSelectUnis;	//����ѡ�е�λ
	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::Camera*				m_pCamera;
	Ogre::Entity*				m_pGold;
	Ogre::AxisAlignedBoxSceneQuery*		m_pSceneQuery;
	Ogre::RaySceneQuery*		m_pRaySceneQuery;

	//RecastѰ·��
	OgreRecast*					m_pRecast;
	OgreDetourTileCache*		m_pDetourTileCache;
	OgreDetourCrowd*			m_pDetourCrowd;

	//���Թ۲��õ����˳������
	OgreBites::SdkCameraMan*	m_cameraMan;
	bool						m_bFreeCamMode;
};


#endif