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

namespace Ogre
{
	class Any;
}

///��Ϊ����
class aiBehavior
{
public:
	aiBehavior() {}
	virtual ~aiBehavior() {}

public:
	virtual	void	Execute(Ogre::Any& owner) = 0;

private:
	aiBehavior(const aiBehavior&);
	aiBehavior& operator= (const aiBehavior&);
};

#endif // Behavior_h__