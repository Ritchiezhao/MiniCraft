/********************************************************************
	created:	23:1:2013   1:06
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\Selectable.h
	author:		maval
	
	purpose:	��ѡ���������.
*********************************************************************/

#ifndef Selectable_h__
#define Selectable_h__

#include "ObjectBase.h"
#include "GameDefine.h"


///����ʵ������OgreProcedural��
class SelectableObject : public RenderableObject
{
	typedef std::unordered_map<STRING, Ogre::MeshPtr>	SelectionCircleCache;

public:
	SelectableObject();
	~SelectableObject();

public:
	void	SetSelected(bool bSelected);
	bool	GetSelected() const { return m_bSelected; }

private:
	Ogre::MeshPtr	_CreateSelectionCircleMesh(const Ogre::MeshPtr& objMesh);

private:
	static SelectionCircleCache	m_selCircleCache;	//cacheÿ�ֵ�λ��ѡ�п�mesh

	bool						m_bSelected;		//�ö����Ƿ�ѡ��
	Ogre::SceneNode*			m_pSelCircleNode;

};

#endif // Selectable_h__