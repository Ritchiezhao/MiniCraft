#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "Singleton.h"
#include "CEGUI.h"
#include "GameDefine.h"
#include "InputManager.h"
#include "CommandPanel.h"

namespace CEGUI
{
	class OgreRenderer;
}

/*------------------------------------------------
					CEGUIģ���װ��
-------------------------------------------------*/

class CGUIManager : public CSingleton<CGUIManager>
{
	DECLEAR_SINGLETON(CGUIManager);

	CGUIManager(void);
	virtual ~CGUIManager(void);

public:
	bool	Init();
	void	Shutdown();
	void	ShowCursor(bool bEnable);
	CEGUI::Window*	LoadWindowLayout(const STRING& name);
	void	UnloadWindowLayout(CEGUI::Window* pWnd);
	void	SetGUISheet(CEGUI::Window* pWnd);

	///��ȡUI���
public:
	UiCommandPanel*		GetCommandPanel() { return &m_cmdPanel; }

private:
	CEGUI::OgreRenderer*	m_pRenderer;
	CEGUI::System*			m_pSystem;
	UiCommandPanel			m_cmdPanel;

	//Hook����Ⱦ�¼�,�����Զ�������
	bool overlayHandler(const CEGUI::EventArgs& args);
//	CEGUI::GeometryBuffer* m_pGeometryBuffer; //���������ٶ����ֵ�Buffer


	//�ҽ�����ϵͳ����¼�
	bool OnInputSys_MousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool OnInputSys_MouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool OnInputSys_MouseMove(const OIS::MouseEvent &arg);
};

#endif
