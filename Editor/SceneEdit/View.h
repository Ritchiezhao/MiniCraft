
// View.h : CEditorView ��Ľӿ�
//


#pragma once


// CEditorView ����

class CEditorView : public CView
{
// ����
public:
	CEditorView();

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
	DECLARE_MESSAGE_MAP()
};

