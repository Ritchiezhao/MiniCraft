/********************************************************************
	created:	27:12:2012   0:04
	filename: 	F:\MiniCraft\Editor\SceneEdit\UI\TerrainPropertyPane.h
	author:		maval
	
	purpose:	�����������
*********************************************************************/

#ifndef TerrainPropertyPane_h__
#define TerrainPropertyPane_h__


#include "PropertiesPane.h"


class PropertyPaneTerrain : public CPropertiesPane
{
public:
	enum ePropertyID
	{
		////property range [propStart, propEnd)
		propStart = 0,
		////These are ReadOnly items
		propWorldSize = 0,
		propMapSize,
		propMinBatchSize,
		propMaxBatchSize,
		propSkirtSize,
		propLayerNormalMap0,
		propLayerNormalMap1,
		propLayerNormalMap2,
		propLayerNormalMap3,
		propLayerNormalMap4,
		////////These are Mutable items
		propMutableItemStart,
		propMaxPixelError = propMutableItemStart,
		propCompMapDist,

		propLayerWorldSize0,
		propLayerWorldSize1,
		propLayerWorldSize2,
		propLayerWorldSize3,
		propLayerWorldSize4,
		propLayerDiffuseMap0,
		propLayerDiffuseMap1,
		propLayerDiffuseMap2,
		propLayerDiffuseMap3,
		propLayerDiffuseMap4,
		propMutableItemEnd,
		propEnd = propMutableItemEnd
	};

public:
	PropertyPaneTerrain():CPropertiesPane() {}
	~PropertyPaneTerrain() {}

	//�������пؼ�����
	void	UpdateAllFromEngine();
	//���¿ؼ�����
	void	UpdateProperty(int id);
	//����/��ֹ�༭Mutable����(ReadOnly���ݲ���Ҫ��,�����Ͳ��ܱ༭)
	void	EnableMutableProperty(BOOL bEnable);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnGridNotify(WPARAM, LPARAM);

private:
	//����layer���������б�
	void			_CreateLayerTexList(int itemID);

private:
	std::unordered_map<int, CXTPPropertyGridItem*>	m_mapItem;
};


#endif // TerrainPropertyPane_h__














