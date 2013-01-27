#include "stdafx.h"
#include "ManipulatorObject.h"
#include "../EditorDefine.h"
#include "ManipulatorScene.h"
#include "ManipulatorAction.h"
#include "Gizmo.h"
#include "Utility.h"
#include <OgreWireBoundingBox.h>


ManipulatorObject::ManipulatorObject()
:m_curEditMode(eEditMode_None)
,m_pSelectEntity(nullptr)
,m_pAnimEntity(nullptr)
,m_pAnimState(nullptr)
{
	ManipulatorScene::GetSingleton().AddCallback(this);
	m_pGizmoAixs = new GizmoAxis;
	m_pRaySceneQuery = ManipulatorSystem.m_pSceneMgr->createRayQuery(Ogre::Ray());
	m_pAABBSceneQuery = ManipulatorSystem.m_pSceneMgr->createAABBQuery(Ogre::AxisAlignedBox());
	m_pRaySceneQuery->setSortByDistance(true);
}

ManipulatorObject::~ManipulatorObject()
{
	ManipulatorSystem.m_pSceneMgr->destroyQuery(m_pRaySceneQuery);
	ManipulatorSystem.m_pSceneMgr->destroyQuery(m_pAABBSceneQuery);
	m_pRaySceneQuery = nullptr;
	m_pAABBSceneQuery = nullptr;
	SAFE_DELETE(m_pGizmoAixs);
	ManipulatorScene::GetSingleton().RemoveCallback(this);
}

void ManipulatorObject::OnGizmoNodeReset()
{
	m_pGizmoAixs->OnGizmoNodeReset();
}

void ManipulatorObject::OnSceneClose()
{
	m_curEditMode = eEditMode_None; 
	m_pSelectEntity = nullptr;
	m_pAnimEntity = nullptr;
	m_pAnimState = nullptr;

	for(auto iter=m_objects.begin(); iter!=m_objects.end(); ++iter)
		delete iter->second;
	m_objects.clear();
}

void ManipulatorObject::OnSceneNew()
{
	m_pGizmoAixs->Reset();
}

void ManipulatorObject::OnSceneOpen()
{
	m_pGizmoAixs->Reset();
}

Ogre::Entity* ManipulatorObject::AddEntity( const Ogre::String& meshname, const Ogre::Vector3& worldPos, 
	const Ogre::Quaternion& orient, const Ogre::Vector3& scale )
{
	static int counter = 0;

	Ogre::String entName("Entity_");
	entName += Ogre::StringConverter::toString(counter++);

	Ogre::Entity* newEntity = ManipulatorSystem.m_pSceneMgr->createEntity(entName, meshname);
	if(!newEntity)
		return nullptr;

	Ogre::SceneNode* pNode = ManipulatorSystem.m_pSceneMgr->getRootSceneNode()->createChildSceneNode(worldPos, orient);
	pNode->setScale(scale);
	pNode->attachObject(newEntity);

	//ÿ��Entity����һ����Χ�нڵ�
	Ogre::WireBoundingBox* aabb = new Ogre::WireBoundingBox;
	aabb->setMaterial("BaseWhiteNoLighting");
	aabb->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
	Ogre::SceneNode* aabbNode = pNode->createChildSceneNode(entName);
	aabbNode->attachObject(aabb);
	aabbNode->setVisible(false);

	_UpdateAABBOfEntity(newEntity);

	//���ò�ѯ����
	newEntity->setQueryFlags(eQueryMask_Entity);

	m_objects.insert(std::make_pair(newEntity, new SObjectInfo));
	
	return newEntity;
}

Ogre::Entity* ManipulatorObject::AddEntity( const Ogre::String& meshname, const Ogre::Vector2& screenPos )
{
	Ogre::Ray ray = ManipulatorSystem.m_pMainCamera->getCameraToViewportRay(screenPos.x, screenPos.y);

	Vector3 pt;
	if (ManipulatorSystem.GetTerrain().GetRayIntersectPoint(ray, pt))
		return AddEntity(meshname, pt);

	return nullptr;
}

void ManipulatorObject::SetSelection( Ogre::Entity* pEnt )
{
	ClearSelection();
	
	assert(pEnt && pEnt->getParentNode());
	ShowEntityGizmo(pEnt, true, m_curEditMode, false);
	m_pSelectEntity = pEnt;

	//�ص��¼�
	Excute([this](ManipulatorObjectEventCallback* callback){ callback->OnObjectSetSelection(m_pSelectEntity); });
}

void ManipulatorObject::ShowEntityGizmo(Ogre::Entity* pEntity, bool bShow, eEditMode mode, bool bDrift/* = false*/)
{
	assert(pEntity);
	assert(mode != eEditMode_None);

	if (mode == eEditMode_Select)
	{
		Ogre::SceneNode* aabbNode = dynamic_cast<Ogre::SceneNode*>(pEntity->getParentSceneNode()->getChild(pEntity->getName()));
		aabbNode->setVisible(bShow);
		if (bShow)
		{
			//��ʾ��Χ��
			Ogre::WireBoundingBox* pAABB = GetEntityAABBGizmo(pEntity);
			if(bDrift)		//��ʾΪ��ɫ
				pAABB->setMaterial("RedEmissive_ZCheck");
			else			//��ʾΪ��ɫ
				pAABB->setMaterial("GreenEmissive_ZCheck");
		}
	}
	else
	{
		//��ʾ������
		m_pGizmoAixs->Show(bShow, mode == eEditMode_Move || mode == eEditMode_Scale);
		if (bShow)
			m_pGizmoAixs->Attach(pEntity->getParentSceneNode());
	}
}

Ogre::MovableObject* ManipulatorObject::DoRaySceneQuery( const Ogre::Ray& ray, int queryMask /*= eQueryMask_Default*/ )
{
	m_pRaySceneQuery->setRay(ray);
	m_pRaySceneQuery->setQueryMask(queryMask);
	const Ogre::RaySceneQueryResult& result = m_pRaySceneQuery->execute();

	if(result.empty())
		return nullptr;

	return result[0].movable;
}

void ManipulatorObject::DoAABBSceneQuery( const Ogre::AxisAlignedBox& aabb, int queryMask /*= 0xffffffff*/ )
{
	m_pAABBSceneQuery->setBox(aabb);
	m_pAABBSceneQuery->setQueryMask(queryMask);
	Ogre::SceneQueryResult& queryResults = m_pAABBSceneQuery->execute();

	auto movableList = queryResults.movables;
}

void ManipulatorObject::SelectionSetPosition( const Ogre::Vector3& vecMove )
{
	assert(m_pSelectEntity);
	m_pSelectEntity->getParentSceneNode()->_setDerivedPosition(vecMove);

	//�ص��¼�
	Excute([this](ManipulatorObjectEventCallback* callback){ callback->OnObjectPropertyChanged(m_pSelectEntity); });
}

void ManipulatorObject::SelectionRotate( float radian )
{
	assert(m_pSelectEntity);

	switch (m_pGizmoAixs->GetActiveAxis())
	{
	case eAxis_X: m_pSelectEntity->getParentSceneNode()->pitch(Ogre::Radian(radian)); break;
	case eAxis_Y: m_pSelectEntity->getParentSceneNode()->yaw(Ogre::Radian(radian)); break;
	case eAxis_Z: m_pSelectEntity->getParentSceneNode()->roll(Ogre::Radian(radian)); break;
	}

	//�ص��¼�
	Excute([this](ManipulatorObjectEventCallback* callback){ callback->OnObjectPropertyChanged(m_pSelectEntity); });
}

void ManipulatorObject::SelectionScale( const Ogre::Vector3& scaleMultiplier )
{
	assert(m_pSelectEntity);
	m_pSelectEntity->getParentSceneNode()->scale(scaleMultiplier);

	//�ص��¼�
	Excute([this](ManipulatorObjectEventCallback* callback){ callback->OnObjectPropertyChanged(m_pSelectEntity); });
}

void ManipulatorObject::SelectionSetOrientation( const Ogre::Quaternion& orient )
{
	assert(m_pSelectEntity);
	m_pSelectEntity->getParentSceneNode()->_setDerivedOrientation(orient);

	//�ص��¼�
	Excute([this](ManipulatorObjectEventCallback* callback){ callback->OnObjectPropertyChanged(m_pSelectEntity); });
}

void ManipulatorObject::SelectionSetScale( const Ogre::Vector3 scale )
{
	assert(m_pSelectEntity);
	m_pSelectEntity->getParentSceneNode()->setScale(scale);

	//�ص��¼�
	Excute([this](ManipulatorObjectEventCallback* callback){ callback->OnObjectPropertyChanged(m_pSelectEntity); });
}

void ManipulatorObject::ClearSelection()
{
	if (m_pSelectEntity)
	{
		//��������gizmo
		ShowEntityGizmo(m_pSelectEntity, false, eEditMode_Select);
		ShowEntityGizmo(m_pSelectEntity, false, eEditMode_Move);
		Ogre::Entity* pSelection = m_pSelectEntity;
		m_pSelectEntity = nullptr;

		//�ص��¼�
		Excute([=,this](ManipulatorObjectEventCallback* callback){ callback->OnObjectClearSelection(pSelection); });
	}
}

void ManipulatorObject::OnFrameMove( float dt )
{
	//����ѡ������İ�Χ��
	if (m_pSelectEntity)
		_UpdateAABBOfEntity(m_pSelectEntity);

	//���¶���
	if(m_pAnimState)
		m_pAnimState->addTime(dt);
}

Ogre::WireBoundingBox* ManipulatorObject::GetEntityAABBGizmo(Ogre::Entity* pEntity)
{
	assert(pEntity);
	Ogre::SceneNode* aabbNode = dynamic_cast<Ogre::SceneNode*>(pEntity->getParentSceneNode()->getChild(pEntity->getName()));
	return dynamic_cast<Ogre::WireBoundingBox*>(aabbNode->getAttachedObject(0));
}

void ManipulatorObject::Load( rapidxml::xml_node<>* XMLNode )
{
	Ogre::SceneManager* pSceneMgr = ManipulatorSystem.m_pSceneMgr;
	size_t count = Ogre::StringConverter::parseUnsignedInt(XMLNode->first_attribute("count")->value());
	rapidxml::xml_node<>* curObjNode = XMLNode->first_node();

	for (size_t i=0; i< count; ++i)
	{
		const String strMesh = curObjNode->first_attribute("meshname")->value();
		const bool bIsNavMesh = Ogre::StringConverter::parseBool(curObjNode->first_attribute("isnavmesh")->value());
		const bool bIsBuilding = Ogre::StringConverter::parseBool(curObjNode->first_attribute("isbuilding")->value());
		const bool bIsResource = Ogre::StringConverter::parseBool(curObjNode->first_attribute("isresource")->value());
		const Ogre::Vector3 pos = Ogre::StringConverter::parseVector3(curObjNode->first_attribute("position")->value());
		const Ogre::Quaternion orient = Ogre::StringConverter::parseQuaternion(curObjNode->first_attribute("orientation")->value());
		const Ogre::Vector3 scale = Ogre::StringConverter::parseVector3(curObjNode->first_attribute("scale")->value());

		Ogre::Entity* pNewEnt = AddEntity(strMesh, pos, orient, scale);
		assert(pNewEnt);

		SetObjectNavMeshFlag(pNewEnt, bIsNavMesh);
		SetObjectIsBuilding(pNewEnt, bIsBuilding);
		SetObjectIsResource(pNewEnt, bIsResource);

		curObjNode = curObjNode->next_sibling();
	}
}

void ManipulatorObject::_UpdateAABBOfEntity( Ogre::Entity* pEntity )
{
	assert(pEntity);

	Ogre::SceneNode* aabbNode = dynamic_cast<Ogre::SceneNode*>(
		pEntity->getParentSceneNode()->getChild(pEntity->getName()));
	Ogre::WireBoundingBox* pAABB = GetEntityAABBGizmo(pEntity);
	pAABB->setupBoundingBox(pEntity->getWorldBoundingBox(true));
	//���ⱻ�ü�
	(const_cast<Ogre::AxisAlignedBox&>(pAABB->getBoundingBox())).setInfinite();
	aabbNode->_updateBounds();
}

void ManipulatorObject::SetObjectNavMeshFlag( Ogre::Entity* pEntity, bool bIsNavMesh )
{
	auto iter = m_objects.find(pEntity);
	assert(iter != m_objects.end());

	(iter->second)->m_bAddToNavmesh = bIsNavMesh;
}

bool ManipulatorObject::GetObjectNavMeshFlag( Ogre::Entity* pEntity ) const
{
	auto iter = m_objects.find(pEntity);
	assert(iter != m_objects.end());

	return (iter->second)->m_bAddToNavmesh;
}

std::vector<std::wstring> ManipulatorObject::GetAnimationNames( Ogre::Entity* pEntity ) const
{
	assert(pEntity);
	std::vector<std::wstring> vecRet;
	Ogre::Skeleton* pSkeleton = pEntity->getSkeleton();

	vecRet.push_back(L"None");

	//û�п��ö���
	if(!pSkeleton || pSkeleton->getNumAnimations()==0)
		return vecRet;

	for(size_t i=0; i<pSkeleton->getNumAnimations(); ++i)
		vecRet.push_back(Utility::EngineToUnicode(pSkeleton->getAnimation(i)->getName()));

	return vecRet;
}

void ManipulatorObject::PlayAnimation( Ogre::Entity* pEntity, int animIndex )
{
	assert(pEntity);

	//ֹ֮ͣǰ�Ķ���
	if (m_pAnimState)
	{
		m_pAnimState->setEnabled(false);
		m_pAnimEntity = nullptr;
		m_pAnimState = nullptr;
	}

	if (animIndex != -1)
	{
		const Ogre::String& animName = pEntity->getSkeleton()->getAnimation(animIndex)->getName();
		m_pAnimEntity = pEntity;
		m_pAnimState = pEntity->getAnimationState(animName);
		assert(m_pAnimState);

		m_pAnimState->setEnabled(true);
		m_pAnimState->setLoop(true);
	}
}

void ManipulatorObject::SetObjectIsBuilding( Ogre::Entity* pEntity, bool bIsBuilding )
{
	auto iter = m_objects.find(pEntity);
	assert(iter != m_objects.end());

	(iter->second)->m_bIsBuilding = bIsBuilding;
}

bool ManipulatorObject::GetObjectIsBuilding( Ogre::Entity* pEntity ) const
{
	auto iter = m_objects.find(pEntity);
	assert(iter != m_objects.end());

	return (iter->second)->m_bIsBuilding;
}

void ManipulatorObject::SetObjectIsResource( Ogre::Entity* pEntity, bool bIsResource )
{
	auto iter = m_objects.find(pEntity);
	assert(iter != m_objects.end());

	(iter->second)->m_bIsResource = bIsResource;
}

bool ManipulatorObject::GetObjectIsResource( Ogre::Entity* pEntity ) const
{
	auto iter = m_objects.find(pEntity);
	assert(iter != m_objects.end());

	return (iter->second)->m_bIsResource;
}






