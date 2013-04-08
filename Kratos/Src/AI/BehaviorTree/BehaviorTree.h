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
		virtual	eNodeType		GetType() const { assert(0); return (eNodeType)-1; }
		//��������������,�õ�Ҫ���е���Ϊ
		virtual	eEvalState		Evaluate(aiBlackBoard* pInfo, STRING& retBehavior);
		//У����Ч��
		bool					ValidateTree();
		void					SetRace(eGameRace race) { m_race = race; }
		eGameRace				GetRace() const { return m_race; }
		aiBehaviorTreeNode*		GetRootNode() const { return m_root; }

	private:
		aiBehaviorTree(const aiBehaviorTree&);
		aiBehaviorTree& operator= (const aiBehaviorTree&);

		aiBehaviorTreeNode*		m_root;
		eGameRace				m_race;
	};
}


#endif // BehaviorTree_h__