/********************************************************************
	created:	20:1:2013   22:41
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\Faction.h
	author:		maval
	
	purpose:	Faction����һ�������Ӫ
*********************************************************************/

#ifndef Faction_h__
#define Faction_h__

#include "GameDefine.h"
#include "KratosPrerequisites.h"

class Building;

class Faction
{
public:
	Faction(eGameRace race);
	~Faction() {}

public:
	virtual void	Update(float dt) {}
	void			SetBase(Building* pBase) { m_base = pBase; }
	Building*		GetBase()	{ return m_base; }
	void			AddMineral(int num) { m_mineral +=num; }
	void			SetTeamColor(const COLOR& color) { m_teamColor = color; }
	const COLOR&	GetTeamColor() const { return m_teamColor; }
	void			SetEnemy(Faction* enemy);
	Faction*		GetEnemy() { return m_pEnemy; }
	void			OnUnitDeath() { --m_unitNum; assert(m_unitNum >= 0); }
	int				GetUnitNum() const { return m_unitNum; }

protected:
	eGameRace	m_race;
	int			m_mineral;		//��Ǯ��
	Building*	m_base;			//���Ի���
	COLOR		m_teamColor;	//������ɫ
	Faction*	m_pEnemy;		//�ж���Ӫ
	int			m_unitNum;		//��ǰ��λ����
};

#endif // Faction_h__