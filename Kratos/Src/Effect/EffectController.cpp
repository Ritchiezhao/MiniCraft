#include "EffectController.h"
#include "OgreManager.h"
#include "ParticleEffect.h"

namespace Kratos
{

	EffectController::EffectController( Ogre::Entity* parent )
	:m_parent(parent)
	,m_anim(nullptr)
	{

	}

	EffectController::~EffectController()
	{
		for(auto iter=m_effects.begin(); iter!=m_effects.end(); ++iter)
		{
			EffectSlots& slots = iter->second;
			for(size_t i=0; i<slots.size(); ++i)
			{
				slots[i]->Stop();
				delete slots[i];
			}
		}
		m_effects.clear();
	}

	ParticleEffect* EffectController::AddEffect( const STRING& animName)
	{
		ParticleEffect* newEffect = new ParticleEffect(m_parent);
		m_effects[animName].push_back(newEffect);
		return newEffect;
	}

	void EffectController::RemoveEffect( const STRING& name )
	{
		for (auto iter=m_effects.begin(); iter!=m_effects.end(); ++iter)
		{
			EffectSlots& slots = iter->second;
			for (auto itEffect=slots.begin(); itEffect!=slots.end(); ++itEffect)
			{
				ParticleEffect* effect = *itEffect;
				if (effect->GetName() == name)
				{
					effect->Destroy();
					delete effect;
					slots.erase(itEffect);

					return;
				}
			}
		}
		assert(0 && "There's no effect with this name!");
	}

	void EffectController::PlayAnimation( const STRING& animName, bool bLoop )
	{
		assert(m_parent->hasAnimationState(animName));

		//ֹͣ��ǰ����
		StopAnimation();

		//���Ŷ���
		m_anim = m_parent->getAnimationState(animName);
		m_anim->setEnabled(true);
		m_anim->setTimePosition(0);
		m_anim->setLoop(bLoop);

		//������Ч
		auto iter = m_effects.find(animName);
		if (iter != m_effects.end())
		{
			EffectSlots& slots = iter->second;
			for (auto itEffect=slots.begin(); itEffect!=slots.end(); ++itEffect)
			{
				ParticleEffect* effect = *itEffect;
				effect->Start();
			}
		}
	}

	void EffectController::StopAnimation()
	{
		if(m_anim)
		{
			//ֹͣ��Ч
			auto iter = m_effects.find(m_anim->getAnimationName());
			if (iter != m_effects.end())
			{
				EffectSlots& slots = iter->second;
				for (auto itEffect=slots.begin(); itEffect!=slots.end(); ++itEffect)
					(*itEffect)->Stop();
			}

			//ֹͣ����
			m_anim->setEnabled(false);
			m_anim = nullptr;
		}
	}

	void EffectController::Update( float dt )
	{
		if (m_anim)
		{
			//���¶���
			static float fLastTimePos = m_anim->getTimePosition();
			m_anim->addTime(dt);

			if(m_anim->hasEnded())
				m_anim = nullptr;

			bool bLooped = false;
			float fCurTimePos = m_anim->getTimePosition();
			if(fCurTimePos < fLastTimePos)
			{
				//hack a little..
				//˵�������Ѿ�ѭ����һ��
				assert(m_anim->getLoop());
				bLooped = true;
			}
			fLastTimePos = fCurTimePos;

			//������Ч
			auto iter = m_effects.find(m_anim->getAnimationName());
			if(iter != m_effects.end())
			{
				EffectSlots& slots = iter->second;
				for (auto itEffect=slots.begin(); itEffect!=slots.end(); ++itEffect)
				{
					ParticleEffect* effect = *itEffect;
					if(bLooped)
						effect->Start();
					else
						effect->Update(dt);
				}
			}
		}
	}

	ParticleEffect* EffectController::GetEffect( const STRING& name )
	{
		for (auto iter=m_effects.begin(); iter!=m_effects.end(); ++iter)
		{
			EffectSlots& slots = iter->second;
			for (auto itEffect=slots.begin(); itEffect!=slots.end(); ++itEffect)
			{
				ParticleEffect* effect = *itEffect;
				if (effect->GetName() == name)
					return effect;
			}
		}

		return nullptr;
	}

	void EffectController::_SetParent( Ogre::Entity* ent )
	{
		for(auto itSlot=m_effects.begin(); itSlot!=m_effects.end(); ++itSlot)
		{
			EffectSlots& slots = itSlot->second;
			for (auto itEffect=slots.begin(); itEffect!=slots.end(); ++itEffect)
				(*itEffect)->_SetParent(ent);
		}
		m_parent = ent; 
		m_anim = nullptr;
	}

}

