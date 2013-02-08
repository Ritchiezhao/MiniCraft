/********************************************************************
	created:	7:2:2013   12:27
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\GameDataDef.h
	author:		maval
	
	purpose:	��Ϸ�߼����ݽṹ����͹�����
*********************************************************************/
#ifndef GameDataDef_h__
#define GameDataDef_h__

#include "Singleton.h"

//��Ϸ����:����,����,����
enum eGameRace
{
	eGameRace_Terran,
	//eGameRace_Protoss,
	eGameRace_Zerg,
	eGameRace_Count
};

//Building�������,��RaceBuildingData.xml
struct SBuildingData
{
	eGameRace		m_race;				//��������
	std::string		m_iconName;			//�༭���õ���ͼ���ļ���
	std::string		m_meshname;			//ģ���ļ���
	std::vector<std::string>	m_vecAbilities;	//����������
};

#define MAX_ABILITY_SLOT	15

//Ability�������,��AbilityData.xml
struct SAbilityData
{
	std::string m_iconName;	//ͼ���ļ���
};

//��ƻ���ֵ���������ָ��,����Ϊһ����ʼ�����,�ڳ����˳�ǰ,�Ͳ���ȥ�ı���,
//����map��ʵ��,���ڲ��಻����иĶ�.����Ч�����ⲻ��.
typedef std::unordered_map<std::string, SBuildingData> BuildingNameIndexTable;
typedef std::unordered_map<std::string, SAbilityData> AbilityNameIdxTable;


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
};

#endif // GameDataDef_h__