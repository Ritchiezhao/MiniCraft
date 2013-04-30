/********************************************************************
	created:	4:3:2013   23:02
	filename: 	F:\MiniCraft\Editor\SceneEdit\Manipulator\ManipulatorEffect.h
	author:		maval
	
	purpose:	ͼ��Ч����ع���
*********************************************************************/

#ifndef ManipulatorEffect_h__
#define ManipulatorEffect_h__

#include "ManipulatorEventCallback.h"

namespace Kratos
{
	class EffectController;
	class ParticleEffect;
}

class ManipulatorEffect : public ManipulatorSceneEventCallback
{
public:
	ManipulatorEffect();
	~ManipulatorEffect();

	//////////////�¼��ص�
	virtual void	OnSceneClose();

public:
	void	OnFrameMove(float dt);	
	void	Serialize(rapidxml::xml_document<>* doc, rapidxml::xml_node<>* XMLNode);
	void	LoadEffect(rapidxml::xml_node<>* node);

	void	SetShadowEnable(bool bEnable);
	bool	GetShadowEnable() const;
	void	SetSSAOEnable(bool bEnable);
	bool	GetSSAOEnable() const;
	void	SetSharpenEnable(bool bEnable);
	bool	GetSharpenEnable() const;
	void	SetFXAAEnable(bool bEnable);
	bool	GetFXAAEnable() const;

	void	SetShadowParam(const std::string& name, const std::wstring& value);
	void	SetSsaoParam(const std::string& name, const std::wstring& value);
	const std::string& GetShadowParam(const std::string& name) const;
	const std::string& GetSsaoParam(const std::string& name) const;

	std::vector<std::wstring>	GetMeshAnimNames(const std::string& meshname) const;
	void						PlayAnimation(Ogre::Entity* ent, int animIndex, bool bPlayOrStop);
	const std::string			GetCurAnimationName();
	void						OnAnimSelectChange(const std::string& anim);
	void						OnAttachEffectSelChange(const std::string& effect);
	bool						GetIsPlayingAnim() const;
	std::vector<std::wstring>	GetLocatorNames() const;
	void						BindEntityToEffectTemplate(Ogre::Entity* ent);
	std::vector<std::wstring>	GetAttachEffectNames();
	int							GetAttachEffectType(const std::string& name);
	//����/ȥ��һ������Ч
	std::wstring				AddEffect(int type);
	void						RemoveEffect(const std::string& name);
	//��ȡPU��������ģ������
	std::vector<std::wstring>	GetParticleTmpNames() const;
	//����/��ȡ�ҽ���Ч����
	void						SetEffectParam(const std::string& param, const std::string& value);
	const std::string			GetEffectParam(const std::string& param);
	std::vector<std::wstring>	GetAttachEffectMeshNames();

private:
	Kratos::EffectController*	_GetEffectController(Ogre::Entity* ent);

private:
	typedef std::unordered_map<std::string, Kratos::EffectController*> EffectTemplate;
	EffectTemplate		m_effectTemplates;	//����ģ�͵Ĺҽ���Чģ��.�༭�������Ǳ༭
	bool				m_bIsPlayAnim;
	std::string			m_curAnim;
	std::string			m_curEffect;
};


#endif // ManipulatorEffect_h__







