/********************************************************************
	created:	23:1:2013   1:06
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\Selectable.h
	author:		maval
	
	purpose:	��ѡ���������.
*********************************************************************/

#ifndef SelectableObject_h__
#define SelectableObject_h__

#include "ObjectBase.h"
#include "GameDefine.h"
#include "Ability.h"


///����ʵ������OgreProcedural��
class SelectableObject : public RenderableObject
{
public:
	SelectableObject();
	~SelectableObject();

public:
	void	SetSelected(bool bSelected);
	bool	GetSelected() const { return m_bSelected; }

	//!!��Ogre Root����ǰ�������
	static void	ReleaseMeshCache();

protected:
	//������б�ѡ����Ϊ���ػ�
	virtual	void	OnSelected(bool bSelected) {}

private:
	Ogre::MeshPtr	_CreateSelectionCircleMesh(const Ogre::MeshPtr& objMesh);

	typedef std::unordered_map<STRING, Ogre::MeshPtr>	SelectionCircleCache;
	static SelectionCircleCache	m_selCircleCache;	//cacheÿ�ֵ�λ��ѡ�п�mesh
	bool						m_bSelected;		//�ö����Ƿ�ѡ��
	Ogre::SceneNode*			m_pSelCircleNode;

	typedef std::vector<Ability>	AbilitySlots;
	AbilitySlots				m_abilities;		//�����������
};

#endif // SelectableObject_h__