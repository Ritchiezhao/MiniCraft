/********************************************************************
	created:	30:12:2012   9:57
	filename: 	F:\MiniCraft\Editor\SceneEdit\Manipulator\ManipulatorNavMesh.h
	author:		maval
	
	purpose:	Recast�⵼���������
*********************************************************************/

#ifndef ManipulatorNavMesh_h__
#define ManipulatorNavMesh_h__

#include "ManipulatorEventCallback.h"

class OgreRecast;
class OgreDetourTileCache;
class InputGeom;

class ManipulatorNavMesh : public ManipulatorSceneEventCallback
{
public:
	ManipulatorNavMesh();
	~ManipulatorNavMesh();

public:
	////////�¼��ص�
	virtual	void	OnSceneNew();
	virtual	void	OnSceneOpen();
	virtual void	OnSceneClose();

public:
	void		Generate();				//���ɵ�������
	void		Reset();
	void		SaveObj();				//����obj�ļ�(�����������񼸺�����)
	void		SaveNavMesh();			//����������������
	void		ShowNavMesh(bool bShow);//��ʾ��������
	bool		GetIsShowNavMesh() const { return m_bShowNavMesh; }
	bool		HasGenerate() const { return m_bHasGenerate; }
	void		OnGizmoNodeReset() {}

private:
	OgreRecast*				m_pRecast;
	InputGeom*				m_pInputGeom;
	OgreDetourTileCache*	m_pDetourTileCache;
	bool					m_bShowNavMesh;
	bool					m_bHasGenerate;
	Ogre::SceneNode*		m_debugRenderNode;
};


#endif // ManipulatorNavMesh_h__







