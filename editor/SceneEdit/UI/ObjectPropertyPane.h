/********************************************************************
	created:	8:1:2013   0:54
	filename: 	F:\MiniCraft\Editor\SceneEdit\UI\ObjectPropertyPane.h
	author:		maval
	
	purpose:	�����������
*********************************************************************/

#ifndef ObjectPropertyPane_h__
#define ObjectPropertyPane_h__


#include "PropertiesPane.h"

class CXTPPropertyGridItemVec3;

class PropertyPaneObject : public CPropertiesPane
{
public:
	enum ePropertyID
	{
		////property range [propStart, propEnd)
		propStart = 0,
		////These are ReadOnly items
		propMeshName = propStart,
		////////These are Mutable items
		propMutableItemStart,
		propPosition = propMutableItemStart,
		propOrientation,
		propScale,
		propAddToNavmesh,
		propIsBuilding,
		propMutableItemEnd,
		propEnd = propMutableItemEnd,

		//Auto managed property
		propPosX, propPosY, propPosZ,
		propOrientX, propOrientY, propOrientZ, propOrientW,
		propScaleX, propScaleY, propScaleZ
	};

public:
	PropertyPaneObject():CPropertiesPane() {}
	~PropertyPaneObject() {}

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
	Ogre::Vector3	_UpdateVec3ItemProperty(CXTPPropertyGridItemVec3* pItem);

	std::unordered_map<int, CXTPPropertyGridItem*>	m_mapItem;
};


#endif // ObjectPropertyPane_h__














