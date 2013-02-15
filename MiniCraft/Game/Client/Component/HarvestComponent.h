/********************************************************************
	created:	15:2:2013   14:17
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\AI\HarvestComponent.h
	author:		maval
	
	purpose:	�ɼ���Դ���,�߼�����ͨ�����ʹ�ø���
*********************************************************************/

#ifndef HarvestComponent_h__
#define HarvestComponent_h__

#include "Component.h"

enum eHarvestStage
{
	eHarvestStage_ToRes,		//����Դ�ƶ�
	eHarvestStage_Gather,		//���ڲɼ�
	eHarvestStage_Return,		//���ڷ���
	eHarvestStage_None			//��δ����ɼ��׶�
};

class SelectableObject;
class Resource;

class HarvestComponent : public Component
{
public:
	HarvestComponent(SelectableObject* pOwner);
	~HarvestComponent() {}

public:
	virtual void	Update(float dt);
	//���õ�ǰ�׶�
	void			SetCurStage(eHarvestStage stage) { m_curStage = stage; }
	//���òɼ�Ŀ��
	void			SetTarget(Resource* pRes) { m_pTarget = pRes; }
	

private:
	Resource*		m_pTarget;		//Ŀ����Դ
	bool			m_bCarried;		//��ǰ�Ƿ�������Դ
	eHarvestStage	m_curStage;		//��ǰ�ɼ����н׶�
	float			m_fGatherTime;	//�ɼ������˶��
	Ogre::Entity*	m_pCrystal;
};

#endif // HarvestComponent_h__