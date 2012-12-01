#ifndef UNIT_STATE_H
#define UNIT_STATE_H



class Unit;

enum eUnitState
{
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
	virtual ~UnitState() {}
public:
	virtual	void Enter() = 0;
	virtual void Update(float dt) = 0;
	virtual void Exit() = 0;
public:
	eUnitState	GetType() const { return m_type; }

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
	virtual ~MoveState() {}
public:
	virtual	void Enter();
	virtual void Update(float dt);
	virtual void Exit();

private:
	Ogre::Vector3			m_destPos;
	Ogre::AnimationState*	m_pRunBaseAnim;
	Ogre::AnimationState*	m_pRunTopAnim;
};

/************************************************************************/
/*							����״̬			                            */
/************************************************************************/

class AttackState : public UnitState
{
public:
	AttackState(Unit* pOwner):UnitState(pOwner) { m_type = eUnitState_Attack; }
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
	CollectResState(Unit* pOwner):UnitState(pOwner) { m_type = eUnitState_Collect; }
	virtual ~CollectResState() {}
public:
	virtual	void Enter() {}
	virtual void Update(float dt) {}
	virtual void Exit() {}
};

/************************************************************************/
/*							������Դ״̬			                            */
/************************************************************************/

class ReturnResState : public UnitState
{
public:
	ReturnResState(Unit* pOwner):UnitState(pOwner) { m_type = eUnitState_Return; }
	virtual ~ReturnResState() {}
public:
	virtual	void Enter() {}
	virtual void Update(float dt) {}
	virtual void Exit() {}
};


#endif