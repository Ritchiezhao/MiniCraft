/********************************************************************
	created:	29:1:2013   20:55
	filename: 	F:\MiniCraft\Editor\SceneEdit\Manipulator\ManipulatorGameData.h
	author:		maval
	
	purpose:	��Ϸ�ͻ���������ر༭����.ģ��SC2,������Ϸ�����ļ���ͨ��XML���.
*********************************************************************/

#ifndef ManipulatorGameData_h__
#define ManipulatorGameData_h__

#include "../../MiniCraft/Game/Client/GameDataDef.h"

class GameDataDefManager;

class ManipulatorGameData
{
public:
	ManipulatorGameData();
	~ManipulatorGameData() {}

public:
	//�������б༭��Ҫ�õ�����ϷXML�����ļ�
	void						LoadAllXml();
	//��������XML
	void						SaveAllXml();
	//��ȡ����Ľ��������б�
	std::vector<std::wstring>	GetRaceBuildingNames(eGameRace race) const;
	//��ȡbuilding����
	const SBuildingData*		GetBuildingData(const std::wstring& name);
	//��ȡ����ability�����б�
	std::vector<std::wstring>	GetAbilityNames() const;
	//��ȡability����
	const SAbilityData*			GetAbilityData(const std::wstring& name);
	//���ý���������
	void						SetBuildingAbility(const std::wstring& buildingName, int slotIndex, const std::wstring& abilName);
	//��ȡ��λ����.ע�������mesh����
	SUnitData*					GetUnitData(const std::string& meshname);

private:
	GameDataDefManager*			m_dataMgr;
};


#endif // ManipulatorGameData_h__







