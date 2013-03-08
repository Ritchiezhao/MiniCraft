/********************************************************************
	created:	7:3:2013   21:04
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\UI\PortraitPanel.h
	author:		maval
	
	purpose:	3DФ�����UI���
*********************************************************************/

#ifndef PortraitPanel_h__
#define PortraitPanel_h__

class SelectableObject;

class UiPortraitPanel
{
public:
	UiPortraitPanel();
	~UiPortraitPanel() {}

public:
	void	Init();
	void	Update();
	void	Destroy();
	void	SetActiveObject(SelectableObject* pObj);

private:
	SelectableObject*		m_pActiveObject;
	CEGUI::Window*			m_pWnd;
	Ogre::TexturePtr		m_RT;
	CEGUI::Imageset*		m_image;
	Ogre::SceneManager*		m_pSceneMgr;		//��ȾФ��ר��
	Ogre::Light*			m_pLight;			//����
};


#endif // PortraitPanel_h__