/********************************************************************
	created:	30:4:2013   21:47
	filename	EventCallback.h
	author:		maval

	purpose:	�¼��ص���
*********************************************************************/

#ifndef EventCallback_h__
#define EventCallback_h__

#include "EventCallbackBase.h"

////////////////////////////////////////////////////////////////////////
/// ��λ��صĻص��¼�
class Unit;

class UnitEventCallback : public Kratos::EventCallbackBase
{
public:
	virtual	void	OnUnitDeath(Unit* pUnit) {}
};

#endif // EventCallback_h__