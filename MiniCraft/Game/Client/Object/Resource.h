/********************************************************************
	created:	24:1:2013   21:54
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\Object\Resource.h
	author:		maval
	
	purpose:	�ɲɼ���Դ��
*********************************************************************/

#ifndef Resource_h__
#define Resource_h__


#include "SelectableObject.h"


class Resource : public SelectableObject
{
public:
	Resource();
	~Resource() {}

public:
	virtual eObjectType GetType() const { return eObjectType_Resource; }
	virtual void	Update(float dt) {}

	void			DecreaseRes(int num) { m_resLeft -= num; }
	//����Դ���ɼ�һ�ε�����
	int				GetGatherOnceNum()	{ return 5; }

private:
	int			m_resLeft;		//ʣ����Դ��
};


#endif // Resource_h_