#include "stdafx.h"
#include "BehaviorTreeEditorView.h"
#include "Manipulator/ManipulatorScene.h"
#include "BehaviorTreeEditorProperty.h"
#include "resource.h"
#include "BehaviorTreeEditorDlg.h"
#include "Utility.h"
#include "BehaviorTreeEditorExplorer.h"

BEGIN_MESSAGE_MAP(BehaviorTreeEditorView, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

const int OWN_BLACKBOARD_NODE_ID	=	-1;
const int GLOBAL_BLACKBOARD_NODE_ID	=	-2;

BehaviorTreeEditorView::BehaviorTreeEditorView(CXTPDialog* parent)
:m_page(nullptr)
,m_curTmpl(nullptr)
,m_ownBBNode(nullptr)
,m_globalBBNode(nullptr)
,m_pExplorer(nullptr)
{
}

BehaviorTreeEditorView::~BehaviorTreeEditorView()
{
	m_page->GetNodes()->RemoveAll();
}

BOOL BehaviorTreeEditorView::PreCreateWindow( CREATESTRUCT& cs )
{
	if(!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style |= WS_CLIPSIBLINGS;

	return TRUE;
}

//TODO: SubclassHelper not finished yet..
WNDPROC	g_proc;
CXTPFlowGraphControl* g_ctrl;
BehaviorTreeEditorProperty* g_prop;
CXTPFlowGraphNode*	g_ownBB;
CXTPFlowGraphNode*	g_globalBB;

LRESULT CALLBACK MyWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam )
{
	if (uMsg == WM_LBUTTONDOWN)
	{
		CPoint point;
		GetCursorPos(&point);
		g_ctrl->ScreenToClient(&point);

		CXTPFlowGraphNode* pNode = g_ctrl->HitTestNode(point);
		CXTPFlowGraphConnection* pConne = g_ctrl->HitTestConnection(point);
		eBTSelectionType type;
		CXTPFlowGraphElement* curElement = nullptr;

		if (pNode)
		{
			if(pNode == g_ownBB)
			{
				CXTPFlowGraphConnectionPoint* pItem = g_ctrl->HitTestConnectionArea(point);
				if(pItem)
				{
					type = eBTSelectionType_OwnBlackboard;
					curElement = pItem;
				}
				else
				{
					type = eBTSelectionType_BT;
				}
			}
			else if(pNode == g_globalBB)
			{
				CXTPFlowGraphConnectionPoint* pItem = g_ctrl->HitTestConnectionArea(point);
				if(pItem)
				{
					type = eBTSelectionType_GlobalBlackboard;
					curElement = pItem;
				}
				else
				{
					type = eBTSelectionType_BT;
				}
			}
			else
			{
				type = eBTSelectionType_TreeNode;
				curElement = pNode;
			}
		}
		else if (pConne)
		{
			type = eBTSelectionType_Connection;
			curElement = pConne;
		}
		else
		{
			type = eBTSelectionType_BT;
		}

		g_prop->GetPropPane().OnFgElementSelected(type, curElement);
	}
	return CallWindowProcW(g_proc, hWnd, uMsg, wParam, lParam);
}

int BehaviorTreeEditorView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndControl.Create(WS_VSCROLL | WS_HSCROLL | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), 
		this, IDC_BTEditor_FlowGraph);

	g_proc = (WNDPROC)SetWindowLongPtrW(m_wndControl.GetSafeHwnd(), GWLP_WNDPROC, (LONG_PTR)MyWndProc);
	g_ctrl = &m_wndControl;

	m_wndControl.SetPaintManager(new CXTPFlowGraphMetallicTheme());
	m_wndControl.SetSmoothingMode(xtpFlowGraphSmoothingModeHighQuality);
	m_wndControl.GetPages()->RemoveAll();
	m_page = m_wndControl.GetPages()->AddPage(new CXTPFlowGraphPage());
	m_wndControl.SetActivePage(m_page);
	m_wndControl.SetZoomRange(0.5, 5.0);

	return 0;
}

void BehaviorTreeEditorView::OnSize( UINT nType, int cx, int cy )
{
	CRect rcClient;
	GetClientRect(rcClient);

	HDWP hdwp = BeginDeferWindowPos(1);
	DeferWindowPos(hdwp, m_wndControl.GetSafeHwnd(), nullptr, 0, 0, rcClient.Width(), rcClient.Height(), SWP_NOZORDER);
	EndDeferWindowPos(hdwp);
}

void BehaviorTreeEditorView::SetActiveItem( const std::wstring& name )
{
	if (name.empty())
	{
		m_pProp->GetPropPane().OnFgElementSelected(eBTSelectionType_None);
		m_page->GetNodes()->RemoveAll();
	}
	else
	{
		m_curTmpl = &ManipulatorSystem.GetGameData().GetBTTemplate(name);
		m_pProp->GetPropPane().OnFgElementSelected(eBTSelectionType_BT);
		RefreshAll();
	}
}

void BehaviorTreeEditorView::RefreshAll()
{
	m_page->GetNodes()->RemoveAll();

	//�����ڵ�
	for (auto itNode=m_curTmpl->m_nodeList.begin(); itNode!=m_curTmpl->m_nodeList.end(); ++itNode)
	{
		auto& node = *itNode;
		CXTPFlowGraphNode* pNode = m_page->GetNodes()->AddNode(new CXTPFlowGraphNode());
		node->fgElementName = _OnFgElementAdded(pNode);

		pNode->SetCaption(node->type.c_str());
		pNode->SetColor(node->color);
		pNode->GetConnectionPoints()->GetAt(0)->SetCaption(node->txtProperty.c_str());

		int id = Utility::GenGUID();
		pNode->SetID(id);
		node->flowGraphNodeID = id;
	}

	//���ӽڵ�
	_ConnectFgNodes(m_curTmpl->rootNode);

	///���кڰ�
	m_ownBBNode = m_page->GetNodes()->AddNode(new CXTPFlowGraphNode());
	m_ownBBNode->SetCaption(L"OwnBlackBoard");
	m_ownBBNode->SetColor(0xc0c0c0ff);
	m_ownBBNode->SetID(OWN_BLACKBOARD_NODE_ID);
	RefreshBlackboard(true);
	
	///����ȫ�ֺڰ�
	m_globalBBNode = m_page->GetNodes()->AddNode(new CXTPFlowGraphNode());
	m_globalBBNode->SetCaption(L"RaceBlackBoard");
	m_globalBBNode->SetColor(0xc0c0c0ff);
	m_globalBBNode->SetID(GLOBAL_BLACKBOARD_NODE_ID);
	RefreshBlackboard(false);

	g_ownBB = m_ownBBNode;
	g_globalBB = m_globalBBNode;
}

void BehaviorTreeEditorView::_ConnectFgNodes( ManipulatorGameData::BTTemplate::SBTNode* node )
{
	CXTPFlowGraphNodes* nodes = m_page->GetNodes();
	//���ӵ��ӽڵ�
	for (size_t iChild=0; iChild<node->childs.size(); ++iChild)
	{
		if(!node->childs[iChild])
			continue;

		CXTPFlowGraphConnection* pConnection;
		pConnection = m_page->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
		_OnFgElementAdded(pConnection);

		CXTPFlowGraphNode* pFrom = FindFgNodeByID(node->flowGraphNodeID);
		CXTPFlowGraphNode* pTo = FindFgNodeByID(node->childs[iChild]->flowGraphNodeID);

		pConnection->SetOutputPoint(pFrom->GetConnectionPoints()->GetAt(0));
		pConnection->SetInputPoint(pTo->GetConnectionPoints()->GetAt(0));
	}

	//�����ӽڵ�
	for(size_t i=0; i<node->childs.size(); ++i)
	{
		if(node->childs[i])
			_ConnectFgNodes(node->childs[i]);
	}
}

void BehaviorTreeEditorView::Arrange()
{
	m_wndControl.Arrange();
}

void BehaviorTreeEditorView::SetPropertyDlg( BehaviorTreeEditorProperty* pProp )
{
	m_pProp = pProp;
	g_prop = m_pProp;
}

void BehaviorTreeEditorView::AddNewNode( ManipulatorGameData::eBTNodeType type )
{
	CXTPFlowGraphNode* pNode = m_page->GetNodes()->AddNode(new CXTPFlowGraphNode());
	auto node = ManipulatorSystem.GetGameData().AddBTNode(*m_curTmpl, type);
	node->fgElementName = _OnFgElementAdded(pNode);

	pNode->SetCaption(node->type.c_str());
	pNode->SetColor(node->color);

	int id = Utility::GenGUID();
	pNode->SetID(id);
	node->flowGraphNodeID = id;
}

void BehaviorTreeEditorView::RefreshTreeNode( ManipulatorGameData::BTTemplate::SBTNode* pNode )
{
	FindFgNodeByID(pNode->flowGraphNodeID)->GetConnectionPoints()->GetAt(0)->SetCaption(pNode->txtProperty.c_str());
}

void BehaviorTreeEditorView::RefreshBlackboard( bool bOwnBB )
{
	CXTPFlowGraphNode* pNode = bOwnBB ? m_ownBBNode : m_globalBBNode;
	ManipulatorGameData::Blackboard* pBB = bOwnBB ? &m_curTmpl->m_ownBB : m_curTmpl->m_raceBB;
	pNode->GetConnectionPoints()->RemoveAll();

	for (size_t i=0; i<pBB->size(); ++i)
	{
		ManipulatorGameData::SBBParam& param = pBB->at(i);
		CXTPFlowGraphConnectionPoint* pConnectionPoint;
		pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
		pConnectionPoint->SetCaption(param.name.c_str());
		pConnectionPoint->SetType(xtpFlowGraphPointOutput);

		int id = Utility::GenGUID();
		pConnectionPoint->SetID(id);
		param.fgID = id;
	}
}

void BehaviorTreeEditorView::AddBlackboardParam( bool bOwnBB )
{
	CXTPFlowGraphNode* pNode = bOwnBB ? m_ownBBNode : m_globalBBNode;
	ManipulatorGameData::Blackboard* pBB = bOwnBB ? &m_curTmpl->m_ownBB : m_curTmpl->m_raceBB;
	const std::string paramName = ManipulatorSystem.GetGameData().DefineBlackboardParam(bOwnBB, *m_curTmpl);

	CXTPFlowGraphConnectionPoint* pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint);
	pConnectionPoint->SetCaption(Utility::EngineToUnicode(paramName).c_str());
	pConnectionPoint->SetType(xtpFlowGraphPointOutput);

	int id = Utility::GenGUID();
	pConnectionPoint->SetID(id);
	pBB->at(pBB->size()-1).fgID = id;
}

ManipulatorGameData::BTTemplate::SBTNode* BehaviorTreeEditorView::FindNodeByID( int id )
{
	auto iter = std::find_if(m_curTmpl->m_nodeList.begin(), m_curTmpl->m_nodeList.end(), 
		[&](const ManipulatorGameData::BTTemplate::SBTNode* pNode)
	{
		return pNode->flowGraphNodeID == id;
	});
	assert(iter != m_curTmpl->m_nodeList.end());

	return *iter;
}

CXTPFlowGraphNode* BehaviorTreeEditorView::FindFgNodeByID( int id )
{
	CXTPFlowGraphNodes* pNodes = m_page->GetNodes();
	CXTPFlowGraphNode* pFgNode = nullptr;
	for (int i=0; i<pNodes->GetCount(); ++i)
	{
		if (pNodes->GetAt(i)->GetID() == id)
		{
			pFgNode = pNodes->GetAt(i);
			break;
		}
	}
	assert(pFgNode != nullptr);

	return pFgNode;
}

void BehaviorTreeEditorView::Sync()
{
	//���Ŀǰ����Ľṹ
	for (auto iter=m_curTmpl->m_nodeList.begin(); iter!=m_curTmpl->m_nodeList.end(); ++iter)
	{
		auto treenode = *iter;
		treenode->parent = nullptr;
		//no clear()!
		for(size_t i=0; i<treenode->childs.size(); ++i)
			treenode->childs[i] = nullptr;
	}

	//ͬ����Ϊ���Ľṹ
	CXTPFlowGraphNodes* pNodes = m_page->GetNodes();
	for (int iNode=0; iNode<pNodes->GetCount(); ++iNode)
	{
		CXTPFlowGraphNode* pNode = pNodes->GetAt(iNode);
		if(pNode == m_ownBBNode || pNode == m_globalBBNode)
			continue;
		
		CXTPFlowGraphConnectionPoint* pConnectionPoint = pNode->GetConnectionPoints()->GetAt(0);
		if(pConnectionPoint->GetInputConnectionsCount() > 1)
		{
			::MessageBoxW(0, L"Node has more than one parent!", L"Warning", MB_ICONWARNING);
			continue;
		}

		auto self = FindNodeByID(pNode->GetID());

		//parent
		if (pConnectionPoint->GetInputConnectionsCount() > 0)
		{
			CXTPFlowGraphConnection* pConnection = pConnectionPoint->GetInputConnectionAt(0);
			auto parent = FindNodeByID(pConnection->GetOutputNode()->GetID());
			self->parent = parent;
			
			if(parent->childs.size() <= (size_t)self->priority)
				parent->childs.resize(self->priority + 1);
			parent->childs[self->priority] = self;
		}
		
		//childs
		int childCnt = pConnectionPoint->GetOutputConnectionsCount();
		for (int iChild=0; iChild<childCnt; ++iChild)
		{
			CXTPFlowGraphConnection* pConnection = pConnectionPoint->GetOutputConnectionAt(iChild);
			auto child = FindNodeByID(pConnection->GetInputNode()->GetID());

			if(self->childs.size() <= (size_t)child->priority)
				self->childs.resize(child->priority + 1);
			self->childs[child->priority] = child;
			child->parent = self;
		}
	}

	//��������Ϊ���еĽڵ����
	for (int iNode=0; iNode<pNodes->GetCount(); ++iNode)
	{
		CXTPFlowGraphNode* pNode = pNodes->GetAt(iNode);
		if(pNode == m_ownBBNode || pNode == m_globalBBNode)
			continue;

		auto self = FindNodeByID(pNode->GetID());
		if(!(m_curTmpl->rootNode == self) && !_IsChildOf(m_curTmpl->rootNode, self))
			ManipulatorSystem.GetGameData().DeleteBTNode(*m_curTmpl, pNode->GetID());
	}
}

std::wstring BehaviorTreeEditorView::_OnFgElementAdded( CXTPFlowGraphElement* element )
{
	
	std::string name = "Element_";
	name += Ogre::StringConverter::toString(Utility::GenGUID());
	const std::wstring wname = Utility::EngineToUnicode(name);

	m_elements.insert(std::make_pair(wname, element));

	if(element->IsKindOf(RUNTIME_CLASS(CXTPFlowGraphNode)))
	{
		CXTPFlowGraphNode* pNode = dynamic_cast<CXTPFlowGraphNode*>(element);
		CXTPFlowGraphConnectionPoint* pConnectionPoint;
		pConnectionPoint = pNode->GetConnectionPoints()->AddConnectionPoint(new CXTPFlowGraphConnectionPoint());
		pConnectionPoint->SetCaption(L"");
		pConnectionPoint->SetType(xtpFlowGraphPointInputAndOutput);
	}
	else if (element->IsKindOf(RUNTIME_CLASS(CXTPFlowGraphConnection)))
	{
		CXTPFlowGraphConnection* pConne = dynamic_cast<CXTPFlowGraphConnection*>(element);
		pConne->SetCaption(wname.c_str());
	}
	else
	{
		assert(0);
	}

	return std::move(wname);
}

void BehaviorTreeEditorView::_OnFgElememtRemoved( const std::wstring& name )
{
	auto iter = m_elements.find(name);
	assert(iter != m_elements.end());
	m_elements.erase(iter);
}

std::wstring BehaviorTreeEditorView::GetFgElementName(eBTSelectionType type, CXTPFlowGraphElement* element)
{
	std::wstring name;
	if(type == eBTSelectionType_TreeNode)
	{
		CXTPFlowGraphNode* pFgNode = dynamic_cast<CXTPFlowGraphNode*>(element);
		auto node = FindNodeByID(pFgNode->GetID());
		name = node->fgElementName;
	}
	else if (type == eBTSelectionType_Connection)
	{
		CXTPFlowGraphConnection* pConne = dynamic_cast<CXTPFlowGraphConnection*>(element);
		name = pConne->GetCaption();
	}
	else
	{
		assert(0);
	}

	return std::move(name);
}

void BehaviorTreeEditorView::DeleteCurElement()
{
	assert(m_curTmpl);
	ManipulatorGameData& manGameData = ManipulatorSystem.GetGameData();
	eBTSelectionType type = m_pProp->GetPropPane().GetCurSelType();
	CXTPFlowGraphElement* curFgElement = m_pProp->GetPropPane().GetCurFgElement();

	switch (type)
	{
	case eBTSelectionType_TreeNode:
		{
			CXTPFlowGraphNode* pFgNode = dynamic_cast<CXTPFlowGraphNode*>(curFgElement);

			if(FindNodeByID(pFgNode->GetID()) == m_curTmpl->rootNode)
			{
				if(IDCANCEL == ::MessageBoxW(0, L"Really remove root node?", L"Warning", MB_ICONWARNING | MB_OKCANCEL))
					return;
			}

			//�ڵ㱻�Ƴ�,��ô������������Ҳ�ᱻ�Ƴ�
			CXTPFlowGraphConnectionPoint* pConnePt = pFgNode->GetConnectionPoints()->GetAt(0);
			for (int i=0; i<pConnePt->GetInputConnectionsCount(); ++i)
			{
				CXTPFlowGraphConnection* pConne = pConnePt->GetInputConnectionAt(i);
				_OnFgConnectionRemoved(pConne);
			}
			for (int i=0; i<pConnePt->GetOutputConnectionsCount(); ++i)
			{
				CXTPFlowGraphConnection* pConne = pConnePt->GetOutputConnectionAt(i);
				_OnFgConnectionRemoved(pConne);
			}

			const std::wstring name = GetFgElementName(type, curFgElement);
			_OnFgElememtRemoved(name);
			manGameData.DeleteBTNode(*m_curTmpl, pFgNode->GetID());
			pFgNode->Remove();
		}
		break;

	case eBTSelectionType_Connection:
		{
			CXTPFlowGraphConnection* pConne = dynamic_cast<CXTPFlowGraphConnection*>(curFgElement);
			_OnFgConnectionRemoved(pConne);

			const std::wstring name = GetFgElementName(type, curFgElement);
			_OnFgElememtRemoved(name);
			pConne->Remove();
		}
		break;

	case eBTSelectionType_OwnBlackboard:
		{
			CXTPFlowGraphConnectionPoint* pConnePt = dynamic_cast<CXTPFlowGraphConnectionPoint*>(curFgElement);
			manGameData.DeleteBlackboardParam(pConnePt->GetID(), true, *m_curTmpl);

			pConnePt->Remove();
		}
		break;

	case eBTSelectionType_GlobalBlackboard:
		{
			CXTPFlowGraphConnectionPoint* pConnePt = dynamic_cast<CXTPFlowGraphConnectionPoint*>(curFgElement);
			manGameData.DeleteBlackboardParam(pConnePt->GetID(), false, *m_curTmpl);

			pConnePt->Remove();
		}
		break;

	default: assert(0);
	}

	m_pProp->GetPropPane().OnFgElementSelected(eBTSelectionType_BT);
}

void BehaviorTreeEditorView::_OnFgConnectionRemoved( CXTPFlowGraphConnection* pConne )
{
	auto inputNode = FindNodeByID(pConne->GetInputNode()->GetID());
	auto outputNode = FindNodeByID(pConne->GetOutputNode()->GetID());

	inputNode->parent = nullptr;
	outputNode->childs[inputNode->priority] = nullptr;
}

bool BehaviorTreeEditorView::_IsChildOf( ManipulatorGameData::BTTemplate::SBTNode* parent, ManipulatorGameData::BTTemplate::SBTNode* self )
{
	while(self->parent)
	{
		if(self->parent == parent)
			return true;
		self = self->parent;
	}
	return false;
}

void BehaviorTreeEditorView::NewBT( const std::wstring& name )
{
	SetActiveItem(L"");
	m_curTmpl = &ManipulatorSystem.GetGameData().NewBTTemplate(name);
	assert(m_curTmpl);
	RefreshAll();
	m_pExplorer->Refresh();
}











