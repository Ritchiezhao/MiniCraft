/********************************************************************
	created:	26:3:2013   22:25
	filename	BehaviorTreeNode.h
	author:		maval

	purpose:	��Ϊ���ڵ��
*********************************************************************/

#ifndef BehaviorTreeNode_h__
#define BehaviorTreeNode_h__

#include "KratosPrerequisites.h"

class aiBlackBoard;

///����ڵ�
class aiBehaviorTreeNode
{
public:
	aiBehaviorTreeNode() {}
	virtual ~aiBehaviorTreeNode() {}

public:
	virtual	bool	Evaluate(aiBlackBoard* pInfo, STRING& retBehavior);
	void			AddChild(aiBehaviorTreeNode* node) { m_childs.push_back(node); }

protected:
	std::list<aiBehaviorTreeNode*>	m_childs;
};

///���нڵ�,�������ҽ���
class aiBTSequenceNode : public aiBehaviorTreeNode
{
public:
	aiBTSequenceNode() {}
	~aiBTSequenceNode() {}

public:
	virtual	bool	Evaluate(aiBlackBoard* pInfo, STRING& retBehavior);
};

///��Ϊ�ڵ�,��ΪҶ�ڵ�,����һ������ִ�е���Ϊ
class aiBTActionNode : public aiBehaviorTreeNode
{
public:
	aiBTActionNode();
	~aiBTActionNode() {}

public:
	virtual	bool	Evaluate(aiBlackBoard* pInfo, STRING& retBehavior);
	void			SetBehaviorName(const STRING& name) { m_behaviorName = name; }

private:
	STRING		m_behaviorName;
};

///�����ڵ�
class aiBTConditionNode : public aiBehaviorTreeNode
{
public:
	aiBTConditionNode();
	~aiBTConditionNode() {}

public:
	virtual	bool	Evaluate(aiBlackBoard* pInfo, STRING& retBehavior);
	void			SetConditions(const STRING& con) { m_conditions = con; }
	const STRING&	GetConditions() const { return m_conditions; } 

private:
	STRING		m_conditions;	//�ж������ַ���
};

#endif // BehaviorTreeNode_h__