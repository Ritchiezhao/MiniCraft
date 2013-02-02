#include "stdafx.h"
#include "Application.h"
#include "InputManager.h"
#include "OgreManager.h"
#include "GUIManager.h"
#include "AppStateManager.h"
#include "ScriptSystem.h"
#include "BattleState.h"



Applicaton::Applicaton()
:m_stateMgr(nullptr)
,m_inputMgr(nullptr)
,m_ogreMgr(nullptr)
,m_guiMgr(nullptr)
{

}

Applicaton::~Applicaton()
{
}

bool Applicaton::Init()
{
	m_stateMgr = CAppStateManager::GetSingletonPtr();
	m_inputMgr = CInputManager::GetSingletonPtr();
	m_ogreMgr =	COgreManager::GetSingletonPtr();
	m_guiMgr = CGUIManager::GetSingletonPtr();

	CBattleState::create(m_stateMgr, CBattleState::StateName);

	if(	!m_ogreMgr->Init()	|| 
		!m_inputMgr->Init()	||
		!m_guiMgr->Init()	)
		return false;

	ScriptSystem::GetSingleton().Init();

	return true;
}

void Applicaton::Run()
{
	//进入游戏
	m_stateMgr->changeAppState(m_stateMgr->findByName(CBattleState::StateName));

	float timeSinceLastFrame = 1;
	int startTime = 0;
	//游戏主循环
	while(true)
	{
		if(m_ogreMgr->GetRenderWindow()->isClosed())
			break;

		Ogre::WindowEventUtilities::messagePump();

		if(m_ogreMgr->GetRenderWindow()->isActive())
		{
			startTime = m_ogreMgr->GetTimer()->getMillisecondsCPU();

			//各子系统进行更新
			CInputManager::GetSingleton().Capture();
			if(!m_stateMgr->UpdateCurrentState(timeSinceLastFrame))
				break;
			if(!m_ogreMgr->Update(timeSinceLastFrame))
				break;

			timeSinceLastFrame = static_cast<float>(m_ogreMgr->GetTimer()->getMillisecondsCPU() - startTime);
			timeSinceLastFrame /= 1000.0f;
		}
		else
		{
			Sleep(1000);
		}
	}
}

void Applicaton::Shutdown()
{
	ScriptSystem::GetSingleton().Shutdown();
	m_guiMgr->Shutdown();
	m_stateMgr->shutdown();	
	m_inputMgr->Shutdown();
	m_ogreMgr->Shutdown();
}


