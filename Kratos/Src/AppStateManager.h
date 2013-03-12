#ifndef APP_STATE_MANAGER_H
#define APP_STATE_MANAGER_H


#include "AppState.h"
#include "Singleton.h"
#include <OgrePrerequisites.h>

namespace Kratos
{

	/************************************************************************/
	/*							����״̬������								*/
	/************************************************************************/

	class CAppStateManager : public CSingleton<CAppStateManager>, public AppStateListener
	{
		DECLEAR_SINGLETON(CAppStateManager);
		CAppStateManager();
		~CAppStateManager();

	public:
		struct state_info
		{
			std::string name;
			CAppState* state;
		};

		//�˳���Ϸ
		void shutdown();
		//���µ�ǰ״̬�߼�,����false�����˳���Ϸ
		bool UpdateCurrentState(float dt);

		CAppState* getCurState();
		void manageAppState(const std::string& stateName, CAppState* state);
		CAppState* findByName(const std::string& stateName);
		void changeAppState(CAppState* state);
		bool pushAppState(CAppState* state);
		void popAppState();
		void pauseAppState();
		void popAllAndPushAppState(CAppState* state);

	protected:
		void _init(CAppState *state);

		std::vector<CAppState*>		m_ActiveStateStack;
		std::vector<state_info>		m_States;
		bool						m_bShutdown;
	};

}


#endif