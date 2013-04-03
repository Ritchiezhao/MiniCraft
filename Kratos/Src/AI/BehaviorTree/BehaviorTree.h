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
#include "GameDefine.h"

namespace Kratos
{
	class aiBehaviorTree : public aiBehaviorTreeNode
	{
	public:
		aiBehaviorTree(eGameRace race);
		~aiBehaviorTree();

	public:
		eGameRace				GetRace() const { return m_race; }
		aiBehaviorTreeNode*		GetRootNode() const { return m_root; }
		void					AddNode(aiBehaviorTreeNode* node, aiBehaviorTreeNode* parent);
		//��������������,�õ�Ҫ���е���Ϊ
		virtual	eEvalState		Evaluate(aiBlackBoard* pInfo, STRING& retBehavior);
		//У����Ч��
		void					ValidateTree();		

	private:
		aiBehaviorTree(const aiBehaviorTree&);
		aiBehaviorTree& operator= (const aiBehaviorTree&);

		aiBehaviorTreeNode*		m_root;
		typedef HashMap<int, aiBehaviorTreeNode*> NodeMap;
		NodeMap					m_nodeMap;	//���ݽڵ��ַ���ٻ�ȡ
		eGameRace				m_race;
	};
}


#endif // BehaviorTree_h__