/********************************************************************
	created:	26:3:2013   22:25
	filename	BehaviorTreeNode.h
	author:		maval

	purpose:	��Ϊ���ڵ��
*********************************************************************/

#ifndef BehaviorTreeNode_h__
#define BehaviorTreeNode_h__

#include "KratosPrerequisites.h"

namespace Kratos
{
	class aiBlackBoard;
	class aiBehaviorConditon;

	enum eEvalState
	{
		eEvalState_Success,
		eEvalState_Failure,
		eEvalState_Running
	};

	enum eNodeType
	{
		eNodeType_Sequence,
		eNodeType_Condition,
		eNodeType_Action
	};

	///����ڵ�
	class aiBehaviorTreeNode
	{
	public:
		aiBehaviorTreeNode() {}
		virtual ~aiBehaviorTreeNode() {}

		typedef std::list<aiBehaviorTreeNode*> ChildNodes;

		static const STRING	GetNodeTypeToStr(eNodeType type);
		static eNodeType	GetNodeTypeFromStr(const STRING& type);

	public:
		virtual	eNodeType	GetType() const = 0;
		virtual	eEvalState	Evaluate(aiBlackBoard* pInfo, STRING& retBehavior) = 0;
		virtual bool		Validate();
		void				AddChild(aiBehaviorTreeNode* node) { m_childs.push_back(node); }
		const ChildNodes&	GetChilds() const { return m_childs; }	

	protected:
		ChildNodes	m_childs;
	};

	///���нڵ�,�������ҽ���
	class aiBTSequenceNode : public aiBehaviorTreeNode
	{
	public:
		aiBTSequenceNode() {}
		~aiBTSequenceNode() {}

	public:
		virtual	eNodeType	GetType() const { return eNodeType_Sequence; }
		virtual bool		Validate();
		virtual	eEvalState	Evaluate(aiBlackBoard* pInfo, STRING& retBehavior);
	};

	///��Ϊ�ڵ�,��ΪҶ�ڵ�,����һ������ִ�е���Ϊ
	class aiBTActionNode : public aiBehaviorTreeNode
	{
	public:
		aiBTActionNode();
		~aiBTActionNode() {}

	public:
		virtual	eNodeType	GetType() const { return eNodeType_Action; }
		virtual	eEvalState	Evaluate(aiBlackBoard* pInfo, STRING& retBehavior);
		virtual bool		Validate();
		void				SetBehaviorName(const STRING& name) { m_behaviorName = name; }
		const STRING&		GetBehaviorName() const	{ return m_behaviorName; }

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
		virtual	eNodeType	GetType() const { return eNodeType_Condition; }
		virtual	eEvalState	Evaluate(aiBlackBoard* pInfo, STRING& retBehavior);
		virtual bool		Validate();
		void				SetConditions(const STRING& con, aiBlackBoard* pTmplBB);
		const STRING&		GetConditions() const { return m_conditions; } 

	private:
		STRING				m_conditions;	//�ж������ַ���
		aiBehaviorConditon* m_pHandler;
	};
}


#endif // BehaviorTreeNode_h__