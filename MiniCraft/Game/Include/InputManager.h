#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Singleton.h"
#include <boost/bind.hpp>
#include <boost/signal.hpp>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

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
	//��ʼ������ϵͳ
	bool Init();
	//�ر�����ϵͳ
	void Shutdown();
	//����ϵͳ�Ƿ��ѳ�ʼ��
	bool IsInit() { return m_bIsInit; }
	//���������豸
	void Capture();

	//�ҽ�������¼�,�ڶ��������ǵ���˳��,Ĭ���Ƿŵ����
	void BindMouseMove(const MouseMoveHandler& handler, int priority=0);
	//�ҽ�����ɿ��¼�
	void BindMousePressed(const MouseBtnHandler& handler, int priority=0);
	//�ҽ�����ƶ��¼�
	void BindMouseRelease(const MouseBtnHandler& handler, int priority=0);
	//�ҽӼ��̰����¼�
	void BindKeyPressed(const KeyHandler& handler, int priority=0);
	//�ҽӼ����ɿ��¼�
	void BindKeyReleased(const KeyHandler& handler, int priority=0);

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

	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
};

#endif
