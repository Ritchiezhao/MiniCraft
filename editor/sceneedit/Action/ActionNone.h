/********************************************************************
	created:	24:12:2012   0:50
	filename: 	F:\MiniCraft\Editor\SceneEdit\Action\ActionNone.h
	author:		maval
	
	purpose:	��ʾ�޼�����Ϊ
*********************************************************************/

#ifndef ActionNone_h__
#define ActionNone_h__


#include "ActionBase.h"


class ActionNone : public ActionBase
{
public:
	ActionNone() {}
	~ActionNone() {}

public:
	virtual	void	Enter() {}
	virtual void	Leave() {}
};



#endif // ActionNone_h__