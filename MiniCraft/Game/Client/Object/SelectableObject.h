/********************************************************************
	created:	23:1:2013   1:06
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\Selectable.h
	author:		maval
	
	purpose:	��ѡ���������.��ѡ�������ܹ�ӵ�м���Command.
*********************************************************************/

#ifndef SelectableObject_h__
#define SelectableObject_h__

#include "ObjectBase.h"
#include "GameDefine.h"
#include "GameDataDef.h"

class AiComponent;

///����ʵ������OgreProcedural��
class SelectableObject : public RenderableObject
{
public:
	SelectableObject();
	~SelectableObject();

public:
	virtual	void	Update(float dt);
	//!!��Ogre Root����ǰ�������
	static void		ReleaseMeshCache();

	void			SetSelected(bool bSelected);
	bool			GetSelected() const { return m_bSelected; }

	void			SetAbility(int slotIndex, const SAbilityData* pData);
	void			ExcuteCommand(int slotIndex);

private:
	Ogre::MeshPtr	_CreateSelectionCircleMesh(const Ogre::MeshPtr& objMesh);
	void			_OnSelected(bool bSelected);

	typedef std::unordered_map<STRING, Ogre::MeshPtr>	SelectionCircleCache;
	static SelectionCircleCache	m_selCircleCache;	//cacheÿ�ֵ�λ��ѡ�п�mesh
	bool						m_bSelected;		//�ö����Ƿ�ѡ��
	Ogre::SceneNode*			m_pSelCircleNode;
	SAbilityData*				m_pAbilitySlots[MAX_ABILITY_SLOT];
	AiComponent*				m_pAi;
};

#endif // SelectableObject_h__