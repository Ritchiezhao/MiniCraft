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
	eObjectState_Idle,			//����
	eObjectState_Produce,		//����
	eObjectState_Move,			//�ƶ�
	eObjectState_Targeting,		//ѡ��Ŀ��
	eObjectState_Stop,			//ֹͣ
	eObjectState_Gather,		//�ɼ���Դ
	eObjectState_Attack			//����
};

class SelectableObject;

///״̬����
class ObjectState
{
public:
	ObjectState(eObjectState type):m_type(type) {}
	virtual ~ObjectState() {}

public:
	virtual	void Enter(SelectableObject* pOwner) {}
	virtual void Update(float dt, SelectableObject* pOwner) {}
	virtual void Exit(SelectableObject* pOwner) {}

public:
	eObjectState	GetType() const { return m_type; }

private:
	ObjectState(const ObjectState&);
	ObjectState& operator= (const ObjectState&);

	eObjectState	m_type;
};

///����״̬
class StateIdle : public ObjectState
{
public:
	StateIdle():ObjectState(eObjectState_Idle) {}

public:
	virtual	void Enter(SelectableObject* pOwner);
	virtual void Exit(SelectableObject* pOwner);
};

///ѡ��Ŀ��״̬
class StateTargeting : public ObjectState
{
public:
	StateTargeting():ObjectState(eObjectState_Targeting) {}

public:
	virtual	void Enter(SelectableObject* pOwner);
	virtual void Exit(SelectableObject* pOwner);

private:
	bool		OnInputSys_MouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
	bool		OnInputSys_MouseMove(const OIS::MouseEvent &arg);
};

///�ƶ�״̬
class StateMove : public ObjectState
{
public:
	StateMove():ObjectState(eObjectState_Move) {}

public:
	virtual	void Enter(SelectableObject* pOwner);
	virtual void Update(float dt, SelectableObject* pOwner);
	virtual void Exit(SelectableObject* pOwner);
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

///ֹͣ״̬
class StateStop : public ObjectState
{
public:
	StateStop():ObjectState(eObjectState_Stop) {}

public:
	virtual	void Enter(SelectableObject* pOwner);
	virtual void Update(float dt, SelectableObject* pOwner);
};

///�ɼ�״̬
class StateGather : public ObjectState
{
public:
	StateGather():ObjectState(eObjectState_Gather) {}

public:
	virtual	void Enter(SelectableObject* pOwner);
	virtual void Update(float dt, SelectableObject* pOwner);
	virtual void Exit(SelectableObject* pOwner);
};

///����״̬
class StateAttack : public ObjectState
{
public:
	StateAttack():ObjectState(eObjectState_Attack) {}

public:
	virtual	void Enter(SelectableObject* pOwner) {}
	virtual void Update(float dt, SelectableObject* pOwner) {}
	virtual void Exit(SelectableObject* pOwner) {}
};


#endif // ObjectState_h__