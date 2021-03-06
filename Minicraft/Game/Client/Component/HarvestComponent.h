/********************************************************************
	created:	15:2:2013   14:17
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\AI\HarvestComponent.h
	author:		maval
	
	purpose:	采集资源组件,逻辑对象通过组合使用该类
*********************************************************************/

#ifndef HarvestComponent_h__
#define HarvestComponent_h__

#include "Component.h"

class SelectableObject;
class Resource;
class Unit;

class HarvestComponent : public Component
{
public:
	HarvestComponent(SelectableObject* pOwner);
	~HarvestComponent() {}

	enum eHarvestStage
	{
		eHarvestStage_ToRes,		//向资源移动
		eHarvestStage_NearRes,		//已到达资源采集点
		eHarvestStage_Gather,		//正在采集
		eHarvestStage_Return,		//正在返还
		eHarvestStage_NearBase,		//已到达返还资源点
		eHarvestStage_None			//还未进入采集阶段
	};

public:
	virtual void	Update(float dt);
	//设置当前阶段
	void			SetCurStage(eHarvestStage stage) { m_curStage = stage; }
	eHarvestStage	GetCurStage() const	{ return m_curStage; }

	//设置采集目标
	void			SetTarget(Resource* pRes) { m_pTarget = pRes; }
	Resource*		GetTarget()	{ return m_pTarget; }
	void			SetGatherTime(float fTime) { m_fGatherTime = fTime; }
	float			GetGatherTime() const	{ return m_fGatherTime; }
	void			SetResVisible(bool bVisible); 

private:
	Resource*		m_pTarget;		//目标资源
	bool			m_bCarried;		//当前是否载有资源
	eHarvestStage	m_curStage;		//当前采集进行阶段
	float			m_fGatherTime;	//采集进行了多久
	Ogre::Entity*	m_pCrystal;
};

#endif // HarvestComponent_h__