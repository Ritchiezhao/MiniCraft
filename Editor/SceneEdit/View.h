
// View.h : CEditorView ��Ľӿ�
//


#pragma once


// CEditorView ����

class CEditorView : public CView
{
// ����
public:
	CEditorView();
	DECLARE_DYNCREATE(CEditorView)

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual	void OnDraw(CDC* dc) {}
	virtual void PostNcDestroy() {}

// ʵ��
public:
	virtual ~CEditorView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	DECLARE_MESSAGE_MAP()
};

