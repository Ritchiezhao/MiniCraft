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

typedef std::list<Ogre::Entity*> ObjectContainer;
typedef std::unordered_map<Ogre::Entity*, bool> ObjectNavMeshFlagMap;

class ManipulatorObject : public ManipulatorSceneEventCallback, public ManipulatorCallbackManager<ManipulatorObjectEventCallback>
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
	void		Load(rapidxml::xml_node<>* XMLNode);
	void		OnFrameMove(float dt);
	eEditMode	GetCurEditMode() const { return m_curEditMode; }
	void		SetCurEditMode(eEditMode mode) { m_curEditMode = mode; }
	const ObjectContainer&	GetAllObjects() const { return m_objects; }

	//����Entity
	Ogre::Entity* AddEntity(const Ogre::String& meshname, const Ogre::Vector3& worldPos, 
		const Ogre::Quaternion& orient = Ogre::Quaternion::IDENTITY, const Ogre::Vector3& scale = Ogre::Vector3(1,1,1));
	Ogre::Entity* AddEntity(const Ogre::String& meshname, const Ogre::Vector2& screenPos);

	///����ѡ��
	void		SetSelection(Ogre::Entity* pEnt);
	Ogre::Entity*	GetSelection() const { return m_pSelectEntity; }
	void		ClearSelection();
	void		SelectionSetPosition(const Ogre::Vector3& newPos);
	void		SelectionSetOrientation(const Ogre::Quaternion& orient);
	void		SelectionSetScale(const Ogre::Vector3 scale);
	void		SelectionRotate(float radian);
	void		SelectionScale(const Ogre::Vector3& scaleMultiplier);

	//ȡ��Entity�İ�Χ��Gizmo.��Χ����ʾ�������Լ�����,��ʹ��OGREĬ�ϵ�showBoundingBox
	Ogre::WireBoundingBox*	GetEntityAABBGizmo(Ogre::Entity* pEntity);
	//���ݲ���ģʽ,��ʾ������Ӧ��Gizmo
	void		ShowEntityGizmo(Ogre::Entity* pEntity, bool bShow, eEditMode mode, bool bDrift = false);
	GizmoAxis*	GetGizmoAxis() const { return m_pGizmoAixs; }
	void		OnGizmoNodeReset();
	void		SetObjectNavMeshFlag(Ogre::Entity* pEntity, bool bIsNavMesh);
	bool		GetObjectNavMeshFlag(Ogre::Entity* pEntity) const;

	//���߲�ѯ
	Ogre::MovableObject* DoRaySceneQuery(const Ogre::Ray& ray, int queryMask = 0xffffffff);
	void		DoAABBSceneQuery(const Ogre::AxisAlignedBox& aabb, int queryMask = 0xffffffff);

private:
	void		_UpdateAABBOfEntity(Ogre::Entity* pEntity);

private:
	ObjectContainer	m_objects;			//�����е����аڷ�����
	ObjectNavMeshFlagMap m_navMeshFlag;	//�������Ƿ����NavMesh����
	eEditMode		m_curEditMode;
	Ogre::Entity*	m_pSelectEntity;	//��ǰѡ������
	GizmoAxis*		m_pGizmoAixs;		//������ָʾ��
	Ogre::RaySceneQuery* m_pRaySceneQuery;
	Ogre::AxisAlignedBoxSceneQuery*	m_pAABBSceneQuery;
};


#endif // ManipulatorObject_h__







