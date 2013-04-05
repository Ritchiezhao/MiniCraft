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
struct SUnitData;

class Unit : public SelectableObject
{
	DECL_PARAM_COMMAND(Name)
	DECL_PARAM_COMMAND(Race)
	DECL_PARAM_COMMAND(PortraitName)
	DECL_PARAM_COMMAND(ProduceTime)
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
	void			Init();
	void			SetName(const STRING& name);
	const STRING&	GetName() const		{ return m_unitName; }
	void			SetRace(int race)	{ assert(0); /*shouldn't be called!*/ }
	int				GetRace() const;
	void			SetPortraitName(const STRING& name)	{ assert(0); /*shouldn't be called!*/ }
	const STRING&	GetPortraitName() const;
	void			SetProduceTime(float time)	{ assert(0); /*shouldn't be called!*/ }
	float			GetProduceTime() const;

	SUnitData*		GetUnitData() { return m_data; }
	Ogre::Entity*	GetPortrait(Ogre::SceneManager* sm, Ogre::Light* light);
	void			StopAction();
	void			SetStopTime(float fTime) { m_fStopTime = fTime; }
	float			GetStopTime() const	{ return m_fStopTime; }

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

protected:
	virtual void	_OnSelected(bool bSelected);

private:
	SUnitData*				m_data;
	STRING					m_unitName;		//��λ����,��:scv,marine...
	float					m_fStopTime;	//�Ѿ�����ֹͣ״̬���
	static std::unordered_map<STRING, Ogre::Entity*>			m_portraitCache;		//cacheÿ�ֵ�λ��3DФ��ģ��
	static std::unordered_map<STRING, Ogre::AnimationState*>	m_portraitAnimCache;	//cacheÿ�ֵ�λ��3DФ�񶯻�
	Ogre::BillboardSet*		m_pHealthBar;
};


#endif	//Unit_h__