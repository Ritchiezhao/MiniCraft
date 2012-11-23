#ifndef BATTLE_STATE_H
#define BATTLE_STATE_H

#include "AppState.h"




/************************************************************************/
/*							��Ϸ����״̬��                                */
/************************************************************************/

class CBattleState : public CAppState
{
public:
	CBattleState();
	~CBattleState();

	DECLARE_APPSTATE_CLASS(CBattleState)

	void enter();
	void createScene();
	void exit();
	bool pause();
	void resume();
	void update(float timeSinceLastFrame);
	void render();

	static std::string StateName;

private:
};


#endif