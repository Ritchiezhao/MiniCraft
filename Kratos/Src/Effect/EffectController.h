/********************************************************************
	created:	11:3:2013   13:44
	author:		maval
	
	purpose:	���ӵ���Ч������.ÿ����������ģ�Ͷ���ӵ��һ��
*********************************************************************/

#ifndef EffectController_h__
#define EffectController_h__

#include "KratosPrerequisites.h"

namespace Kratos
{
	class ParticleEffect;

	class EffectController
	{
	public:
		EffectController(Ogre::Entity* parent);
		~EffectController();

		typedef std::map<STRING, ParticleEffect*>		EffectSlots;		//һ�����������йҽӵ��Ӧ����Ч
		typedef std::unordered_map<STRING, EffectSlots>	EffectContainer;	//���ж�����Ӧ����Ч

	public:
		//����һ���ҽ���Ч
		void			AddEffect(const STRING& animName, const STRING& locator, ParticleEffect* pEffect);
		//ɾ���ҽ���Ч
		void			RemoveEffect(const STRING& animName, const STRING& locator);
		//��ȡģ�Ͷ�Ӧ��Ч
		ParticleEffect*	GetEffect(const STRING& animName, const STRING& locator);
		//���Ŷ���,�Զ�������Ч�Ĳ���
		void			PlayAnimation(const STRING& animName, bool bLoop);
		void			StopAnimation();
		//���¸ÿ�����
		void			Update(float dt);
		//�༭����
		const EffectContainer&	_GetEffects() const { return m_effects; }

	private:
		Ogre::Entity*			m_parent;
		EffectContainer			m_effects;
		Ogre::AnimationState*	m_anim;			//��ǰ���Ŷ���
	};

}

#endif // EffectController_h__