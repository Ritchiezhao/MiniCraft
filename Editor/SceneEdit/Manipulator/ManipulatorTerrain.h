/********************************************************************
	created:	14:12:2012   0:52
	filename: 	F:\MiniCraft\Editor\SceneEdit\Manipulator\ManipulatorTerrain.h
	author:		maval
	
	purpose:	���β�����.
*********************************************************************/
#ifndef ManipulatorTerrain_h__
#define ManipulatorTerrain_h__

namespace Ogre
{
	class Terrain;
	class TerrainGlobalOptions;
	class TerrainGroup;
	class SceneManager;
}
using Ogre::Terrain;
using Ogre::TerrainGlobalOptions;
using Ogre::TerrainGroup;

#include "../Brush.h"


class ManipulatorTerrain
{
public:
	ManipulatorTerrain();
	~ManipulatorTerrain() {}
	
	enum eTerrainEditMode
	{
		eTerrainEditMode_None,
		eTerrainEditMode_Deform,
		eTerrainEditMode_Splat
	};

public:
	void	NewFlatTerrain();
	void	Shutdown();
	void	Load(rapidxml::xml_node<>* XMLNode);
	void	Serialize(rapidxml::xml_document<>& doc, rapidxml::xml_node<>* XMLNode);

	void	OnGizmoNodeReset();
	float	GetHeightAt(const Ogre::Vector2& worldPos);
	bool	GetRayIntersectPoint(const Ogre::Ray& worldRay, Ogre::Vector3& retPt);
	float	GetWorldSize() const { assert(m_terrainGroup); return m_terrainGroup->getTerrainWorldSize(); }
	size_t	GetMapSize() const	{ assert(m_terrainGroup); return m_terrainGroup->getTerrainSize(); }

	//brush stuff
	void	SetBrushPosition(const Ogre::Vector3& pos);
	void	SetSquareBrushWidth(float w);
	void	SetSquareBrushHeight(float h);
	float	GetSquareBrushWidth();
	float	GetSquareBrushHeight();

	void	OnEdit(float dt);
	//deform
	void	SetTerrainDeformEnabled(bool bEnable);
	bool	GetTerrainDeformEnabled() { return m_curEditMode == eTerrainEditMode_Deform; }

	//splat
	void	SetTerrainSplatEnabled(bool bEnable);
	bool	GetTerrainSplatEnabled() { return m_curEditMode == eTerrainEditMode_Splat; }

private:
	void	_ConfigureTerrainDefaults();

private:
	std::unique_ptr<TerrainGroup>			m_terrainGroup;
	std::unique_ptr<TerrainGlobalOptions>	m_terrainOption;
	Terrain*								m_pTerrain;			//Ŀǰ����һ�����
	Ogre::SceneManager*						m_pSceneMgr;

	int										m_vertexPerSide;	//����ÿ�ߵĶ�����
	float									m_worldSize;		//���η�Χ
	Ogre::Vector3							m_origPos;			//����ԭ��

	std::unique_ptr<Brush>					m_brush[2]; //0:cirle 1:square
	int										m_curBrushIndex;
	eTerrainEditMode						m_curEditMode;
};





#endif // ManipulatorTerrain_h__







