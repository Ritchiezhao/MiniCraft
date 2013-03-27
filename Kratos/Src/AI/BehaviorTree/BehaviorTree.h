/********************************************************************
	created:	26:3:2013   22:23
	filename	BehaviorTree.h
	author:		maval

	purpose:	��Ϊѡ������,��������֮������,�γ�ɭ��
				���������м����,���GameBrains�Ѳ�֪����,HavokҪ��,����
*********************************************************************/

#ifndef BehaviorTree_h__
#define BehaviorTree_h__

#include "KratosPrerequisites.h"
#include "BehaviorTreeNode.h"


class aiBehaviorTree : public aiBehaviorTreeNode
{
public:
	aiBehaviorTree(const STRING& name);
	~aiBehaviorTree();

public:
	const STRING&	GetName() const { return m_name; }
	//��������������,�õ�Ҫ���е���Ϊ
	virtual	bool	Evaluate(aiBlackBoard* pInfo, STRING& retBehavior);

private:
	STRING					m_name;		//����Ϊ��������
	aiBehaviorTreeNode*		m_root;
};

#endif // BehaviorTree_h__