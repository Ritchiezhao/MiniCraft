
// View.cpp : CEditorView ���ʵ��
//

#include "stdafx.h"
#include "SceneEdit.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditorView

CEditorView::CEditorView()
{
}

CEditorView::~CEditorView()
{
}

IMPLEMENT_DYNCREATE(CEditorView, CView)

BEGIN_MESSAGE_MAP(CEditorView, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CEditorView ��Ϣ�������

BOOL CEditorView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CEditorView::OnPaint() 
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	
	// TODO: �ڴ˴������Ϣ����������
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}

void CEditorView::OnSize( UINT nType, int cx, int cy )
{
	CView::OnSize(nType, cx, cy);
	((CSceneEditApp*)AfxGetApp())->m_app.OnViewportResized();
}

