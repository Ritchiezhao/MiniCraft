/********************************************************************
	created:	20:1:2013   22:16
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\ObjectBase.h
	author:		maval
	
	purpose:	��Ϸ�������,������Ϸʵ�����̳�
*********************************************************************/

#ifndef ObjectBase_h__
#define ObjectBase_h__

#include "GameDefine.h"
#include <OgreStringInterface.h>
#include "KratosPrerequisites.h"
#include "Component.h"

////////////////////////////////////////////////////
///�������
class Object : public Ogre::StringInterface
{
public:
	Object();
	virtual ~Object();

public:
	int					GetID() const { return m_ID; }
	void				AddComponent(eComponentType type, Component* pCo);
	Component*			GetComponent(eComponentType type);
	void				UpdateAllComponent(float dt);
	virtual eObjectType GetType() const = 0;
	virtual	void		Update(float dt) {}

private:
	int					m_ID;			//����Ψһ��ʾID

	typedef std::unordered_map<eComponentType, Component*>	ComponentContainer;
	ComponentContainer	m_components;	//�������
};


////////////////////////////////////////////////////
///����Ⱦ�������
class RenderableObject : public Object
{
	DECL_PARAM_COMMAND(MeshName)

public:
	RenderableObject();
	~RenderableObject() {}

public:
	virtual void	CreateRenderInstance();	
	///NO VIRTUAL!!
	bool			InitParamDict(const STRING& name);

public:
	void			SetMeshName(const STRING& meshname);
	const STRING&	GetMeshName() const { return m_meshname; }
	void			DestroyRenderInstance();
	bool			IsRenderableReady() const { return m_bRenderableReady; }
	void			SetPosition(const POS& pos);
	void			SetOrientation(const ORIENT& orient);
	void			SetScale(const SCALE& scale);
	const POS&		GetPosition() const;
	const ORIENT&	GetOrientation() const;
	const SCALE&	GetScale() const;
	Ogre::Entity*	GetEntity() { return m_pEntity; }
	Ogre::SceneNode* GetSceneNode() { return m_pSceneNode; }

protected:
	Ogre::Entity*		m_pEntity;
	Ogre::SceneNode*	m_pSceneNode;
	bool				m_bRenderableReady;	//��Ⱦʵ���Ƿ��Ѵ���
	STRING				m_meshname;
};



#endif // ObjectBase_h__