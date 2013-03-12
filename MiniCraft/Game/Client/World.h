#ifndef WORLD_H
#define WORLD_H

#include "Singleton.h"
#include "GameDefine.h"
#include "SceneSerializer.h"
#include "KratosPrerequisites.h"

class SelectableObject;
class OgreRecast;
class OgreDetourCrowd;
class Faction;
class UiCommandPanel;
class UiInfoPanel;
class UiPortraitPanel;
class Scene;

//���ó�Աȫ�ֻ���
struct SGlobalEnvironment 
{
	SGlobalEnvironment() { Reset(); }
	void	Reset() { m_pRecast=nullptr; m_pCrowd=nullptr; } 

	OgreRecast*			m_pRecast;
	OgreDetourCrowd*	m_pCrowd;
};

extern SGlobalEnvironment	g_Environment;


namespace OgreBites
{
	class SdkCameraMan;
}

typedef	std::vector<SelectableObject*>	SelectedContainer;
/************************************************************************/
/*								���������                                */
/************************************************************************/

class World : public CSingleton<World>, public Kratos::SceneSerializer
{
	World();
	~World();
	DECLEAR_SINGLETON(World);

protected:
	///////////////////��дSceneSerializer����
	virtual void	_LoadObjects(rapidxml::xml_node<>* node);

public:
	void	Init();
	void	Update(float dt);
	void	Shutdown();

	const Ogre::AxisAlignedBox&	GetResAABB() const { return m_pGold->getWorldBoundingBox(); }
	POS				GetRandomPositionOnNavmesh();

	void			EnableFreeCamera(bool bEnable);
	bool			IsFreeCameraEnabled() { return m_bFreeCamMode; }
	OgreBites::SdkCameraMan*	GetCameraMan()	{ return m_cameraMan; }

	//����AABB������ѯ��������
	void			GetAABBSceneQueryResult(const Ogre::AxisAlignedBox& box, 
		std::vector<Ogre::MovableObject*>& result, int queryMask = 0xffffffff);
	//�������߳�����ѯ���ĵ�1������
	Ogre::MovableObject*	GetRaySceneQueryResult(const Ogre::Ray& ray, int queryMask = 0xffffffff);

	//���Ե���������������Ч��NavMesh��
	bool			ClampPosToNavMesh(POS& wPos);
	//���ö���Ϊѡ��״̬
	void			SetObjectSelected(int ID);
	//�������ѡ��״̬
	void			ClearSelectedState();

	const SelectedContainer&	GetSelectedObjects() { return m_vecSelectUnis; }
	//��������������ͨ������Ͷ��г��ڵ�����
	void			ClampToTerrain(POS& pos);
	//��һ�������һ�����¿���̨UI
	void			UpdateConsoleUITransform(float dt);
	//���������������εĽ���,û�ཻ����false
	bool			GetTerrainIntersectPos(const FLOAT2& screenPos, POS& retPt);
	//��ȡ�����ϵ
	Faction*		GetFaction(eGameRace race) { return m_player[race]; }

	///��ȡUI���
	UiCommandPanel*	GetCommandPanel() { return m_cmdPanel; }
	UiInfoPanel*	GetInfoPanel()	{ return m_infoPanel; }
	UiPortraitPanel* GetPortraitPanel() { return m_portraitPanel; }

private:
	SelectedContainer			m_vecSelectUnis;	//����ѡ�е�λ
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

	//UI console for test
	Ogre::SceneNode*			m_pUISceneNode1;
	Ogre::SceneNode*			m_pUISceneNode2;
	Ogre::SceneNode*			m_pUISceneNode3;
	Ogre::SceneNode*			m_pUISceneNode4;
	Ogre::AnimationState*		m_pConsoleAnim1;
	Ogre::AnimationState*		m_pConsoleAnim2;

	UiCommandPanel*				m_cmdPanel;
	UiInfoPanel*				m_infoPanel;
	UiPortraitPanel*			m_portraitPanel;

	Faction*					m_player[eGameRace_Count];
	Kratos::Scene*				m_pTestScene;
};


#endif