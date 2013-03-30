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
	aiBehaviorTree();
	~aiBehaviorTree();

public:
	aiBehaviorTreeNode*		GetRootNode() const { return m_root; }
	void					AddNode(aiBehaviorTreeNode* node, aiBehaviorTreeNode* parent);
	//��������������,�õ�Ҫ���е���Ϊ
	virtual	eEvalState		Evaluate(aiBlackBoard* pInfo, STRING& retBehavior);
	//У����Ч��
	void					ValidateTree();		

private:
	aiBehaviorTreeNode*		m_root;
	typedef HashMap<int, aiBehaviorTreeNode*> NodeMap;
	NodeMap					m_nodeMap;	//���ݽڵ��ַ���ٻ�ȡ
};

#endif // BehaviorTree_h__