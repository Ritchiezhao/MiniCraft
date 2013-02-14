/********************************************************************
	created:	21:1:2013   0:51
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\Object\Unit.h
	author:		maval
	
	purpose:	��Ϸ��λ��
*********************************************************************/

#ifndef Unit_h__
#define Unit_h__


#include "SelectableObject.h"
#include "ScriptSystem.h"


struct lua_State;
class PathComponent;

class Unit : public SelectableObject
{
	DECL_PARAM_COMMAND(ClampPos)
	DECL_PARAM_COMMAND(UnitName)
	DECL_PARAM_COMMAND(NeedMove)
public:
	Unit();
	Unit(lua_State* L) {}
	~Unit();

	static const char className[];
	static Luna<Unit>::RegType methods[];

	const static STRING UNIT_TABLE_NAME;

public:
	virtual eObjectType GetType() const { return eObjectType_Unit; }
	virtual void	Update(float dt);
	virtual void	_OnCommandFinished(eCommandType cmd);

public:
	void			SetPathComponent(PathComponent* path)	{ m_pPath = path; }
	PathComponent*	GetPathComponent()	{ return m_pPath; }
	void			SetUnitName(const STRING& name);
	const STRING&	GetUnitName() const {return m_unitName; } 
	void			SetDestPos(const POS& destPos);
	const POS&		GetDestPos() const	{ return m_destPos; }
	void			PlayAnimation(eAnimation type, bool bLoop);
	void			StopAnimation();
	//���õ�λ����,�ڲ����Զ��гֵ�������
	void			SetClampPos(const POS& pos);
	const POS&		GetClampPos() const { return GetPosition(); }
	void			SetNeedMove(bool bNeedMove) { m_bPosChanged = bNeedMove; }
	bool			GetNeedMove() const { return m_bPosChanged; }

public:
	///lua��������
	int				PlayAnimation(lua_State* L);
	int				StopAnimation(lua_State* L);
	int				FindPath(lua_State* L);
	int				SetState(lua_State* L);
	int				SetDestPosition(lua_State* L);
	int				GetDestPosition(lua_State* L);
	int				UpdatePathFinding(lua_State* L);
	int				GetCurCommandType(lua_State* L);
	int				AttachRes(lua_State* L);
	int				DetachRes(lua_State* L);

private:
	PathComponent*			m_pPath;		//Ѱ·���
	STRING					m_unitName;		//��λ����,��:scv,marine...
	POS						m_destPos;
	bool					m_bPosChanged;	//�Ƿ���Ҫ����Ѱ·.���ݸñ�־λ�������ƶ�ʱ�Ƿ���Ҫ�Ƚ���ѡ��Ŀ��״̬
	Ogre::AnimationState*	m_pAnimState;	//��ǰ���Ŷ���
	
};


#endif	//Unit_h__