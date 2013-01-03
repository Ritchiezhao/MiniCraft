/********************************************************************
	created:	24:12:2012   0:25
	filename: 	F:\MiniCraft\Editor\SceneEdit\Manipulator\ManipulatorAction.h
	author:		maval
	
	purpose:	�༭��Action������
*********************************************************************/

#ifndef ManipulatorAction_h__
#define ManipulatorAction_h__

#include "Singleton.h"


enum eActionType
{
	eActionType_None,
	eActionType_TerrainDeform,
	eActionType_TerrainSplat,
	eActionType_ObjectEdit,
	eActionType_ObjectSelect
};

class ActionBase;

class ManipulatorAction : public CSingleton<ManipulatorAction>
{
	ManipulatorAction();
	virtual ~ManipulatorAction();
	DECLEAR_SINGLETON(ManipulatorAction);

	typedef std::unordered_map<eActionType, ActionBase*>	ActionMap;

public:
	//�л�����״̬
	void			SetActiveAction(eActionType type);
	ActionBase*		GetActiveActoin() { return m_pActiveAction; }

private:
	ActionBase*		m_pActiveAction;	//��ǰ����״̬
	ActionMap		m_mapAction;		//����Action
};


#endif // ManipulatorAction_h__





