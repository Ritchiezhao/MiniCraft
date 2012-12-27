/********************************************************************
	created:	27:12:2012   0:04
	filename: 	F:\MiniCraft\Editor\SceneEdit\UI\TerrainPropertyPane.h
	author:		maval
	
	purpose:	�����������
*********************************************************************/

#ifndef TerrainPropertyPane_h__
#define TerrainPropertyPane_h__


#include "../resource.h"
#include "PropertiesPane.h"


class PropertyPaneTerrain : public CPropertiesPane
{
public:
	PropertyPaneTerrain():CPropertiesPane() {}
	~PropertyPaneTerrain() {}

	//����������ֵ��UI
	void	UpdateFromEngine();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnGridNotify(WPARAM, LPARAM);

private:
	std::unordered_map<int, CXTPPropertyGridItem*>	m_mapItem;
};


#endif // TerrainPropertyPane_h__














