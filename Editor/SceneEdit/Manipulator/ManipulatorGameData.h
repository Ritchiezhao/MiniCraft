/********************************************************************
	created:	29:1:2013   20:55
	filename: 	F:\MiniCraft\Editor\SceneEdit\Manipulator\ManipulatorGameData.h
	author:		maval
	
	purpose:	��Ϸ�ͻ���������ر༭����.ģ��SC2,������Ϸ�����ļ���ͨ��XML���.
*********************************************************************/

#ifndef ManipulatorGameData_h__
#define ManipulatorGameData_h__

#include "../../MiniCraft/Game/Client/GameDataDef.h"
#include "rapidxml.hpp"

class GameDataDefManager;

class ManipulatorGameData
{
public:
	ManipulatorGameData();
	~ManipulatorGameData();

	//node:������Ĵ���Ҫһ��
	enum eBTNodeType
	{
		eBTNodeType_Sequence,
		eBTNodeType_Condition,
		eBTNodeType_Action
	};

	struct SBBParam
	{
		explicit SBBParam(const std::wstring paramName)
		:name(paramName),fgID(-1) {}

		bool operator== (const SBBParam& rhs) { return name == rhs.name; }

		std::wstring name;
		int fgID;
	};
	typedef std::vector<SBBParam> Blackboard;

	struct SBBValue 
	{
		std::wstring value;
		std::wstring type;
	};

	//һ����Ϊ��ģ�����Ϣ��ȡ,��UI��ʹ��
	//UI�㲻ֱ�ӽӴ����������
	class BTTemplate 
	{
	public:
		std::wstring	m_name;
		int				race;
		std::wstring	m_scriptName;
		std::wstring	m_scriptEntry;

		struct SBTNode
		{
			SBTNode()
			:parent(nullptr),txtProperty(L""),fgElementName(L""),flowGraphNodeID(-1),priority(0) {}

			std::wstring	type;
			std::wstring	txtProperty;
			std::wstring	fgElementName;
			int				flowGraphNodeID;
			int				priority;
			DWORD			color;
			SBTNode*		parent;
			std::vector<SBTNode*> childs;
		};
		std::list<SBTNode*>	m_nodeList;
		SBTNode*			rootNode;

		Blackboard			m_ownBB;
		Blackboard*			m_raceBB;
	};
	typedef std::vector<BTTemplate>	BTTemplates;

public:
	//�������б༭��Ҫ�õ�����ϷXML�����ļ�
	void						LoadAllXml();
	//��������XML
	void						SaveAllXml();
	//��ȡ����Ľ��������б�
	std::vector<std::wstring>	GetRaceBuildingNames(eGameRace race) const;
	//��ȡbuilding����
	SBuildingData*				GetBuildingData(const std::wstring& name);
	//��ȡ����ability�����б�
	std::vector<std::wstring>	GetAbilityNames() const;
	//��ȡability����
	const SAbilityData*			GetAbilityData(const std::wstring& name);
	//���ý���������
	void						SetBuildingAbility(const std::wstring& buildingName, int slotIndex, const std::wstring& abilName);
	//��ȡ��λ����.ע�������mesh����
	SUnitData*					GetUnitData(const std::string& meshname);

	////////////////////////////////////////////////////////////////////////
	////////////////////// Behavior Tree
	BTTemplate&					NewBTTemplate(const std::wstring& name);
	//��ȡ������Ϊ��ģ������
	std::vector<std::wstring>	GetAllBehaviorTreeTemplateNames() const;
	BTTemplate&					GetBTTemplate(const std::wstring& name);
	void						SaveAllBehaviorTreeTemplates();
	//��ȡ���п���behavior����
	std::vector<std::wstring>	GetAllBehaviorNames() const;
	//У�����Ϊ��ģ�����Ч��
	void						ValidateBehaviorTemplate(const BTTemplate& tmpl);
	BTTemplate::SBTNode*		AddBTNode(BTTemplate& tmpl, eBTNodeType type);
	void						DeleteBTNode(BTTemplate& tmpl, int id);
	//����ڰ����
	const std::string			DefineBlackboardParam(bool bOwnBB, BTTemplate& tmpl);
	void						DeleteBlackboardParam(int paramID, bool bOwnBB, BTTemplate& tmpl);
	const SBBValue				GetBlackboardParam(int paramID, BTTemplate& tmpl, bool bOwnBB);
	void						SetBlackboardParam(int paramID, const SBBValue& param, BTTemplate& tmpl, bool bOwnBB);
	void						RenameBlackboardParam(int paramID, const std::wstring& newName, BTTemplate& tmpl, bool bOwnBB);
	SBBParam*					FindBBParam(Blackboard& BB, int id);

private:
	void						_ParseAllBTTemplates();
	DWORD						_GetBTNodeColor(eBTNodeType type);
	void						_ParseBTNode(const Kratos::aiBehaviorTreeNode* pEngineNode, BTTemplate::SBTNode* pNode,
		BTTemplate::SBTNode* parent, BTTemplate& tmpl);
	void						_ParseBlackboard(Blackboard& bb, Kratos::aiBlackBoard* pEngineBB);
	void						_SaveBTTemplate(const BTTemplate& tmpl, const STRING& filepath);
	void						_SaveBTNode(rapidxml::xml_document<>* doc, BTTemplate::SBTNode* node, rapidxml::xml_node<>* xmlNode);
	void						_SaveBlackboard(rapidxml::xml_document<>* doc, Kratos::aiBlackBoard* pBB, rapidxml::xml_node<>* xmlNode);
	void						_GetBlackboard(bool bOwn, BTTemplate& tmpl, Blackboard*& pBB, Kratos::aiBlackBoard*& pEngineBB);

	GameDataDefManager*			m_dataMgr;
	BTTemplates					m_btTemplates;
	Blackboard					m_raceBlackboards[eGameRace_Count];
};


#endif // ManipulatorGameData_h__







