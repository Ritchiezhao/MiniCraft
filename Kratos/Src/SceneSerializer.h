/********************************************************************
	created:	17:2:2013   1:23
	filename: 	F:\MiniCraft\Kratos\Src\SceneSerializer.h
	author:		maval
	
	purpose:	��������������.ͨ��ģ�����ģʽ�ÿͻ��˺ͱ༭��
				ͨ���̳�����ʵ��ĳЩ�������ݵļ����ػ���Ϊ.
*********************************************************************/

#ifndef SceneSerializer_h__
#define SceneSerializer_h__

#include <OgrePrerequisites.h>
#include <rapidxml.hpp>       
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>

class Scene;

class SceneSerializer
{
public:
	SceneSerializer();
	virtual ~SceneSerializer() {}

public:
	void			LoadScene(const std::string& sceneName, const std::string& sceneGroup);
	void			SaveScene();
	void			SetSerializerOwner(Scene* pOwner) { m_pOwner = pOwner; }
	void			SetSerializerSceneManager(Ogre::SceneManager* pSceneMgr) { m_pSerializerMgr = pSceneMgr; }

protected:
	virtual	void	_LoadTerrain(rapidxml::xml_node<>* node);
	virtual void	_LoadObjects(rapidxml::xml_node<>* node) = 0;

private:
	Scene*				m_pOwner;
	Ogre::SceneManager* m_pSerializerMgr;
	std::string			m_sceneGroup;
};

#endif // SceneSerializer_h__