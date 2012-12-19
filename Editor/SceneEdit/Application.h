/********************************************************************
	created:	14:10:2012   9:15
	filename: 	C:\Users\mavaL\Desktop\SceneEdit\SceneEdit\SceneEdit\Application.h
	author:		maval
	
	purpose:	�༭��Ӧ�ó�������
*********************************************************************/


#pragma once

#include <Ogre.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>


using namespace Ogre;


class Application : public OIS::MouseListener, OIS::KeyListener
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

private:
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg ); 

private:
	void		_InitOgre(int width, int height, HWND hwnd, HWND hParent);
	void		_InitOIS(HWND hwnd);

	RenderWindow*		m_pRenderWnd;
	Root*				m_pRoot;
	Camera*				m_pMainCam;
	SceneManager*		m_pSceneMgr;
	OIS::InputManager*	m_pInputManager;
	OIS::Mouse*			m_pMouse;
	OIS::Keyboard*		m_pKeyboard;

	bool				m_bQuit;
	bool				m_bRButtonDown;
	Vector3				m_tranVector;
};


