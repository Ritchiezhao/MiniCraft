#include "stdafx.h"
#include "ActionNone.h"
#include "Manipulator/ManipulatorScene.h"

void ActionNone::Enter()
{
	//���ѡ������
	ManipulatorSystem.GetObject().ClearSelection();
}
