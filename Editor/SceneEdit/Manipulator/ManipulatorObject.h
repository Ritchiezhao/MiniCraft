/********************************************************************
	created:	20:12:2012   0:39
	filename: 	F:\MiniCraft\Editor\SceneEdit\Manipulator\ManipulatorObject.h
	author:		maval
	
	purpose:	�ɰڷ����崴��,����,�ٿ�.
*********************************************************************/

#ifndef ManipulatorObject_h__
#define ManipulatorObject_h__

#include "ManipulatorEventCallback.h"
#include "EditorDefine.h"

class GizmoAxis;

class ManipulatorObject : public ManipulatorSceneEventCallback
{
public:
	enum eEditMode
	{
		eEditMode_None,
		eEditMode_Move,
		eEditMode_Rotate,
		eEditMode_Scale,
		eEditMode_Select
	};

	//////////////�¼��ص�
	virtual void	OnSceneClose();
	virtual void	OnSceneNew();
	virtual void	OnSceneOpen();

public:
	ManipulatorObject();
	~ManipulatorObject();

public:
	void		OnFrameMove(float dt);
	eEditMode	GetCurEditMode() const { return m_curEditMode; }
	void		SetCurEditMode(eEditMode mode) { m_curEditMode = mode; }
	//����Entity
	bool		AddEntity(const Ogre::String& meshname, const Ogre::Vector3& worldPos);
	bool		AddEntity(const Ogre::String& meshname, const Ogre::Vector2& screenPos);
	///����ѡ��
	void		SetSelection(Ogre::Entity* pEnt);
	Ogre::Entity*	GetSelection() const { return m_pSelectEntity; }
	void		ClearSelection();
	//ȡ��Entity�İ�Χ��Gizmo.��Χ����ʾ�������Լ�����,��ʹ��OGREĬ�ϵ�showBoundingBox
	Ogre::WireBoundingBox*	GetEntityAABBGizmo(Ogre::Entity* pEntity);
	//�ƶ�����
	void		SelectionMove(const Ogre::Vector3& vecMove);
	//���ݲ���ģʽ,��ʾ������Ӧ��Gizmo
	void		ShowEntityGizmo(Ogre::Entity* pEntity, bool bShow, eEditMode mode, bool bDrift = false);
	void		HighlightGizmoAxis(bool bHighlight, eAxis axis);
	void		OnGizmoNodeReset();
	//���߲�ѯ
	Ogre::MovableObject* DoRaySceneQuery(const Ogre::Ray& ray, int queryMask = 0xffffffff);
	void		DoAABBSceneQuery(const Ogre::AxisAlignedBox& aabb, int queryMask = 0xffffffff);

private:
	eEditMode		m_curEditMode;
	Ogre::Entity*	m_pSelectEntity;	//��ǰѡ������
	GizmoAxis*		m_pGizmoAixs;		//������ָʾ��
	Ogre::RaySceneQuery* m_pRaySceneQuery;
	Ogre::AxisAlignedBoxSceneQuery*	m_pAABBSceneQuery;
};


#endif // ManipulatorObject_h__







