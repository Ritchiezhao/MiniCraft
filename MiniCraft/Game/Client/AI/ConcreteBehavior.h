/********************************************************************
	created:	28:3:2013   21:41
	filename	ConcreteBehavior.h
	author:		maval

	purpose:	��Ϊ�������߼���Ϊ,�൱�߼���صĶ���
*********************************************************************/

#ifndef ConcreteBehavior_h__
#define ConcreteBehavior_h__

#include "Behavior.h"

///����
class aiBehaviorIdle : public Kratos::aiBehavior
{
public:
	virtual	void	Execute(Ogre::Any& owner);
	virtual void	Exit(Ogre::Any& owner);
};

///����˻����ƶ�
class aiBehaviorMoveToEnemyBase : public Kratos::aiBehavior
{
public:
	virtual	void	Execute(Ogre::Any& owner);
	virtual	void	Update(Ogre::Any& owner, float dt);
	virtual void	Exit(Ogre::Any& owner);
};

///���������ƶ�������Դ
class aiBehaviorMoveToBase : public Kratos::aiBehavior
{
public:
	virtual	void	Execute(Ogre::Any& owner);
	virtual	void	Update(Ogre::Any& owner, float dt);
	virtual void	Exit(Ogre::Any& owner);
};

///��ɲɼ���Դ�ƶ�
class aiBehaviorMoveToRes : public Kratos::aiBehavior
{
public:
	virtual	void	Execute(Ogre::Any& owner);
	virtual	void	Update(Ogre::Any& owner, float dt);
	virtual void	Exit(Ogre::Any& owner);
};

///�ɼ���Դ
class aiBehaviorGathering : public Kratos::aiBehavior
{
public:
	virtual	void	Execute(Ogre::Any& owner);
	virtual	void	Update(Ogre::Any& owner, float dt);
	virtual void	Exit(Ogre::Any& owner);
};

///�����Դ
class aiBehaviorRetriveRes : public Kratos::aiBehavior
{
public:
	virtual	void	Execute(Ogre::Any& owner);
};

///������Դ
class aiBehaviorReturnRes : public Kratos::aiBehavior
{
public:
	virtual	void	Execute(Ogre::Any& owner);
};

#endif // ConcreteBehavior_h__