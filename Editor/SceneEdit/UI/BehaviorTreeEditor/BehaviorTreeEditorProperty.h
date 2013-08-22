/********************************************************************
	created:	31:3:2013   21:52
	filename	BehaviorTreeEditorProperty.h
	author:		maval

	purpose:	��Ϊ���༭��ģ��
*********************************************************************/

#ifndef BehaviorTreeEditorProperty_h__
#define BehaviorTreeEditorProperty_h__

#include "..\PropertiesPane.h"
#include "Manipulator/ManipulatorGameData.h"
#include "BehaviorTreeEditorView.h"

class PropertyPaneBehaviorTree : public CPropertiesPane
{
public:
	PropertyPaneBehaviorTree();
	~PropertyPaneBehaviorTree() {}

	enum ePropertyID
	{
		////property range [propStart, propEnd)
		propStart = 0,
		////////These are Readonly items
		propBTName = propStart,						//��Ϊ������
		propFgElementName,							//Flow graphԪ������
		propConnectionInput,						//���ӵ�����ڵ�
		propConnectionOutput,						//���ӵ�����ڵ�
		////////These are Mutable items
		propMutableItemStart,
		propBTRace = propMutableItemStart,			//��Ϊ������
		propBTScriptName,							//��Ϊ���ű��ļ���
		propBTScriptEntry,							//��Ϊ���ű���ں�����
		propConditon,								//�����ڵ���ʽ
		propAction,									//��Ϊ��
		propPriority,								//�ڵ����
		propBBParamName,							//�ڰ��������
		propBBParamValue,							//�ڰ����ֵ
		propBBParamType,							//�ڰ��������
		propMutableItemEnd,
		propEnd = propMutableItemEnd
	};

	enum eCategory
	{
		eCategory_BehaviorTree,
		eCategory_Name,
		eCategory_Node,
		eCategory_SequenceNode,
		eCategory_ConditionNode,
		eCategory_ActionNode,
		eCategory_Blackboard,
		eCategory_Connection
	};

public:
	void			SetView(BehaviorTreeEditorView* pView) { m_pView = pView; }
	void			OnFgElementSelected(eBTSelectionType nodeType, CXTPFlowGraphElement* element = nullptr);
	eBTSelectionType	GetCurSelType() const { return m_curNodeType; }
	CXTPFlowGraphElement*
					GetCurFgElement()	{ return m_curFgElement; }

protected:
	virtual	bool	_OnCreate();
	virtual	void	_SetProperty(int nID);
	virtual	void	_UpdateProperty(int nID);
	virtual int		_GetIDStart()		{ return propStart; }
	virtual int		_GetIDEnd()			{ return propEnd; }
	virtual int		_GetIDMutableStart() { return propMutableItemStart; }
	virtual int		_GetIDMutableEnd()	{ return propMutableItemEnd; }

private:
	ManipulatorGameData::Blackboard*	_GetCurBB();

private:
	BehaviorTreeEditorView*						m_pView;
	CXTPFlowGraphElement*						m_curFgElement;
	eBTSelectionType								m_curNodeType;
};

class BehaviorTreeEditorProperty : public CDialog	
{
public:
	BehaviorTreeEditorProperty(CXTPDialog* parent);
	~BehaviorTreeEditorProperty() {}

public:
	void			SetView(BehaviorTreeEditorView* pView);
	PropertyPaneBehaviorTree& GetPropPane()	{ return m_propertyBT; }

protected:
	virtual BOOL	OnInitDialog();

private:
	DECLARE_MESSAGE_MAP()
	afx_msg	void	OnSize(UINT nType, int cx, int cy);

private:
	PropertyPaneBehaviorTree	m_propertyBT;
};


#endif // BehaviorTreeEditorProperty_h__














