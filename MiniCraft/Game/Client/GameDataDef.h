/********************************************************************
	created:	7:2:2013   12:27
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\GameDataDef.h
	author:		maval
	
	purpose:	��Ϸ�߼����ݽṹ����͹�����
*********************************************************************/
#ifndef GameDataDef_h__
#define GameDataDef_h__

#include "Singleton.h"
#include "GameDefine.h"
#include "Command.h"

//Building�������,��RaceBuildingData.xml
struct SBuildingData
{
	eGameRace		m_race;				//��������
	STRING			m_iconName;			//�༭���õ���ͼ���ļ���
	STRING			m_meshname;			//ģ���ļ���
	std::vector<STRING>	m_vecAbilities;	//����������
};

//Ability�������,��AbilityData.xml
struct SAbilityData
{
	STRING			m_iconName;			//ͼ���ļ���
	eCommandType	m_type;				//��������
	STRING			m_param;			//���Ӳ���
};

//Unit���,��UnitTable.xml
struct SUnitData
{
	float		m_fTimeCost;			//��������ʱ��
	STRING		m_meshname;				//ģ���ļ���
};

//��ƻ���ֵ���������ָ��,����Ϊһ����ʼ�����,�ڳ����˳�ǰ,�Ͳ���ȥ�ı���,
//����map��ʵ��,���ڲ��಻����иĶ�.����Ч�����ⲻ��.
typedef std::unordered_map<STRING, SBuildingData> BuildingNameIndexTable;
typedef std::unordered_map<STRING, SAbilityData> AbilityNameIdxTable;
typedef std::unordered_map<STRING, SUnitData>	UnitTable;


class GameDataDefManager : public CSingleton<GameDataDefManager>
{
	GameDataDefManager() {}
	~GameDataDefManager() {}
	DECLEAR_SINGLETON(GameDataDefManager)

public:
	void	LoadAllData();
	void	SaveAllData();

public:
	BuildingNameIndexTable	m_buildingData;
	AbilityNameIdxTable		m_abilityData;
	UnitTable				m_unitData;
};

#endif // GameDataDef_h__