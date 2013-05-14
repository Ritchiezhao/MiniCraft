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

//��Ⱦ���Ϳ���
enum eRenderType
{
	eRenderType_Default		=	0xffffffff,
	eRenderType_Terrain		=	1<<0,
	eRenderType_Resource	=	1<<1,
	eRenderType_Unit		=	1<<2,
	eRenderType_Building	=	1<<3,
	eRenderType_UI			=	1<<4
};

//������ѯ����
enum eQueryType
{
	eQueryType_All				=	0xffffffff,
	eQueryType_Default			=	1<<0,
	eQueryType_Terrain			=	1<<1,
	eQueryType_Unit				=	1<<2,
	eQueryType_Resource			=	1<<3,
	eQueryType_Building			=	1<<4,
};
#define QueryTypeSelectableObject (eQueryType_Unit | eQueryType_Resource | eQueryType_Building)

//����
enum eCommandType
{
	eCommandType_Produce,		//����
	eCommandType_Move,			//�ƶ�
	eCommandType_Stop,			//ֹͣ
	eCommandType_Gather,		//�ɼ�
	eCommandType_Attack			//����
};

//��λ�Ŀ��ö�������
enum eAnimation
{
	eAnimation_Idle,					//����
	eAnimation_Move	,					//�ƶ�
	eAnimation_Gather,					//�ɼ�
	eAnimation_Attack,					//����
	eAnimation_Death					//����
};


