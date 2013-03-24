/********************************************************************
	created:	21:3:2013   23:26
	filename	DeferredLightEffect.h
	author:		maval

	purpose:	�ҽ���ģ���ϵĶ�̬��Դ.
*********************************************************************/

#ifndef DeferredLightEffect_h__
#define DeferredLightEffect_h__

#include "EffectBase.h"
#include <OgreVector3.h>

namespace Kratos
{
	enum eDLightType
	{
		eDLightType_Point,
		eDLightType_Spot,
		eDLightType_None
	};

	class DLight;

	class DLightEffect : public AttachEffectBase
	{
		DECL_PARAM_COMMAND(LightType)
		DECL_PARAM_COMMAND(LightRadius)
		DECL_PARAM_COMMAND(PointAttenParam)
	public:
		DLightEffect(Ogre::Entity* parent);
		~DLightEffect();

	public:
		virtual void	Start();
		virtual void	Stop();
		virtual void	Pause();
		virtual void	Resume();
		virtual void	Update(float dt);
		virtual void	Destroy();

		void			SetLightType(int type);
		int				GetLightType() const { return m_dlType; }
		void			SetLightRadius(float fRadius);
		float			GetLightRadius() const { return m_fRadius; }
		void			SetPointAttenParam(const FLOAT3& param);
		const FLOAT3&	GetPointAttenParam() const { return m_dlPointParam; }

	private:
		eDLightType		m_dlType;
		DLight*			m_light;
		///���
		float			m_fRadius;			//�⾶
		FLOAT3			m_dlPointParam;		//˥������
	};
}

#endif // DeferredLightEffect_h__