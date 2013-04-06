/********************************************************************
	created:	15:2:2013   14:17
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\AI\HarvestComponent.h
	author:		maval
	
	purpose:	�ɼ���Դ���,�߼�����ͨ�����ʹ�ø���
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
		eHarvestStage_ToRes,		//����Դ�ƶ�
		eHarvestStage_NearRes,		//�ѵ�����Դ�ɼ���
		eHarvestStage_Gather,		//���ڲɼ�
		eHarvestStage_Return,		//���ڷ���
		eHarvestStage_NearBase,		//�ѵ��ﷵ����Դ��
		eHarvestStage_None			//��δ����ɼ��׶�
	};

public:
	virtual void	Update(float dt);
	//���õ�ǰ�׶�
	void			SetCurStage(eHarvestStage stage) { m_curStage = stage; }
	eHarvestStage	GetCurStage() const	{ return m_curStage; }

	//���òɼ�Ŀ��
	void			SetTarget(Resource* pRes) { m_pTarget = pRes; }
	void			SetGatherTime(float fTime) { m_fGatherTime = fTime; }
	float			GetGatherTime() const	{ return m_fGatherTime; }
	void			SetResVisible(bool bVisible); 

private:
	Resource*		m_pTarget;		//Ŀ����Դ
	bool			m_bCarried;		//��ǰ�Ƿ�������Դ
	eHarvestStage	m_curStage;		//��ǰ�ɼ����н׶�
	float			m_fGatherTime;	//�ɼ������˶��
	Ogre::Entity*	m_pCrystal;
};

#endif // HarvestComponent_h__