/********************************************************************
	created:	20:1:2013   22:16
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\ObjectBase.h
	author:		maval
	
	purpose:	��Ϸ�������,������Ϸʵ�����̳�
*********************************************************************/

#ifndef ObjectBase_h__
#define ObjectBase_h__

#include "GameDefine.h"

////////////////////////////////////////////////////
///�������
class Object
{
public:
	Object();
	virtual ~Object() {}

public:
	int					GetID() const { return m_ID; }
	virtual eObjectType GetType() const = 0;
	virtual const STRING& GetNamePrefix() const = 0;
	virtual	void		Update(float dt) = 0;

private:
	int	m_ID;	//����Ψһ��ʾID
};


////////////////////////////////////////////////////
///����Ⱦ�������
class RenderableObject : public Object
{
public:
	RenderableObject();
	~RenderableObject() {}

public:
	virtual	void	CreateRenderInstance(const STRING& meshname);
	virtual void	DestroyRenderInstance();
	virtual void	SetPosition(const POS& pos);
	virtual void	SetOrientation(const ORIENT& orient);
	virtual void	SetScale(const SCALE& scale);

public:
	bool			IsRenderableReady() const { return m_bRenderableReady; }

	const POS&		GetPosition() const;
	const ORIENT&	GetOrientation() const;
	const SCALE&	GetScale() const;

protected:
	Ogre::Entity*		m_pEntity;
	Ogre::SceneNode*	m_pSceneNode;
	bool				m_bRenderableReady;	//��Ⱦʵ���Ƿ��Ѵ���
};



#endif // ObjectBase_h__