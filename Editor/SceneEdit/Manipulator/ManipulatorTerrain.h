/********************************************************************
	created:	14:12:2012   0:52
	filename: 	F:\MiniCraft\Editor\SceneEdit\Manipulator\ManipulatorTerrain.h
	author:		maval
	
	purpose:	���β�����.
*********************************************************************/
#ifndef ManipulatorTerrain_h__
#define ManipulatorTerrain_h__

#include "ManipulatorEventCallback.h"

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


class ManipulatorTerrain : public ManipulatorSceneEventCallback
{
	friend class ManipulatorNavMesh;
public:
	ManipulatorTerrain();
	~ManipulatorTerrain();

	//////////////�¼��ص�
	virtual void	OnSceneNew();
	virtual void	OnSceneOpen();
	virtual void	OnSceneClose();
	
	enum eTerrainEditMode
	{
		eTerrainEditMode_None,
		eTerrainEditMode_Deform,
		eTerrainEditMode_Splat
	};

public:
	void	Serialize(rapidxml::xml_document<>* doc, rapidxml::xml_node<>* XMLNode);
	void	OnGizmoNodeReset();
	float	GetHeightAt(const Ogre::Vector2& worldPos);
	bool	GetRayIntersectPoint(const Ogre::Ray& worldRay, Ogre::Vector3& retPt);
	float	GetWorldSize() const;
	size_t	GetMapSize() const;
	float	GetMaxPixelError() const;
	float	GetSkirtSize() const;
	int		GetMinBatchSize() const;
	int		GetMaxBatchSize() const;
	float	GetCompositeMapDist() const;

	void	SetMaxPixelError(float f);
	void	SetSkirtSize(float f);
	void	SetCompositeMapDist(float f);

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
	const Ogre::StringVector& GetAllLayerTexThumbnailNames();

	///���û�ȡLayer���
	void	SetLayerTexWorldSize(int nLayer, float fSize);
	float	GetLayerTexWorldSize(int nLayer);
	void	SetLayerTexture(int nLayer, const std::string& diffuseMapName);
	void	SetLayerTexture(int nLayer, int diffuseID);
	const std::string GetLayerDiffuseMap(int nLayer) const;
	const std::string GetLayerNormalMap(int nLayer) const;

	//���õ�ǰ�༭layer
	void	SetCurEditLayer(int nLayer) { m_curEditLayer = nLayer; }
	int		GetCurEditLayer() const { return m_curEditLayer; }

private:
	Ogre::StringVector						m_vecLayerTex;		//��ˢ���õ�����������
	std::unique_ptr<Brush>					m_brush[2]; //0:cirle 1:square
	int										m_curBrushIndex;
	eTerrainEditMode						m_curEditMode;
	int										m_curEditLayer;					
};





#endif // ManipulatorTerrain_h__







