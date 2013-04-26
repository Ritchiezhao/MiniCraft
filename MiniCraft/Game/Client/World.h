#ifndef WORLD_H
#define WORLD_H

#include "Singleton.h"
#include "GameDefine.h"
#include "SceneSerializer.h"
#include "KratosPrerequisites.h"
#include "ScriptSystem.h"

class SelectableObject;
class OgreRecast;
class OgreDetourCrowd;
class Faction;
class UiCommandPanel;
class UiInfoPanel;
class UiPortraitPanel;

//���ó�Աȫ�ֻ���
struct SGlobalEnvironment 
{
	SGlobalEnvironment() { Reset(); }
	void	Reset() 
	{ 
		m_pRecast=nullptr; 
		m_pCrowd=nullptr; 
		m_pDetourTileCache=nullptr; 
	} 

	OgreRecast*				m_pRecast;
	OgreDetourCrowd*		m_pCrowd;
	OgreDetourTileCache*	m_pDetourTileCache;
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

class World : public CSingleton<World>, private Kratos::SceneSerializer
{
	World();
	~World();
	DECLEAR_SINGLETON(World);

protected:
	///////////////////��дSceneSerializer����
	virtual void	_LoadObjects(rapidxml::xml_node<>* node);

public:
	static const char className[];
	static Luna<World>::RegType methods[];
	World(lua_State* L) {}
	///////////////////////////////////////////
	/////////////lua��������
	int		GetPlayerUnitNum(lua_State* L);
	int		SetGlobalBBParam_Int(lua_State* L);
	int		SetGlobalBBParam_Float(lua_State* L);
	int		SetGlobalBBParam_Bool(lua_State* L);

public:
	void	Init();
	void	Update(float dt);
	void	Shutdown();

	Kratos::Scene*	GetScene()	{ return m_pTestScene; }
	void			EnableFreeCamera(bool bEnable);
	bool			IsFreeCameraEnabled() { return m_bFreeCamMode; }
	OgreBites::SdkCameraMan*	GetCameraMan()	{ return m_cameraMan; }

	//AABB������ѯ
	void			GetAABBSceneQueryResult(const Ogre::AxisAlignedBox& box, 
		std::vector<Ogre::MovableObject*>& result, int mask = eQueryType_All);
	//���߳�����ѯ
	Ogre::MovableObject*	GetRaySceneQueryResult(const OIS::MouseEvent& arg, 
		int mask = eQueryType_All, POS* retIntersect = nullptr);
	//���γ�����ѯ
	void			GetSphereSceneQueryResult(const Ogre::Sphere& s, 
		std::vector<Ogre::MovableObject*>& result, int mask = eQueryType_All);

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
	//test
	void			StartRagdoll();

	///��ȡUI���
	UiCommandPanel*	GetCommandPanel() { return m_cmdPanel; }
	UiInfoPanel*	GetInfoPanel()	{ return m_infoPanel; }
	UiPortraitPanel* GetPortraitPanel() { return m_portraitPanel; }

private:
	Kratos::ScriptSystem*		m_pScriptSystem;
	Kratos::COgreManager*		m_pRenderSystem;

	SelectedContainer			m_vecSelectUnis;	//����ѡ�е�λ
	Ogre::AxisAlignedBoxSceneQuery*	m_pSceneQuery;
	Ogre::RaySceneQuery*		m_pRaySceneQuery;
	Ogre::SphereSceneQuery*		m_pSphereSceneQuery;

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