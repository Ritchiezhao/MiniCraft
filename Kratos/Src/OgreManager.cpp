#include "OgreManager.h"
#include <Ogre.h>

using namespace Ogre;


COgreManager::COgreManager(void)
: mRoot(0),
mWindow(0),
m_Timer(NULL),
m_bHasInit(false),
m_pViewport(NULL)
{
}

COgreManager::~COgreManager(void)
{
}

bool COgreManager::Init()
{
	//��Դ�����ļ��Ͳ�������ļ�
	String ResourceCfg, PluginCfg;
#ifdef _DEBUG
	ResourceCfg = "resources_d.cfg";
	PluginCfg = "plugins_d.cfg";
#else
	ResourceCfg = "resources.cfg";
	PluginCfg = "plugins.cfg";
#endif

	mRoot = new Ogre::Root(PluginCfg);

	Ogre::ConfigFile cf;
	cf.load(ResourceCfg);
	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
	
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}
	//ogre.cfg
	if(mRoot->restoreConfig() || mRoot->showConfigDialog())
	{
		mWindow = mRoot->initialise(true, "Game : MiniCraft");
	}
	else
	{
		return false;
	}

	m_pViewport = mWindow->addViewport(NULL);
	m_pViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	//Set initial mouse clipping size
	windowResized(mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	m_Timer = new Ogre::Timer();
	m_Timer->reset();
	mWindow->setActive(true);
	m_bHasInit = true;

	return true;
}

//Adjust mouse clipping area
void COgreManager::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

// 	const OIS::MouseState &ms = mMouse->getMouseState();
// 	ms.width = width;
// 	ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void COgreManager::windowClosed(Ogre::RenderWindow* rw)
{
// 	//Only close for window that created OIS (the main window in these demos)
// 	if( rw == mWindow )
// 		CInputManager::GetSingleton().Shutdown();
}

void COgreManager::Shutdown()
{
	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	//��������ϵͳ
	windowClosed(mWindow);
	//����Root
	delete mRoot;
}

bool COgreManager::Update(float dt)
{
	if(mWindow->isClosed())
		return false;

	mRoot->renderOneFrame(dt);

	return true;
}

bool COgreManager::IsMainWndClosed()
{
	return mWindow->isClosed();
}

bool COgreManager::IsMainWndActive()
{
	return mWindow->isActive();
}

void COgreManager::GetMainWndHandle( unsigned long& hwnd )
{
	mWindow->getCustomAttribute("WINDOW", &hwnd);
}
