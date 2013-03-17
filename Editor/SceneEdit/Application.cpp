#include "stdafx.h"
#include "Application.h"
#include "EditorDefine.h"
#include "UI/DialogSceneNew.h"
#include "Manipulator/ManipulatorScene.h"
#include "Manipulator/ManipulatorAction.h"
#include "Action/ActionBase.h"
#include "MainFrm.h"
#include "Scene.h"
#include "OgreManager.h"


Application::Application()
:m_appSnapshot(0)
{
}

void Application::Init( int width, int height, HWND hwnd, HWND hParent )
{
	RenderManager.Init(true, hwnd, hParent, width, height);

	ManipulatorScene& manScene = ManipulatorScene::GetSingleton();
	manScene.Init();
	manScene.GetGameData().LoadAllXml();
}

bool Application::Update()
{
	_UpdateInput(TIME_PER_FRAME);

	ManipulatorAction::GetSingleton().GetActiveActoin()->OnFrameMove(TIME_PER_FRAME);
	ManipulatorSystem.OnFrameMove(TIME_PER_FRAME);

	RenderManager.mRoot->renderOneFrame();

	return true;
}

void Application::Shutdown()
{
	SceneClose();
	ManipulatorSystem.Shutdown();
}

void Application::SceneNew()
{
	DialogSceneNew dlg;
	std::wstring newSceneName;
	if (IDOK == dlg.DoModal(ManipulatorSystem.GetScenePath(), newSceneName))
	{
		if(SceneClose())
		{
			ManipulatorSystem.SceneNew(newSceneName);
			m_appSnapshot = ManipulatorSystem.GetOperation().SnapshotMake();
		}
	}
}

void Application::SceneOpen()
{
	std::wstring strFilename;
	CFileDialog dlgFile(TRUE);	
	dlgFile.GetOFN().lpstrFilter = L"*.scene";
	dlgFile.GetOFN().lpstrDefExt = L"scene";
	//dlgFile.GetOFN().lpstrInitialDir = path; 
	dlgFile.GetOFN().lpstrTitle = L"Open Scene"; 

	if(IDOK == dlgFile.DoModal())
	{
		if(SceneClose())
		{
			strFilename = dlgFile.GetOFN().lpstrFile;
			ManipulatorSystem.SceneOpen(strFilename);
			m_appSnapshot = ManipulatorSystem.GetOperation().SnapshotMake();
		}
	}
}

void Application::SceneSave()
{
	ManipulatorSystem.SceneSave();
	m_appSnapshot = ManipulatorSystem.GetOperation().SnapshotMake();
}

bool Application::SceneClose()
{
	//��ʾ����
	bool bNeedSave = !ManipulatorSystem.GetOperation().SnapshotCheck(m_appSnapshot);
	if (bNeedSave)
	{
		int ret = MessageBox(nullptr, L"Warning! The scene has changed, save it?", L"Warning", MB_ICONWARNING|MB_YESNOCANCEL);
		if(ret == IDYES)
			ManipulatorScene::GetSingleton().SceneSave();
		else if(ret == IDCANCEL)
			return false;
	}

	ManipulatorScene::GetSingleton().SceneClose();
	return true;
}

void Application::OnViewportResized()
{
	Ogre::Camera* cam = RenderManager.m_pMainCamera;
	Ogre::RenderWindow* wnd = RenderManager.mWindow;

	//�豸��ʧ
	if (cam)
	{
		wnd->windowMovedOrResized();	
		cam->setAspectRatio(wnd->getWidth()/(float)wnd->getHeight()); 
		//reset �豸
		wnd->update();
	}
}

void Application::_UpdateInput(float dt)
{
	static bool bZKeyDown = false;
	static bool bYKeyDown = false;

	//ȡ����ǰ�༭������״̬
	if(GetAsyncKeyState(VK_ESCAPE) < 0)
	{
		ManipulatorAction::GetSingleton().SetActiveAction(eActionType_None);
	}

	//Undo?
	if (GetAsyncKeyState('Z') < 0)
	{
		if (!bZKeyDown && GetAsyncKeyState(VK_CONTROL) < 0)
		{
			bZKeyDown = true;
			ManipulatorSystem.GetOperation().Undo();
		}
	}
	else
	{
		bZKeyDown = false;
	}
	
	//Redo?
	if (GetAsyncKeyState('Y') < 0)
	{
		if (!bYKeyDown && GetAsyncKeyState(VK_CONTROL) < 0)
		{
			bYKeyDown = true;
			ManipulatorSystem.GetOperation().Redo();
		}
	}
	else
	{
		bYKeyDown = false;
	}
}

void Application::OnLButtonDown( const POINT& pt )
{
	if(!ManipulatorSystem.GetIsSceneReady())
		return;

	SActionParam param;
	_CreateActionParam(pt, param);

	ManipulatorAction::GetSingleton().GetActiveActoin()->OnMouseLButtonDown(param);

	ManipulatorSystem.GetCamera().OnLButtonDown(param);
}

void Application::OnLButtonUp( const POINT& pt )
{
	if(!ManipulatorSystem.GetIsSceneReady())
		return;

	SActionParam param;
	_CreateActionParam(pt, param);

	ManipulatorAction::GetSingleton().GetActiveActoin()->OnMouseLButtonUp(param);

	ManipulatorSystem.GetCamera().OnLButtonUp(param);
}

void Application::OnMouseMove( const POINT& pt )
{
	if(!ManipulatorSystem.GetIsSceneReady())
		return;

	SActionParam param;
	_CreateActionParam(pt, param);

	ManipulatorAction::GetSingleton().GetActiveActoin()->OnMouseMove(param);

	ManipulatorSystem.GetCamera().OnMouseMove(param);
}

void Application::OnRButtonDown( const POINT& pt )
{
	if(!ManipulatorSystem.GetIsSceneReady())
		return;

	SActionParam param;
	_CreateActionParam(pt, param);

	ManipulatorAction::GetSingleton().GetActiveActoin()->OnMouseRButtonDown(param);

	ManipulatorSystem.GetCamera().OnRButtonDown(param);
}

void Application::OnRButtonUp( const POINT& pt )
{
	if(!ManipulatorSystem.GetIsSceneReady())
		return;

	SActionParam param;
	_CreateActionParam(pt, param);

	ManipulatorAction::GetSingleton().GetActiveActoin()->OnMouseRButtonDown(param);

	ManipulatorSystem.GetCamera().OnRButtonUp(param);
}

void Application::OnMouseWheel( short nNotch )
{
	if(!ManipulatorSystem.GetIsSceneReady())
		return;

	ManipulatorSystem.GetCamera().OnMouseWheel(nNotch);
}

void Application::_CreateActionParam( const POINT& viewClientPt, SActionParam& retParam )
{
	Ogre::RenderWindow* wnd = RenderManager.mWindow;

	retParam.m_ptPixel = Ogre::Vector2((float)viewClientPt.x, (float)viewClientPt.y);
	retParam.m_ptRelative.x = viewClientPt.x / (float)wnd->getWidth();
	retParam.m_ptRelative.y = viewClientPt.y / (float)wnd->getHeight();

	static Ogre::Vector2 lastPt = retParam.m_ptPixel;
	retParam.m_ptDeltaRel = retParam.m_ptPixel - lastPt;
	retParam.m_ptDeltaRel.x /= wnd->getWidth();
	retParam.m_ptDeltaRel.y /= wnd->getHeight();

	const Ogre::Ray ray = RenderManager.m_pMainCamera->getCameraToViewportRay(retParam.m_ptRelative.x, retParam.m_ptRelative.y);
	retParam.m_bHitTerrain = ManipulatorSystem.GetTerrain().GetRayIntersectPoint(ray, retParam.m_ptTerrain);

	lastPt = retParam.m_ptPixel;
}




