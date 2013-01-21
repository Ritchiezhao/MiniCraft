#ifndef UNIT_STATE_H
#define UNIT_STATE_H



class Unit;

enum eUnitState
{
	///!!!!����Ҫ��UnitState.lua�еĳ������Ӧ
	// TODO:DRYԭ��,Ҳ��������Ҫ�������
	eUnitState_Idle,
	eUnitState_Move,
	eUnitState_Attack,
	eUnitState_Collect,
	eUnitState_Return,
	eUnitState_Build
};
/************************************************************************/
/*							��λ״̬����	                                */
/************************************************************************/

class UnitState
{
public:
	UnitState(Unit* pOwner):m_pOwner(pOwner) {}
	UnitState(const UnitState& rhs):m_type(rhs.GetType()),m_pOwner(rhs.GetOwner()) {}
	virtual ~UnitState() {}
public:
	virtual	void Enter() = 0;
	virtual void Update(float dt) = 0;
	virtual void Exit() = 0;
public:
	eUnitState	GetType() const { return m_type; }
	Unit*		GetOwner() const { return m_pOwner; }

protected:
	eUnitState	m_type;
	Unit*		m_pOwner;	//��״̬������λ
};

/************************************************************************/
/*							����״̬		                                */
/************************************************************************/

class IdleState : public UnitState
{
public:
	IdleState(Unit* pOwner):UnitState(pOwner),m_pIdleAnim(nullptr) { m_type = eUnitState_Idle; }
	IdleState(const IdleState& rhs):UnitState(rhs) {}
	virtual ~IdleState() {}
public:
	virtual	void Enter();
	virtual void Update(float dt);
	virtual void Exit();

private:
	Ogre::AnimationState*	m_pIdleAnim;
};

/************************************************************************/
/*							�ƶ�״̬		                                */
/************************************************************************/

class MoveState : public UnitState
{
public:
	MoveState(Unit* pOwner);
	MoveState(const MoveState& rhs):UnitState(rhs) {}
	virtual ~MoveState() {}

public:
	virtual	void Enter();
	virtual void Update(float dt);
	virtual void Exit();
};

/************************************************************************/
/*							����״̬			                            */
/************************************************************************/

class AttackState : public UnitState
{
public:
	AttackState(Unit* pOwner):UnitState(pOwner) { m_type = eUnitState_Attack; }
	AttackState(const AttackState& rhs):UnitState(rhs) {}
	virtual ~AttackState() {}
public:
	virtual	void Enter() {}
	virtual void Update(float dt) {}
	virtual void Exit() {}
};

/************************************************************************/
/*							����״̬			                            */
/************************************************************************/

class BuildState : public UnitState
{
public:
	BuildState(Unit* pOwner):UnitState(pOwner) { m_type = eUnitState_Build; }
	BuildState(const BuildState& rhs):UnitState(rhs) {}
	virtual ~BuildState() {}
public:
	virtual	void Enter() {}
	virtual void Update(float dt) {}
	virtual void Exit() {}
};


/************************************************************************/
/*							�ɼ�״̬			                            */
/************************************************************************/

class CollectResState : public UnitState
{
public:
	CollectResState(Unit* pOwner);
	CollectResState(const CollectResState& rhs):UnitState(rhs) {}
	virtual ~CollectResState() {}
public:
	virtual	void Enter();
	virtual void Update(float dt);
	virtual void Exit();
};

/************************************************************************/
/*							������Դ״̬			                            */
/************************************************************************/

class ReturnResState : public UnitState
{
public:
	ReturnResState(Unit* pOwner);
	ReturnResState(const ReturnResState& rhs):UnitState(rhs) {}
	virtual ~ReturnResState() {}
public:
	virtual	void Enter();
	virtual void Update(float dt);
	virtual void Exit();
};


#endif