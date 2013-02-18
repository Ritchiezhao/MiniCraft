/********************************************************************
	created:	17:2:2013   0:48
	filename: 	F:\MiniCraft\Kratos\Src\Scene.h
	author:		maval
	
	purpose:	��Ϸ������
*********************************************************************/

#ifndef Scene_h__
#define Scene_h__

#include <OgrePrerequisites.h>
#include <OgreVector3.h>
#include <OgreColourValue.h>

namespace Ogre
{
	class TerrainGroup;
	class TerrainGlobalOptions;
	class Terrain;
}

class SceneSerializer;

class Scene
{
	friend class SceneSerializer;
public:
	Scene(Ogre::SceneManager* pSceneMgr);
	~Scene() {}

public:
	void	Load(const std::string& sceneName, const std::string& sceneGroup, SceneSerializer* pHandler);
	void	Load(const std::string& fullPath, SceneSerializer* pHandler);
	void	Save(const std::string& fullPath, SceneSerializer* pHandler);
	void	Reset();

	Ogre::TerrainGroup*			GetTerrainGroup() { return m_terrainGroup; }
	Ogre::TerrainGlobalOptions* GetTerrainOption() { return m_terrainOption; }
	Ogre::Terrain*				GetTerrain() { return m_pTerrain; }
	const Ogre::Vector3&		GetSunLightDirection() const { return m_sunLightDir; }
	const Ogre::ColourValue&	GetSunLightDiffuse() const { return m_sunLightDiffuse; }

private:
	Ogre::TerrainGroup*			m_terrainGroup;
	Ogre::TerrainGlobalOptions*	m_terrainOption;
	Ogre::Terrain*				m_pTerrain;
	Ogre::SceneManager*			m_pSceneMgr;
	Ogre::Vector3				m_sunLightDir;			//ȫ�ֹⷽ��
	Ogre::ColourValue			m_sunLightDiffuse;		//ȫ�ֹ���ɫ
};

#endif // Scene_h__