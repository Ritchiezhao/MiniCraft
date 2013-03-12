#pragma once

const		int				MAX_ABILITY_SLOT	=	15;		//������弼�ܲ۸���
const		int				MAX_COMMAND_QUEUE_LEN	=	1;	//���������󳤶�

//��Ϸ����:����,����,����
enum eGameRace
{
	eGameRace_Terran,
	//eGameRace_Protoss,
	eGameRace_Zerg,
	eGameRace_Count
};

//��������
enum eObjectType
{
	eObjectType_Faction,
	eObjectType_Unit,
	eObjectType_Building,
	eObjectType_Resource
};

//������ѯ����
enum eQueryType
{
	eQueryType_Default	=	1<<0,
	eQueryType_WorldGeometry	=	1<<1,
	eQueryType_SelectableObject	=	1<<2
};

//����
enum eCommandType
{
	eCommandType_Produce,		//��������
	eCommandType_Move,			//�ƶ�����
	eCommandType_Stop,			//ֹͣ����
	eCommandType_Gather			//�ɼ�����
};

