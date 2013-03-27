/********************************************************************
	created:	26:3:2013   22:34
	filename	BlackBoard.h
	author:		maval

	purpose:	һ����Ϊ���Ĳ����ֵ�.��������
*********************************************************************/

#ifndef BlackBoard_h__
#define BlackBoard_h__

#include "KratosPrerequisites.h"
#include <OgreCommon.h>

class aiBlackBoard
{
public:
	aiBlackBoard();
	~aiBlackBoard() {}

public:
	//�����²������ֵ���
	void		DefineParam(const STRING& name, const STRING& value);
	void		Clone(aiBlackBoard& toClone);

private:
	aiBlackBoard(const aiBlackBoard&);
	aiBlackBoard& operator= (const aiBlackBoard&);

	Ogre::NameValuePairList		m_params;
};

#endif // BlackBoard_h__