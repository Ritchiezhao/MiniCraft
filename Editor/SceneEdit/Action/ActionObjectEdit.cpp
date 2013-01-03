#include "stdafx.h"
#include "ActionObjectEdit.h"
#include "EditorDefine.h"
#include "Manipulator/ManipulatorScene.h"

ActionObjectEdit::ActionObjectEdit()
:m_bCanMove(false)
,m_bLBDown(false)
,m_curActiveAxis(eAxis_None)
{

}
void ActionObjectEdit::Enter()
{
	ManipulatorObject& manObject = ManipulatorSystem.GetObject();
	ManipulatorObject::eEditMode mode = manObject.GetCurEditMode();

	//��ʾgizmo
	manObject.ShowEntityGizmo(manObject.GetSelection(), true, mode);
	//��ʾ��Χ��
	manObject.ShowEntityGizmo(manObject.GetSelection(), true, ManipulatorObject::eEditMode_Select);
}

void ActionObjectEdit::Leave()
{
	ManipulatorObject& manObject = ManipulatorSystem.GetObject();
	//����������
	manObject.ShowEntityGizmo(manObject.GetSelection(), false, ManipulatorObject::eEditMode_Move);
	//���ذ�Χ��
	manObject.ShowEntityGizmo(manObject.GetSelection(), false, ManipulatorObject::eEditMode_Select);
	manObject.SetCurEditMode(ManipulatorObject::eEditMode_None);
}

void ActionObjectEdit::OnMouseLButtonDown( const SActionParam& param )
{
	m_bLBDown = true;
	if (m_bCanMove)
	{
		assert(m_curActiveAxis != eAxis_None);
		const Ogre::Ray ray = ManipulatorSystem.m_pMainCamera->getCameraToViewportRay(param.m_ptRelative.x, param.m_ptRelative.y);
		m_vecAdjust = _ComputeTranslateVector(ray, m_curActiveAxis);
	}
}

void ActionObjectEdit::OnMouseLButtonUp( const SActionParam& param )
{
	m_bLBDown = false;
}

void ActionObjectEdit::OnMouseMove( const SActionParam& param )
{
	ManipulatorObject& manObject = ManipulatorSystem.GetObject();
	const Ogre::Ray ray = ManipulatorSystem.m_pMainCamera->getCameraToViewportRay(param.m_ptRelative.x, param.m_ptRelative.y);

	if (m_bCanMove && m_bLBDown)
	{
		//����ƽ�Ƽ���
		Ogre::Entity* pSelEnt = ManipulatorSystem.GetObject().GetSelection();
		Ogre::Vector3 oldPos = pSelEnt->getParentSceneNode()->_getDerivedPosition();
		Ogre::Vector3 newPos = _ComputeTranslateVector(ray, m_curActiveAxis) - m_vecAdjust + oldPos;
		ManipulatorSystem.GetObject().GetSelection()->getParentSceneNode()->_setDerivedPosition(newPos);
	}
	else
	{
		Ogre::MovableObject* pMovable = manObject.DoRaySceneQuery(ray, 
			eQueryMask_GizmoAxisX | eQueryMask_GizmoAxisY | eQueryMask_GizmoAxisZ);

		if (pMovable)
		{
			//����Ƶ���ĳ������
			if (m_curActiveAxis != eAxis_None)
			{
				manObject.HighlightGizmoAxis(false, m_curActiveAxis);
				m_curActiveAxis = eAxis_None;
			}

			int mask = pMovable->getQueryFlags();
			if(mask == eQueryMask_GizmoAxisX)		m_curActiveAxis = eAxis_X;
			else if(mask == eQueryMask_GizmoAxisY)	m_curActiveAxis = eAxis_Y;
			else if(mask == eQueryMask_GizmoAxisZ)	m_curActiveAxis = eAxis_Z;

			manObject.HighlightGizmoAxis(true, m_curActiveAxis);
			m_bCanMove = true;
		}
		else if(m_curActiveAxis != eAxis_None)
		{
			//��겻���κ�����
			manObject.HighlightGizmoAxis(false, m_curActiveAxis);
			m_bCanMove = false;
			m_curActiveAxis = eAxis_None;
		}
	}
}

const Ogre::Vector3 ActionObjectEdit::_ComputeTranslateVector(const Ogre::Ray& ray, eAxis axis)
{
	using namespace Ogre;

	Entity* pSelEnt = ManipulatorSystem.GetObject().GetSelection();
	Quaternion qOrient = pSelEnt->getParentSceneNode()->_getDerivedOrientation();
	Vector3 oldPos = pSelEnt->getParentSceneNode()->_getDerivedPosition();

	Plane planeX(qOrient.xAxis(), oldPos);
	Plane planeY(qOrient.yAxis(), oldPos);
	Plane planeZ(qOrient.zAxis(), oldPos);

	float vX = planeX.projectVector(ray.getDirection()).length();
	float vY = planeY.projectVector(ray.getDirection()).length();
	float vZ = planeZ.projectVector(ray.getDirection()).length();

	Vector3 vAxis = Vector3::ZERO;
	switch (axis)
	{
	case eAxis_X: { vX = 10000.0f; vAxis = qOrient.xAxis(); } break;
	case eAxis_Y: { vY = 10000.0f; vAxis = qOrient.yAxis(); } break;
	case eAxis_Z: { vZ = 10000.0f; vAxis = qOrient.zAxis(); } break;
	}

	Plane planeToUse;
	if (vX < vY && vX < vZ)
	{
		planeToUse = planeX;
	}
	else
	{
		if (vY < vX && vY < vZ )
			planeToUse = planeY;
		else
			planeToUse = planeZ;
	}

	std::pair<bool,Ogre::Real> result;
	result = ray.intersects(planeToUse);
	if (result.first)
	{
		Vector3 Proj = ray.getPoint(result.second) - oldPos;
		Vector3 deltaPos = vAxis.dotProduct(Proj) * vAxis;

		return deltaPos;
	}
	
	return Vector3::ZERO;
}




