/********************************************************************
	created:	20:12:2012   0:39
	filename: 	F:\MiniCraft\Editor\SceneEdit\Manipulator\ManipulatorObject.h
	author:		maval
	
	purpose:	�ɰڷ����崴��,����,�ٿ�.
*********************************************************************/

#ifndef ManipulatorObject_h__
#define ManipulatorObject_h__



class ManipulatorObject
{
public:
	ManipulatorObject() {}
	~ManipulatorObject() {}

public:
	//����Entity
	bool	AddEntity(const Ogre::String& meshname, const Ogre::Vector3& worldPos);
	bool	AddEntity(const Ogre::String& meshname, const Ogre::Vector2& screenPos);

	void	OnGizmoNodeReset() {}
};


#endif // ManipulatorObject_h__







