/********************************************************************
	created:	10:2:2013   13:56
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\AI\ObjectState.h
	author:		maval
	
	purpose:	��Ϸ����״̬����ϵ.������Ϊ�����߼�״̬������.
*********************************************************************/
#ifndef ObjectState_h__
#define ObjectState_h__


enum eObjectState
{
	eObjectState_Idle,			//����״̬
	eObjectState_Produce		//����״̬
};

class SelectableObject;

///״̬����
class ObjectState
{
public:
	ObjectState(eObjectState type):m_type(type) {}
	virtual ~ObjectState() {}

public:
	virtual	void Enter(SelectableObject* pOwner) = 0;
	virtual void Update(float dt, SelectableObject* pOwner) = 0;
	virtual void Exit(SelectableObject* pOwner) = 0;

public:
	eObjectState	GetType() const { return m_type; }

private:
	eObjectState	m_type;
};

///����״̬
class StateIdle : public ObjectState
{
public:
	StateIdle():ObjectState(eObjectState_Idle) {}

public:
	virtual	void Enter(SelectableObject* pOwner) {}
	virtual void Update(float dt, SelectableObject* pOwner) {}
	virtual void Exit(SelectableObject* pOwner) {}
};

///����״̬
class StateProduce : public ObjectState
{
public:
	StateProduce():ObjectState(eObjectState_Produce) {}

public:
	virtual	void Enter(SelectableObject* pOwner);
	virtual void Update(float dt, SelectableObject* pOwner);
	virtual void Exit(SelectableObject* pOwner);
};


#endif // ObjectState_h__