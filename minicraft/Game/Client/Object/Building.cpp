#include "stdafx.h"
#include "Building.h"
#include "World.h"


const STRING Building::sNamePrefix = "EntBuilding";

void Building::OnSelected( bool bSelected )
{
	//�����������
	if (bSelected)
	{
		const auto& selObjs = World::GetSingleton().GetSelectedObjects();
		//TODO: ��ѡ״̬���������Ӧ������?
		if(selObjs.size() > 1)
			return;


	}
	else
	{

	}
}
