/********************************************************************
	created:	27:3:2013   23:05
	filename	BehaviorTreeTemplate.h
	author:		maval

	purpose:	��Ϊ��ģ��,�ɶ�Ӧһ����Ϊ��xml.
*********************************************************************/

#ifndef BehaviorTreeTemplate_h__
#define BehaviorTreeTemplate_h__

#include "KratosPrerequisites.h"
#include <rapidxml.hpp>

class aiBehaviorTree;
class aiBlackBoard;
class aiBehaviorTreeNode;

class aiBehaviorTreeTemplate
{
public:
	aiBehaviorTreeTemplate();
	~aiBehaviorTreeTemplate();

public:
	const STRING	Load(const STRING& filename);
	void			Save() {}
	aiBehaviorTree*	GetBT() { return m_pBT; }
	void			CloneBlackBoard(aiBlackBoard& toClone);

private:
	aiBehaviorTreeTemplate(const aiBehaviorTreeTemplate&);
	aiBehaviorTreeTemplate& operator= (const aiBehaviorTreeTemplate&);

	void			_LoadTreeNode(rapidxml::xml_node<>* node, aiBehaviorTreeNode* parent);

	aiBehaviorTree*		m_pBT;
	aiBlackBoard*		m_pBB;
};

#endif // BehaviorTreeTemplate_h__