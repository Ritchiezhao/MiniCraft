/********************************************************************
	created:	28:3:2013   1:35
	filename	Behavior.h
	author:		maval

	purpose:	Behavior��ʾActionNodeִ�е�һ����Ϊ.
				���п��ܵ���Ϊ������������,��λ�κ�ʱ��һ������ĳһ����Ϊ��
*********************************************************************/

#ifndef Behavior_h__
#define Behavior_h__

#include "KratosPrerequisites.h"

class Unit;

///��Ϊ����
class aiBehavior
{
public:
	aiBehavior() {}
	virtual ~aiBehavior() {}

public:
	virtual	void	Execute(Unit* pUnit) = 0;

private:
	aiBehavior(const aiBehavior&);
	aiBehavior& operator= (const aiBehavior&);
};

///������Ϊ
class aiBehaviorIdle : public aiBehavior
{
public:
	virtual	void	Execute(Unit* pUnit);
};

///����˻����ƶ���Ϊ
class aiBehaviorMoveToEnemyBase : public aiBehavior
{
public:
	virtual	void	Execute(Unit* pUnit);
};

#endif // Behavior_h__