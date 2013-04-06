/********************************************************************
	created:	27:3:2013   22:24
	filename	BehaviorComponent.h
	author:		maval

	purpose:	��Ϊ���,������Ϊ��������NPC
*********************************************************************/

#ifndef BehaviorComponent_h__
#define BehaviorComponent_h__

#include "Component.h"
#include "KratosPrerequisites.h"

class FactionAI;

class BehaviorComponent : public Component
{
public:
	BehaviorComponent(SelectableObject* pOwner);
	~BehaviorComponent();

public:
	virtual void			Update(float dt);
	//���øõ�λҪӦ�õ���Ϊ��ģ��
	void					SetTempalte(const STRING& name);
	Kratos::aiBlackBoard*	GetBlackboard() { return m_pOwnBB; }

private:
	Kratos::aiBehaviorTreeTemplate*	m_pTemplate;
	Kratos::aiBlackBoard*			m_pOwnBB;		//�õ�λ��������Ϊ���ڰ�
	Kratos::aiBehavior*				m_pCurBehavior;
};

#endif // BehaviorComponent_h__