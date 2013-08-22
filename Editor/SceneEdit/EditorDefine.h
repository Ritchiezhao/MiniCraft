/********************************************************************
	created:	20:12:2012   1:02
	filename: 	F:\MiniCraft\Editor\SceneEdit\EditorDefine.h
	author:		maval
	
	purpose:	��������
*********************************************************************/

#ifndef EditorDefine_h__
#define EditorDefine_h__


const	int		EDITOR_CLIENT_W			=	1024;
const	int		EDITOR_CLIENT_H			=	768;
const	int		FPS					=	100;
const	float	TIME_PER_FRAME		=	1.0f / FPS;
const	int		MESH_ICON_SIZE		=	64;
const	int		RES_SELECTOR_COLUMN_WIDTH	=	80;

//������ѯ����
enum eQueryMask
{
	eQueryMask_Default	=	0,
	eQueryMask_Entity = 1 << 0
};

//���������
enum eCameraType
{
	eCameraType_RTS,
	eCameraType_ModelViewer
};


#endif // EditorDefine_h__