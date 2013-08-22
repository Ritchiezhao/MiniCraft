/********************************************************************
	created:	20:1:2013   22:20
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\ObjectManager.h
	author:		maval
	
	purpose:	���������,����������Ϸ����
*********************************************************************/

#ifndef ObjectManager_h__
#define ObjectManager_h__

#include "Singleton.h"
#include "GameDefine.h"
#include "KratosPrerequisites.h"

class Object;
class Faction;
class ObjectFactory;

typedef std::unordered_map<eObjectType, ObjectFactory*> FactoryContainer;
typedef std::unordered_map<int, Object*> ObjectContainer;	//ȫ��ID����

class ObjectManager : public CSingleton<ObjectManager>
{
	ObjectManager();
	~ObjectManager();
	DECLEAR_SINGLETON(ObjectManager);

public:
	Object*		CreateObject(eObjectType type);
	void		DestroyObject(Object* pObject);
	void		DestroyAll();
	void		UpdateAll(float dt);
	Object*		GetObject(int ID) { assert(m_objects[ID]); return m_objects[ID]; }
	Ogre::InstanceManager*	GetInstanceManager()	{ return m_unitInstMgr; }

private:
	FactoryContainer	m_factories;
	ObjectContainer		m_objects;
	std::vector<Object*>m_lstToDestroy;

	Ogre::InstanceManager*	m_unitInstMgr;	//unit instancing
};

#endif // ObjectManager_h__