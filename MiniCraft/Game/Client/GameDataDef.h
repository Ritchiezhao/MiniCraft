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

//���������Ա�־
enum eBuildingFlag
{
	eBuildingFlag_ResDropOff = 1		//���Խ�����Դ(������)
};

//Building�������,��RaceBuildingData.xml
struct SBuildingData
{
	eGameRace		m_race;				//��������
	STRING			m_iconName;			//�༭���õ���ͼ���ļ���
	STRING			m_meshname;			//ģ���ļ���
	POS				m_rallyPoint;		//����Ĭ�ϼ����
	std::vector<STRING>	m_vecAbilities;	//����
	int				m_flags;			//���Լ�
};

//Ability�������,��AbilityData.xml
struct SAbilityData
{
	STRING			m_iconName;			//ͼ���ļ���
	eCommandType	m_type;				//��������
	STRING			m_param;			//���Ӳ���,����
};

//����Ӳ���
const	STRING		FORCE_EXECUTE					=	"ForceExecute";
const	STRING		TARGETING_AND_FORCE_EXECUTE		=	"TargetingAndForceExecute";

//��λ�Ŀ��ö�������
enum eAnimation
{
	eAnimation_Idle,					//���ж���
	eAnimation_Move	,					//�ƶ�����
	eAnimation_Gather					//�ɼ�����
};

//Unit���,��UnitTable.xml
struct SUnitData
{
	float		m_fTimeCost;			//��������ʱ��
	STRING		m_meshname;				//ģ���ļ���
	typedef std::unordered_map<eAnimation, STRING>	AnimTable;
	AnimTable	m_anims;				//�õ�λ���ж�������ʵ����.��Ϊ��ģ�͵ĵ����������ֲ�һ��һ��
	std::vector<STRING>	m_vecAbilities;	//����
	eGameRace	m_race;					//����
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