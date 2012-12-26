/********************************************************************
	created:	22:12:2012   12:01
	filename: 	F:\MiniCraft\Editor\SceneEdit\Gizmo.h
	author:		maval
	
	purpose:	�༭���õĸ���ָʾ��
*********************************************************************/

#ifndef Gizmo_h__
#define Gizmo_h__


//
//����
//
class GizmoRectangle : public Ogre::SimpleRenderable
{
public:
	GizmoRectangle() {}
	virtual ~GizmoRectangle();

public:
	virtual Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const { (void)cam; return 0; }
	virtual Ogre::Real getBoundingRadius(void) const { return 0; }

public:
	void	InitRenderable(float w, float h);
	void	DestroyRenderable();
	void	UpdatePosition(const Ogre::Vector3& pos, float w, float h);

protected:
	//���ص�λ����.��Ϊ��������ֱ�Ӹ�����������
	virtual void getWorldTransforms( Ogre::Matrix4* xform ) const;

private:
	//��ķֲ��ܶ�,��1�����絥λ��Ӧ��ĸ���
	static const int POINT_DENSITY = 5;
};

//
//Բ��
//
class GizmoCircle : public Ogre::SimpleRenderable
{
public:
	GizmoCircle() {}
	virtual ~GizmoCircle();

public:
	virtual Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const { (void)cam; return 0; }
	virtual Ogre::Real getBoundingRadius(void) const { return 0; }

public:
	void	InitRenderable();
	void	DestroyRenderable() {}
};


#endif // Gizmo_h__







