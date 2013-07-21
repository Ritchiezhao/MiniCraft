#include "stdafx.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "ObjectBase.h"
#include "OgreManager.h"

ObjectManager::ObjectManager()
{
	//ע�����ж��󹤳�
 	m_factories.insert(std::make_pair(eObjectType_Unit, new UnitFactory));
 	m_factories.insert(std::make_pair(eObjectType_Building, new BuildingFactory));
	m_factories.insert(std::make_pair(eObjectType_Resource, new ResourceFactory));

	if(RenderManager.m_bSupportVTF)
	{
		int numInstPerBatch = 500;
		m_unitInstMgr = RenderManager.m_pSceneMgr->createInstanceManager("UnitInstanceManager", "Marine_0.mesh",
			"General", Ogre::InstanceManager::HWInstancingVTF, numInstPerBatch, Ogre::IM_USEALL | Ogre::IM_VTFBONEMATRIXLOOKUP);
		//Brute Force..��ÿ��instance���������,������������ֹͣ�Ϳ��Ը��Զ���.
		//���ǻ�����VTF�����С,����֡��.
		m_unitInstMgr->setMaxLookupTableInstances(numInstPerBatch);
	}
}

ObjectManager::~ObjectManager()
{
	if(m_unitInstMgr)
	{
		RenderManager.m_pSceneMgr->destroyInstanceManager(m_unitInstMgr);
		m_unitInstMgr = nullptr;
	}

	for(auto iter=m_factories.begin(); iter!=m_factories.end(); ++iter)
		delete iter->second;
	m_factories.clear();

	DestroyAll();
}

Object* ObjectManager::CreateObject( eObjectType type )
{
	auto iter = m_factories.find(type);
	assert(iter != m_factories.end());

	Object* pNewInst = (iter->second)->CreateInstance();
	assert(pNewInst);

	m_objects.insert(std::make_pair(pNewInst->GetID(), pNewInst));

	return pNewInst;
}

void ObjectManager::DestroyAll()
{
	for(auto iter=m_objects.begin(); iter!=m_objects.end(); ++iter)
	{
		auto iterFactory = m_factories.find((iter->second)->GetType());
		ObjectFactory* pFactory = iterFactory->second;
		pFactory->DestroyInstance(iter->second);
	}
	m_objects.clear();
}

void ObjectManager::UpdateAll( float dt )
{
	for(auto iter=m_objects.begin(); iter!=m_objects.end(); ++iter)
	{
		Object* pObj = (iter->second);
		pObj->UpdateAllComponent(dt);
		pObj->Update(dt);
	}

	for (size_t i=0; i<m_lstToDestroy.size(); ++i)
	{
		Object* obj = m_lstToDestroy[i];
		m_objects.erase(obj->GetID());

		auto iterFactory = m_factories.find(obj->GetType());
		ObjectFactory* pFactory = iterFactory->second;
		pFactory->DestroyInstance(obj);
	}
	m_lstToDestroy.clear();
}

void ObjectManager::DestroyObject( Object* pObject )
{
	//��ֱ������,������ÿ֡update������
	m_lstToDestroy.push_back(pObject);
}
