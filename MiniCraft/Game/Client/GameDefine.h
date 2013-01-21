#pragma once



typedef Ogre::Vector3		POS;
typedef Ogre::Quaternion	ORIENT;
typedef	Ogre::Vector3		SCALE;
typedef Ogre::ColourValue	COLOR;


const std::string	SCENE_MANAGER_NAME	=	"DefaultSceneMgr";
const float			SCENE_VERSION		=	0.1f;	//��ǰ.scene�汾��,ע����༭��ͬ��

//��Ϸ����:����,����,����
enum eGameRace
{
	eGameRace_Terrain,
	eGameRace_Protoss,
	eGameRace_Zerg
};

//��������
enum eObjectType
{
	eObjectType_Faction,
	eObjectType_Unit,
	eObjectType_Building,
	eObjectType_Resource
};

