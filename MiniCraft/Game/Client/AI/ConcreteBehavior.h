/********************************************************************
	created:	28:3:2013   21:41
	filename	ConcreteBehavior.h
	author:		maval

	purpose:	��Ϊ��������Ϊ���ÿ�
*********************************************************************/

#ifndef ConcreteBehavior_h__
#define ConcreteBehavior_h__

#include "Behavior.h"

///������Ϊ
class aiBehaviorIdle : public aiBehavior
{
public:
	virtual	void	Execute(Ogre::Any& owner);
};

///����˻����ƶ���Ϊ
class aiBehaviorMoveToEnemyBase : public aiBehavior
{
public:
	virtual	void	Execute(Ogre::Any& owner);
};

#endif // ConcreteBehavior_h__