/********************************************************************
	created:	14:10:2012   9:15
	filename: 	C:\Users\mavaL\Desktop\SceneEdit\SceneEdit\SceneEdit\Application.h
	author:		maval
	
	purpose:	�༭��Ӧ�ó�������
*********************************************************************/

#ifndef Application_h__
#define Application_h__

namespace Ogre
{
	class RenderWindow;
	class Root;
}

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

	void		SceneNew();
	void		SceneOpen();
	void		SceneSave();
	void		SceneClose();

	void		OnLButtonDown(const POINT& pt);
	void		OnLButtonUp(const POINT& pt);
	void		OnRButtonDown(const POINT& pt);
	void		OnRButtonUp(const POINT& pt);
	void		OnMouseMove(const POINT& pt);
	void		OnMouseWheel(short nNotch);

private:
	void		_InitOgre(int width, int height, HWND hwnd, HWND hParent);
	void		_UpdateInput(float dt);
	void		_CreateActionParam(const POINT& viewClientPt, SActionParam& retParam);

	Ogre::RenderWindow*	m_pRenderWnd;
	Ogre::Root*			m_pRoot;
};

#endif // Application_h__


