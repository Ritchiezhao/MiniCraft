#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Singleton.h"
#include <boost/bind.hpp>
#include <boost/signal.hpp>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

//�����¼����ȼ�,�ɸߵ���
enum eInputEventPriority
{
	eInputEventPriority_GUI			=	0,		//GUI�¼���Ӧ
	eInputEventPriority_Targeting	=	1,		//���ѡ��Ŀ��
	eInputEventPriority_default		=	2,
	eInputEventPriority_Count
};

enum eInputEvent
{
	eInputEvent_MouseMove,
	eInputEvent_MouseBtnDown,
	eInputEvent_MouseBtnUp,
	eInputEvent_KeyDown,
	eInputEvent_KeyUp,
	eInputEvent_Count
};

/*------------------------------------------------
					����������������
-------------------------------------------------*/

class CInputManager : public CSingleton<CInputManager>, public OIS::MouseListener, public OIS::KeyListener
{
	DECLEAR_SINGLETON(CInputManager);
	CInputManager();
	~CInputManager();

	//signal combiner
	struct InputHandler 
	{  
		typedef bool result_type;
		template<typename InputIterator>  
		bool operator()(InputIterator first, InputIterator last) const  
		{    
			while (first != last)
			{     
				if (true == *first)       
					return true;       //ĳ��slot�����˸��¼�����true,�����ټ�������
				++first;    
			}    
			return false; 
		}
	};
	typedef boost::function<bool(const OIS::MouseEvent&)> MouseMoveHandler;
	typedef boost::function<bool(const OIS::MouseEvent&, OIS::MouseButtonID)> MouseBtnHandler;
	typedef boost::function<bool(const OIS::KeyEvent&)> KeyHandler;

public:
	bool Init();
	void Shutdown();
	bool IsInit() { return m_bIsInit; }
	//���������豸
	void Capture();

	//�ҽ�������¼�,�ڶ��������ǵ���˳��,Ĭ���Ƿŵ����
	void BindMouseMove(const MouseMoveHandler& handler, eInputEventPriority priority=eInputEventPriority_default);
	//�ҽ�����ɿ��¼�
	void BindMousePressed(const MouseBtnHandler& handler, eInputEventPriority priority=eInputEventPriority_default);
	//�ҽ�����ƶ��¼�
	void BindMouseRelease(const MouseBtnHandler& handler, eInputEventPriority priority=eInputEventPriority_default);
	//�ҽӼ��̰����¼�
	void BindKeyPressed(const KeyHandler& handler, eInputEventPriority priority=eInputEventPriority_default);
	//�ҽӼ����ɿ��¼�
	void BindKeyReleased(const KeyHandler& handler, eInputEventPriority priority=eInputEventPriority_default);

	//�Ͽ��ҽ������¼�
	void UnbindMouseMove(eInputEventPriority priority);
	void UnbindMousePressed(eInputEventPriority priority);
	void UnbindMouseRelease(eInputEventPriority priority);
	void UnbindKeyPressed(eInputEventPriority priority);
	void UnbindKeyReleased(eInputEventPriority priority);

	//����/��ͨ�ҽ�����
	void BlockMouseMove(eInputEventPriority priority, bool bBlock);
	void BlockMousePressed(eInputEventPriority priority, bool bBlock);
	void BlockMouseRelease(eInputEventPriority priority, bool bBlock);
	void BlockKeyPressed(eInputEventPriority priority, bool bBlock);
	void BlockKeyReleased(eInputEventPriority priority, bool bBlock);

private:
	OIS::InputManager* mInputManager;
	OIS::Mouse*    mMouse;
	OIS::Keyboard* mKeyboard;
	bool			m_bIsInit;

	//����boost signal�����������¼�
	boost::signal<bool(const OIS::MouseEvent&), InputHandler> m_MouseMoveSignal;
	boost::signal<bool(const OIS::MouseEvent&, OIS::MouseButtonID), InputHandler> m_MousePressedSignal;
	boost::signal<bool(const OIS::MouseEvent&, OIS::MouseButtonID), InputHandler> m_MouseReleasedSignal;
	boost::signal<bool(const OIS::KeyEvent&), InputHandler> m_KeyPressedSignal;
	boost::signal<bool(const OIS::KeyEvent&), InputHandler> m_KeyReleasedSignal;

	typedef std::vector<boost::signals::connection>	ConnectionGroup;
	typedef std::vector<ConnectionGroup>	ConnectionPriorityGroup;
	ConnectionPriorityGroup		m_connections;		//�ź����Ӵ洢����

	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg ) { return m_MouseMoveSignal(arg); }
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) { return m_MousePressedSignal(arg, id); }
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) { return m_MouseReleasedSignal(arg, id); }
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg ) { return m_KeyPressedSignal(arg); }
	virtual bool keyReleased( const OIS::KeyEvent &arg ) { return m_KeyReleasedSignal(arg); }
};

#endif
