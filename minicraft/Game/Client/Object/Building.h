/********************************************************************
	created:	24:1:2013   0:34
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\Object\Building.h
	author:		maval
	
	purpose:	������
*********************************************************************/

#ifndef Building_h__
#define Building_h__

#include "SelectableObject.h"
#include "Command.h"

struct SBuildingData;

class Building : public SelectableObject
{
	DECL_PARAM_COMMAND(Name)
	DECL_PARAM_COMMAND(RallyPoint)
	DECL_PARAM_COMMAND(Race)
	DECL_PARAM_COMMAND(Icon)
	DECL_PARAM_COMMAND(Flags)
public:
	Building();
	~Building() {}

public:
	virtual eObjectType GetType() const { return eObjectType_Building; }
	virtual void	Update(float dt);
	virtual void	_OnCommandFinished(eCommandType cmd);

public:
	void			Init(const POS& pos, const ORIENT& orient, const SCALE& scale);
	void			SetName(const STRING& name);
	const STRING&	GetName() const				{return m_buildingName; } 
	float			GetCurProgress() const		{ return m_fCurProgress; }
	void			SetRallyPoint(const POS& pos) { assert(0); /*shouldn't be called!*/ }
	const POS&		GetRallyPoint() const;
	void			SetRace(int race)			{ assert(0); /*shouldn't be called!*/ }
	int				GetRace() const;
	void			SetIcon(const STRING& icon)	{ assert(0); /*shouldn't be called!*/ }
	const STRING&	GetIcon() const;
	void			SetFlags(int flags)			{ assert(0); /*shouldn't be called!*/ }
	int				GetFlags() const;

private:
	STRING			m_buildingName;		//��λ����,��:barrack...
	float			m_fCurProgress;		//����ǰ��������״̬,��������ʱ��
	POS				m_rallyPoint;		//�����
	SBuildingData*	m_param;
};


#endif // Building_h__