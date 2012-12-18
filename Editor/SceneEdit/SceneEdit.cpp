StringVectorPtr

// SceneEdit.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "SceneEdit.h"
#include "MainFrm.h"

#include "Application.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSceneEditApp

BEGIN_MESSAGE_MAP(CSceneEditApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CSceneEditApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, CSceneEditApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CSceneEditApp::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, CSceneEditApp::OnFileSave)
	ON_COMMAND(ID_FILE_CLOSE, CSceneEditApp::OnFileClose)
END_MESSAGE_MAP()


// CSceneEditApp ����

CSceneEditApp::CSceneEditApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("SceneEdit.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CSceneEditApp ����

CSceneEditApp theApp;


// CSceneEditApp ��ʼ��

BOOL CSceneEditApp::InitInstance()
{
// 	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
// 	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
// 	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
// 	INITCOMMONCONTROLSEX InitCtrls;
// 	InitCtrls.dwSize = sizeof(InitCtrls);
// 	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
// 	// �����ؼ��ࡣ
// 	InitCtrls.dwICC = ICC_WIN95_CLASSES;
// 	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


//	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ���������ؿ�ܼ�����Դ
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	CView* pView = pFrame->GetActiveView();
	RECT rect;
	pView->GetClientRect(&rect);
	
	///////////////////////////////////////////
	///////////////////////////��ʼ��������
	m_app.Init(rect.right-rect.left, rect.bottom-rect.top, pView->GetSafeHwnd(), m_pMainWnd->GetSafeHwnd());

	///////////////////////////////////////////
	///////////////////////////��ʼ���༭��UI
	CImageList iconList;
	Ogre::StringVectorPtr meshNames;
	m_app.RenderAllMeshIcons(iconList, meshNames);

	if(!pFrame->CreateMeshPanel(iconList, meshNames))
		return FALSE;

	pFrame->CreateDockPane();

	///////////////////////////////////////////
	///////////////////////////��ʼ�����,��ʼ��Ⱦ...
	pFrame->SetTimer(0, (UINT)TIME_PER_FRAME*1000, NULL);

	return TRUE;
}

int CSceneEditApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	return CWinApp::ExitInstance();
}

// CSceneEditApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CSceneEditApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CSceneEditApp::OnFileNew()
{
	m_app.SceneNew();
}

void CSceneEditApp::OnFileOpen()
{
	m_app.SceneOpen();
}

void CSceneEditApp::OnFileSave()
{
	m_app.SceneSave();
}

void CSceneEditApp::OnFileClose()
{
	m_app.SceneClose();
}

// CSceneEditApp ��Ϣ�������



