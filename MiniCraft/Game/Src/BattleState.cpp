#include "stdafx.h"
#include "GameDefine.h"
#include "BattleState.h"
#include "OgreManager.h"
#include "Unit.h"
#include "Command.h"
#include "UnitState.h"
#include "World.h"




std::string CBattleState::StateName = "BattleState";

CBattleState::CBattleState()
:m_pCamera(nullptr)
,m_bCamMoveLeft(false)
,m_bCamMoveRight(false)
,m_bCamMoveUp(false)
,m_bCamMoveDown(false)
{
}

CBattleState::~CBattleState()
{
}

void CBattleState::enter()
{
	using namespace Ogre;

	World::GetSingleton().Init();

	Unit* pTestUnit = World::GetSingleton().CreateUnit();
	pTestUnit->SetState(eUnitState_Idle);

	SceneManager* pSceneMgr = Root::getSingleton().getSceneManager(SCENE_MANAGER_NAME);
	m_pCamera = pSceneMgr->createCamera("GodViewCam");
	m_pCamera->setNearClipDistance(1.0f);
	COgreManager::GetSingleton().GetViewport()->setCamera(m_pCamera);

	//45�ȸ���
	m_pCamera->setPosition(0, 50, 0);
	m_pCamera->lookAt(0, 0, 50);

	//�������¼�
	CInputManager& inputMgr = CInputManager::GetSingleton();
	inputMgr.BindKeyPressed(boost::bind(&CBattleState::OnInputSys_KeyPressed, this, _1));
	inputMgr.BindKeyReleased(boost::bind(&CBattleState::OnInputSys_KeyReleased, this, _1));
	inputMgr.BindMousePressed(boost::bind(&CBattleState::OnInputSys_MousePressed, this, _1, _2));
	inputMgr.BindMouseRelease(boost::bind(&CBattleState::OnInputSys_MouseReleased, this, _1, _2));
	inputMgr.BindMouseMove(boost::bind(&CBattleState::OnInputSys_MouseMove, this, _1));

	m_bQuit = false;
}

bool CBattleState::pause()
{
    return true;
}

void CBattleState::resume()
{
	
}

void CBattleState::exit()
{
	World::GetSingleton().Shutdown();

	COgreManager::GetSingleton().GetViewport()->setCamera(nullptr);
	m_pCamera = nullptr;
}

void CBattleState::update(float timeSinceLastFrame)
{
	if(m_bQuit)
	{
		m_pParent->shutdown();
		return;
	}

	World::GetSingleton().Update(timeSinceLastFrame);

	//����������˶�
	if(m_bCamMoveLeft)	m_pCamera->move(Ogre::Vector3(timeSinceLastFrame*40, 0, 0));
	if(m_bCamMoveRight) m_pCamera->move(Ogre::Vector3(-timeSinceLastFrame*40, 0, 0));
	if(m_bCamMoveUp)	m_pCamera->move(Ogre::Vector3(0, 0, timeSinceLastFrame*40));
	if(m_bCamMoveDown)	m_pCamera->move(Ogre::Vector3(0, 0, -timeSinceLastFrame*40));
}

bool CBattleState::OnInputSys_MousePressed( const OIS::MouseEvent& arg, OIS::MouseButtonID id )
{
	if(id == OIS::MB_Left)
	{

	}
	else if (id == OIS::MB_Right)
	{
		//���ʰȡ�����Ƿ�����Ϸ�����ཻ
		float screenX = arg.state.X.abs / (float)arg.state.width;
		float screenY = arg.state.Y.abs / (float)arg.state.height;
		Ogre::Ray ray;
		m_pCamera->getCameraToViewportRay(screenX, screenY, &ray);
		Ogre::Plane floor(Ogre::Vector3::UNIT_Y, 0);
		auto result = ray.intersects(floor);
		if (result.first)
		{
			Unit* pUnit = World::GetSingleton().GetUnitFromID(0);
			CommandBase* pCmd = _ComputeCommand(pUnit, ray.getPoint(result.second));
			if(pCmd)
				pUnit->GiveCommand(*pCmd);
			delete pCmd;
		}
	}        

	return true;
}

bool CBattleState::OnInputSys_MouseReleased( const OIS::MouseEvent& arg, OIS::MouseButtonID id )
{
	return true;
}

bool CBattleState::OnInputSys_MouseMove( const OIS::MouseEvent& arg )
{
	//��ȡ��Ļ�ߴ�
	Ogre::RenderWindow* pRenderWnd = COgreManager::GetSingleton().GetRenderWindow();
	int w = (int)pRenderWnd->getWidth(), h = (int)pRenderWnd->getHeight();
	//��ȡ��ǰ������λ��
	int absX = arg.state.X.abs, absY = arg.state.Y.abs;

	if	(absX == w		&& arg.state.X.rel	> 0 ) m_bCamMoveRight = true;
	else if(absX == 0	&& arg.state.X.rel < 0)	m_bCamMoveLeft = true;
	if(absY == h	&& arg.state.Y.rel > 0) m_bCamMoveDown = true;
	else if(absY == 0	&& arg.state.Y.rel < 0) m_bCamMoveUp = true;

	if (absX > 0 && absX < w)
		m_bCamMoveRight = m_bCamMoveLeft = false;
	if (absY > 0 && absY < h)
		m_bCamMoveUp = m_bCamMoveDown = false;

	return true;
}

bool CBattleState::OnInputSys_KeyPressed( const OIS::KeyEvent& arg )
{
	return true;
}

bool CBattleState::OnInputSys_KeyReleased( const OIS::KeyEvent& arg )
{
	if(arg.key == OIS::KC_ESCAPE)
		m_bQuit = true;

	return true;
}

void CBattleState::_QueryCursorPos( Ogre::Vector3& retPos )
{

}

CommandBase* CBattleState::_ComputeCommand( Unit* pUnit, const Ogre::Vector3& targetPos )
{
	CommandBase* pCmd = nullptr;

	//����Ƿ�Ŀ��㳬������Ϸ��ͼ
	//TODO:������п��ܼ���Map��,������ݺͲ�����װ��ȥ
	if(targetPos.x < -50 || targetPos.x > 50 || targetPos.z < -50 || targetPos.z > 50)
		return nullptr;

	static Ogre::Vector3 goldArea = World::GetSingleton().GetResAABB().getHalfSize();
	if (targetPos.x >= -goldArea.x && 
		targetPos.x <= goldArea.x &&
		targetPos.y >= -goldArea.z &&
		targetPos.y <= goldArea.z)
	{
		//�ɼ���Դ
		pCmd = new HarvestCommand(pUnit);
	}
	else
	{
		//ִ���ƶ�����
		pCmd = new MoveCommand(pUnit, targetPos);
	}

	return pCmd;
}
