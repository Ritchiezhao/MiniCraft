/********************************************************************
	created:	14:10:2012   9:15
	filename: 	C:\Users\mavaL\Desktop\SceneEdit\SceneEdit\SceneEdit\Application.h
	author:		maval
	
	purpose:	�༭��Ӧ�ó�������
*********************************************************************/


#pragma once

#include <Ogre.h>


using namespace Ogre;

struct SActionParam;

class Application
{
public:
	Application();
	~Application() {}

public:
	void		Init(int width, int height, HWND hwnd, HWND hParent);
	bool		Update();
	void		Shutdown();
	//��Ⱦ�ӿڴ�С�ı�,������Ӧ����
	void		OnViewportResized();
	//RTT��Ⱦ����mesh��ͼ��,����Icon�б��mesh�����б�
	void		RenderAllMeshIcons(CImageList& retImageList, Ogre::StringVectorPtr& retMeshNames);

	void		SceneNew();
	void		SceneOpen();
	void		SceneSave();
	void		SceneClose();

	void		OnLButtonDown(const POINT& pt);
	void		OnLButtonUp(const POINT& pt);
	void		OnRButtonDown(const POINT& pt);
	void		OnRButtonUp(const POINT& pt);
	void		OnMouseMove(const POINT& pt);

private:
	void		_InitOgre(int width, int height, HWND hwnd, HWND hParent);
	void		_UpdateInput(float dt);
	void		_CreateActionParam(const POINT& viewClientPt, SActionParam& retParam);

	RenderWindow*		m_pRenderWnd;
	Root*				m_pRoot;
	Camera*				m_pMainCam;
	SceneManager*		m_pSceneMgr;
	bool				m_bRBDown;
};


