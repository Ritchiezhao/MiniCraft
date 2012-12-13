
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "SceneEdit.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CXTPFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CXTPFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, lpCreateStruct->cx, lpCreateStruct->cy), this, AFX_IDW_PANE_FIRST, NULL))
		return -1;

	SetActiveView(&m_wndView);

	// Create Status bar.
	// Important: All control bars including the Status Bar
	// must be created before CommandBars....
// 	if (!m_wndStatusBar.Create(this) ||
// 		!m_wndStatusBar.SetIndicators(indicators,
// 		sizeof(indicators)/sizeof(UINT)))
// 	{
// 		TRACE0("Failed to create status bar\n");
// 		return -1;      // fail to create
// 	}

	if(!_OnCreateRibbon())
		return -1;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	cs.cx = 800;
	cs.cy = 600;
	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// ������ǰ�Ƶ���ͼ����
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ����ͼ��һ�γ��Ը�����
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// ����ִ��Ĭ�ϴ���
	return CXTPFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnClose()
{
	CSceneEditApp* app = (CSceneEditApp*)AfxGetApp();
	app->m_app.Shutdown();

	CXTPFrameWnd::OnClose();
}

bool CMainFrame::_OnCreateRibbon()
{
	// Initialize the command bars
	if (!InitCommandBars())
		return false;

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
		return false;

	CXTPPaintManager::SetTheme(xtpThemeRibbon);

	CMenu menu;
	menu.Attach(::GetMenu(m_hWnd));
	SetMenu(NULL);

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)pCommandBars->Add(_T("The Ribbon"), xtpBarTop, RUNTIME_CLASS(CXTPRibbonBar));
	if (!pRibbonBar)
	{
		return false;
	}
	pRibbonBar->EnableDocking(0);
	//pRibbonBar->GetTabPaintManager()->m_bSelectOnButtonDown = FALSE;

	CXTPControlPopup* pControlFile = (CXTPControlPopup*)pRibbonBar->AddSystemButton();
	pControlFile->SetIconId(IDB_GEAR);

	UINT uCommand = {IDB_GEAR};
	pCommandBars->GetImageManager()->SetIcons(IDB_GEAR, &uCommand, 1, CSize(0, 0), xtpImageNormal);

	CXTPRibbonTab* pTab1 = pRibbonBar->AddTab(L"Tab1");
	CXTPRibbonTab* pTab2 = pRibbonBar->AddTab(L"Tab2");

	return true;
}
