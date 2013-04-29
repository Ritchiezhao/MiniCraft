/********************************************************************
	created:	7:2:2013   12:27
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\GameDataDef.h
	author:		maval
	
	purpose:	��Ϸ��������.
				��������������������,�鿴�������stringInterface�����ֵ�
*********************************************************************/
#ifndef GameDataDef_h__
#define GameDataDef_h__

#include "Singleton.h"
#include "GameDefine.h"
#include "KratosPrerequisites.h"


//���������Ա�־
enum eBuildingFlag
{
	eBuildingFlag_ResDropOff = 1		//���Խ�����Դ(������)
};

//����Ӳ���
const	STRING		FORCE_EXECUTE					=	"ForceExecute";
const	STRING		TARGETING_AND_FORCE_EXECUTE		=	"TargetingAndForceExecute";

/////////////////////////////////////////////////////////////////////////
////	Building�������,��RaceBuildingData.xml
struct SBuildingData
{
	Ogre::NameValuePairList params;
	std::vector<STRING>	m_vecAbilities;	//����
};

/////////////////////////////////////////////////////////////////////////
////	Ability�������,��AbilityData.xml
struct SAbilityData
{
	STRING			m_iconName;			//ͼ���ļ���
	eCommandType	m_type;				//��������
	STRING			m_param;			//���Ӳ���,����
};

/////////////////////////////////////////////////////////////////////////
////	���ӵ���Ч���,��Effect.xml
struct SEffectData
{
	Ogre::NameValuePairList params;															
};

/////////////////////////////////////////////////////////////////////////
////	��λս���������,��BattleData.xml
struct SBattleData
{
	Ogre::NameValuePairList params;															
};

/////////////////////////////////////////////////////////////////////////
////	Unit���,��UnitTable.xml
struct SUnitData
{
	Ogre::NameValuePairList params;
	std::vector<STRING>		m_vecAbilities;			//����
	typedef HashMap<eAnimation, STRING>	AnimTable;
	AnimTable				m_anims;				//�õ�λ���ж�������ʵ����.��Ϊ��ģ�͵ĵ����������ֲ�һ��һ��
	typedef HashMap<STRING, std::vector<SEffectData>> EffectDataMap;
	EffectDataMap			m_effects;				//�ҽ���Ч
	SBattleData				m_battleInfo;			//ս������
};

//��ƻ���ֵ���������ָ��,����Ϊһ����ʼ�����,�ڳ����˳�ǰ,�Ͳ���ȥ�ı���,
//����map��ʵ��,���ڲ��಻����иĶ�.����Ч�����ⲻ��.
typedef HashMap<STRING, SBuildingData> BuildingNameIndexTable;
typedef HashMap<STRING, SAbilityData> AbilityNameIdxTable;
typedef HashMap<STRING, SUnitData>	UnitTable;


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

///���Գ־û�
void	LoadStringInterface(Ogre::NameValuePairList& params, rapidxml::xml_node<>* node);
void	SaveStringInterface(Ogre::StringInterface* si, Ogre::NameValuePairList& params);

#endif // GameDataDef_h__