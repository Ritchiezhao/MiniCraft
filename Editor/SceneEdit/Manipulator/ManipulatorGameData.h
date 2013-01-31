/********************************************************************
	created:	29:1:2013   20:55
	filename: 	F:\MiniCraft\Editor\SceneEdit\Manipulator\ManipulatorGameData.h
	author:		maval
	
	purpose:	��Ϸ�ͻ���������ر༭����.ģ��SC2,������Ϸ�����ļ���ͨ��XML���.
*********************************************************************/

#ifndef ManipulatorGameData_h__
#define ManipulatorGameData_h__

#define MAX_ABILITY_SLOT	15

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
	std::wstring	m_iconName;			//�༭���õ���ͼ���ļ���
	std::string		m_meshname;			//ģ���ļ���
	std::vector<std::wstring>	m_vecAbilities;	//����������
};

//Ability�������,��AbilityData.xml
struct SAbilityData
{
	std::wstring m_iconName;	//ͼ���ļ���
};

class ManipulatorGameData
{
public:
	ManipulatorGameData() {}
	~ManipulatorGameData() {}

public:
	//�������б༭��Ҫ�õ�����ϷXML�����ļ�
	void						LoadAllXml();
	//��������XML
	void						SaveAllXml();
	//��ȡ����Ľ��������б�
	std::vector<std::wstring>	GetRaceBuildingNames(eGameRace race) const;
	//��ȡbuilding����
	const SBuildingData*		GetBuildingData(eGameRace race, const std::wstring& name);
	//��ȡ����ability�����б�
	std::vector<std::wstring>	GetAbilityNames() const;
	//��ȡability����
	const SAbilityData*			GetAbilityData(const std::wstring& name);
	//���ý���������
	void						SetBuildingAbility(eGameRace race, const std::wstring& buildingName, 
		int slotIndex, const std::wstring& abilName);

private:
	//��ƻ���ֵ���������ָ��,����Ϊһ����ʼ�����,�ڳ����˳�ǰ,�Ͳ���ȥ�ı���,
	//����map��ʵ��,���ڲ��಻����иĶ�.����Ч�����ⲻ��.
	typedef std::unordered_map<std::wstring, SBuildingData> BuildingNameIndexTable;
	typedef std::unordered_map<eGameRace, BuildingNameIndexTable> RaceBuildingTable;
	RaceBuildingTable	m_buildingData;

	typedef std::unordered_map<std::wstring, SAbilityData> AbilityNameIdxTable;
	AbilityNameIdxTable	m_abilityData;
};


#endif // ManipulatorGameData_h__







