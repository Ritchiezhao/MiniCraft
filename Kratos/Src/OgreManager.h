#ifndef OGRE_MANAGER_H
#define OGRE_MANAGER_H

#include "Singleton.h"
#include <OgrePrerequisites.h>
#include <OgreWindowEventUtilities.h>
#include <OgreShadowCameraSetup.h>

//效果设置
struct SEffectConfig 
{
	SEffectConfig() { Reset(); }
	void	Reset() { bShadow = false; bSSAO = false; }

	bool	bShadow;
	bool	bSSAO;
};

/*------------------------------------------------
				 OGRE图形模块封装类
-------------------------------------------------*/
namespace Ogre
{
	class PSSMShadowCameraSetup;
}
class DeferredShadingSystem;

class COgreManager : public Ogre::WindowEventListener, public CSingleton<COgreManager>
{
	DECLEAR_SINGLETON(COgreManager);
	COgreManager(void);
	~COgreManager(void);

public:
	//编辑器与客户端初始化不同.后4个参数用于编辑器初始化
	bool			Init(bool bEditor, HWND externalHwnd=nullptr, HWND hwndParent=nullptr, int width=0, int height=0);
	//更新图形.返回true表示游戏继续进行,返回false表示退出.
	bool			Update(float dt);
	void			Shutdown();
	bool			IsInit() { return m_bHasInit; }
	void			ResetEffect();

	void			MessagePump()		{ Ogre::WindowEventUtilities::messagePump(); }
	bool			IsMainWndClosed();
	bool			IsMainWndActive();
	Ogre::Timer*	GetTimer()			{ return m_Timer; }
	void			GetMainWndHandle(unsigned long& hwnd);
	Ogre::PSSMShadowCameraSetup*	GetShadowCameraSetup() { return (Ogre::PSSMShadowCameraSetup*)mPSSMSetup.get(); }

	const SEffectConfig&	GetEffectConfig() const { return m_effectCfg; }
	void			EnableShadow(bool bEnable);
	//void			EnableDLAA(bool bEnable);
	void			EnableSSAO(bool bEnable);
	void			SetSSAOParam(const Ogre::String& name, float val, bool bRemoveAndAdd = true);

	Ogre::Root*			mRoot;
	Ogre::RenderWindow* mWindow;
	Ogre::Viewport*		m_pViewport;
	Ogre::Timer*		m_Timer;
	Ogre::SceneManager*	m_pSceneMgr;
	Ogre::Camera*		m_pMainCamera;
	DeferredShadingSystem*	m_pDS;
	Ogre::ShadowCameraSetupPtr mPSSMSetup;

private:
	bool				m_bHasInit;
	SEffectConfig		m_effectCfg;
	
	Ogre::CompositorInstance*	m_dlaa;
	Ogre::CompositorInstance*	m_ssao;

	void windowResized(Ogre::RenderWindow* rw);
	void windowClosed(Ogre::RenderWindow* rw);
};

#define RenderManager COgreManager::GetSingleton()

#endif
