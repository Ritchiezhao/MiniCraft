#include "stdafx.h"
#include "ManipulatorEffect.h"
#include "OgreManager.h"
#include "ManipulatorScene.h"
#include "Utility.h"
#include "Effect/EffectController.h"
#include "Effect/ParticleEffect.h"

ManipulatorEffect::ManipulatorEffect()
:m_pssmLambda(0.75f)
,m_ssaoSampleLength(20)
,m_ssaoOffsetScale(1)
,m_ssaoDefaultAccessibility(0.5f)
,m_ssaoEdgeHighlight(1.99f)
,m_curEditEffect(nullptr)
,m_bIsPlayAnim(false)
,m_curAnim(Ogre::StringUtil::BLANK)
{

}

ManipulatorEffect::~ManipulatorEffect()
{
	for(auto iter=m_effects.begin(); iter!=m_effects.end(); ++iter)
		delete iter->second;
	m_effects.clear();
}

void ManipulatorEffect::SetShadowEnable( bool bEnable )
{
	RenderManager.EnableShadow(bEnable);
}

bool ManipulatorEffect::GetShadowEnable() const
{
	return RenderManager.GetEffectConfig().bShadow;
}

void ManipulatorEffect::SetSSAOEnable( bool bEnable )
{
	RenderManager.EnableSSAO(bEnable);
}

bool ManipulatorEffect::GetSSAOEnable() const
{
	return RenderManager.GetEffectConfig().bSSAO;
}

void ManipulatorEffect::SetShadowFarDist( float dist )
{
	RenderManager.m_pSceneMgr->setShadowFarDistance(dist);
}

void ManipulatorEffect::SetShadowSplitPadding( float pad )
{
	RenderManager.GetShadowCameraSetup()->setSplitPadding(pad);
}

void ManipulatorEffect::SetShadowOptimalAdjustFactor( int layer, float factor )
{
	RenderManager.GetShadowCameraSetup()->setOptimalAdjustFactor(layer, factor);
}

void ManipulatorEffect::SetShadowUseSimpleOptimalAdjust( bool b )
{
	RenderManager.GetShadowCameraSetup()->setUseSimpleOptimalAdjust(b);
}

void ManipulatorEffect::SetShadowCameraLightDirectionThreshold( int degree )
{
	RenderManager.GetShadowCameraSetup()->setCameraLightDirectionThreshold(Ogre::Degree((float)degree));
}

void ManipulatorEffect::SetShadowMapSize( int layer, int size )
{
	RenderManager.m_pSceneMgr->setShadowTextureConfig(layer, size, size, Ogre::PF_FLOAT32_R);
}

void ManipulatorEffect::SetShadowSelfShadow( bool b )
{
	RenderManager.m_pSceneMgr->setShadowTextureSelfShadow(b);
}

void ManipulatorEffect::SetShadowCasterRenderBackFaces( bool b )
{
	RenderManager.m_pSceneMgr->setShadowCasterRenderBackFaces(b);
}

void ManipulatorEffect::SetShadowPssmLambda( float f )
{
	m_pssmLambda = f;
	float n = RenderManager.m_pMainCamera->getNearClipDistance();
	float farDist = RenderManager.m_pSceneMgr->getShadowFarDistance();
	RenderManager.GetShadowCameraSetup()->calculateSplitPoints(3, n, farDist, m_pssmLambda); 
}

void ManipulatorEffect::SetShadowDirectionalLightExtrusionDistance( float f )
{
	RenderManager.m_pSceneMgr->setShadowDirectionalLightExtrusionDistance(f);
}

float ManipulatorEffect::GetShadowFarDist() const
{
	return RenderManager.m_pSceneMgr->getShadowFarDistance();
}

float ManipulatorEffect::GetShadowSplitPadding() const
{
	return RenderManager.GetShadowCameraSetup()->getSplitPadding();
}

Ogre::Vector3 ManipulatorEffect::GetShadowOptimalAdjustFactor() const
{
	Ogre::PSSMShadowCameraSetup* cam = RenderManager.GetShadowCameraSetup();
	return Ogre::Vector3(cam->getOptimalAdjustFactor(0), cam->getOptimalAdjustFactor(1), cam->getOptimalAdjustFactor(2));
}

bool ManipulatorEffect::GetShadowUseSimpleOptimalAdjust() const
{
	return RenderManager.GetShadowCameraSetup()->getUseSimpleOptimalAdjust();
}

int ManipulatorEffect::GetShadowCameraLightDirectionThreshold() const
{
	return (int)RenderManager.GetShadowCameraSetup()->getCameraLightDirectionThreshold().valueDegrees();
}

Ogre::Vector3 ManipulatorEffect::GetShadowMapSize() const
{
	Ogre::Vector3 ret;
	auto iter = RenderManager.m_pSceneMgr->getShadowTextureConfigIterator();
	ret.x = (float)iter.getNext().width;
	ret.y = (float)iter.getNext().width;
	ret.z = (float)iter.getNext().width;

	return ret;
}

bool ManipulatorEffect::GetShadowSelfShadow() const
{
	return RenderManager.m_pSceneMgr->getShadowTextureSelfShadow();
}

bool ManipulatorEffect::GetShadowCasterRenderBackFaces() const
{
	return RenderManager.m_pSceneMgr->getShadowCasterRenderBackFaces();
}

float ManipulatorEffect::GetShadowPssmLambda() const
{
	return m_pssmLambda;
}

float ManipulatorEffect::GetShadowDirectionalLightExtrusionDistance() const
{
	return RenderManager.m_pSceneMgr->getShadowDirectionalLightExtrusionDistance();
}

void ManipulatorEffect::Serialize( rapidxml::xml_document<>* doc, rapidxml::xml_node<>* XMLNode )
{
	using namespace Ogre;
	const Kratos::SEffectConfig& cfg = RenderManager.GetEffectConfig();
	SceneManager* sm = RenderManager.m_pSceneMgr;

	const String strAmbient = StringConverter::toString(sm->getAmbientLight());
	const String strShadowOn = StringConverter::toString(cfg.bShadow);

	//shadow param
	const String strFarDist			= StringConverter::toString(GetShadowFarDist());
	const String strPad				= StringConverter::toString(GetShadowSplitPadding());
	const String strAdjustFactor	= StringConverter::toString(GetShadowOptimalAdjustFactor());
	const String strUseSimpleAdjust = StringConverter::toString(GetShadowUseSimpleOptimalAdjust());
	const String strThreshold		= StringConverter::toString(GetShadowCameraLightDirectionThreshold());
	const String strTexSize			= StringConverter::toString(GetShadowMapSize());
	const String strSelfShadow		= StringConverter::toString(GetShadowSelfShadow());
	const String strRenderBack		= StringConverter::toString(GetShadowCasterRenderBackFaces());
	const String strPssmLambda		= StringConverter::toString(GetShadowPssmLambda());
	const String strExtrusion		= StringConverter::toString(GetShadowDirectionalLightExtrusionDistance());

	rapidxml::xml_node<>* shadowNode = doc->allocate_node(rapidxml::node_element, "shadow");

	shadowNode->append_attribute(doc->allocate_attribute("AmbientLight", doc->allocate_string(strAmbient.c_str())));
	shadowNode->append_attribute(doc->allocate_attribute("EnableShadow", doc->allocate_string(strShadowOn.c_str())));
	shadowNode->append_attribute(doc->allocate_attribute("FarDistance",	doc->allocate_string(strFarDist.c_str())));
	shadowNode->append_attribute(doc->allocate_attribute("SplitPadding", doc->allocate_string(strPad.c_str())));
	shadowNode->append_attribute(doc->allocate_attribute("AdjustFactor", doc->allocate_string(strAdjustFactor.c_str())));
	shadowNode->append_attribute(doc->allocate_attribute("UseSimpleAdjust", doc->allocate_string(strUseSimpleAdjust.c_str())));
	shadowNode->append_attribute(doc->allocate_attribute("CameraLightDirectionThreshold", doc->allocate_string(strThreshold.c_str())));
	shadowNode->append_attribute(doc->allocate_attribute("ShadowMapSize", doc->allocate_string(strTexSize.c_str())));
	shadowNode->append_attribute(doc->allocate_attribute("SelfShadow", doc->allocate_string(strSelfShadow.c_str())));
	shadowNode->append_attribute(doc->allocate_attribute("RenderBackFace", doc->allocate_string(strRenderBack.c_str())));
	shadowNode->append_attribute(doc->allocate_attribute("PssmLambda", doc->allocate_string(strPssmLambda.c_str())));
	shadowNode->append_attribute(doc->allocate_attribute("LightExtrusionDistance", doc->allocate_string(strExtrusion.c_str())));

	XMLNode->append_node(shadowNode);

	//ssao param
	const String strSsaoOn = StringConverter::toString(cfg.bSSAO);
	const String strSampleLen				= StringConverter::toString(GetSSAOSampleLength());
	const String strOffsetScale				= StringConverter::toString(GetSSAOOffsetScale());
	const String strDefaultAccessibility	= StringConverter::toString(GetSSAODefaultAccessibility());
	const String strEdgeHighlight			= StringConverter::toString(GetSSAOEdgeHighlight());

	rapidxml::xml_node<>* ssaoNode = doc->allocate_node(rapidxml::node_element, "ssao");

	ssaoNode->append_attribute(doc->allocate_attribute("EnableSSAO", doc->allocate_string(strSsaoOn.c_str())));
	ssaoNode->append_attribute(doc->allocate_attribute("SampleLength", doc->allocate_string(strSampleLen.c_str())));
	ssaoNode->append_attribute(doc->allocate_attribute("OffsetScale", doc->allocate_string(strOffsetScale.c_str())));
	ssaoNode->append_attribute(doc->allocate_attribute("DefaultAccessibility", doc->allocate_string(strDefaultAccessibility.c_str())));
	ssaoNode->append_attribute(doc->allocate_attribute("EdgeHighlight",	doc->allocate_string(strEdgeHighlight.c_str())));

	XMLNode->append_node(ssaoNode);

	///�������е�λ�Ĺҽ���Ч��Ϣ
	for (auto itUnit=m_effects.begin(); itUnit!=m_effects.end(); ++itUnit)
	{
		Kratos::EffectController* pCtrl = itUnit->second;
		const auto& effects = pCtrl->_GetEffects();

		const std::string& meshname = itUnit->first->getMesh()->getName();
		SUnitData* unitData = ManipulatorSystem.GetGameData().GetUnitData(meshname);

		for (auto itAnim=effects.begin(); itAnim!=effects.end(); ++itAnim)
		{
			const auto& slots = itAnim->second;
			for (auto itEffect=slots.begin(); itEffect!=slots.end(); ++itEffect)
			{
				Kratos::ParticleEffect* particle = itEffect->second;
				SEffectData data;
				data.m_locator		= particle->GetLocator();
				data.m_anim			= itAnim->first;
				data.m_particleTmp	= particle->GetParticleTemplate();
				data.m_fStartTime	= particle->GetStartTime();
				data.m_fLifeTime	= particle->GetLifeTime();

				unitData->m_effects.push_back(data);
			}
		}
	}
}

void ManipulatorEffect::SetSSAOSampleLength( float f )
{
	RenderManager.SetSSAOParam("cSampleLengthScreenSpace", f/100);
	m_ssaoSampleLength = f;
}

void ManipulatorEffect::SetSSAOOffsetScale( float f )
{
	RenderManager.SetSSAOParam("cOffsetScale", f/100);
	m_ssaoOffsetScale = f;
}

void ManipulatorEffect::SetSSAOEdgeHighlight( float f )
{
	RenderManager.SetSSAOParam("cEdgeHighlight", f);
	m_ssaoEdgeHighlight = f;
}

void ManipulatorEffect::SetSSAODefaultAccessibility( float f )
{
	RenderManager.SetSSAOParam("cDefaultAccessibility", f);
	m_ssaoDefaultAccessibility = f;
}

float ManipulatorEffect::GetSSAOSampleLength() const
{
	return m_ssaoSampleLength;
}

float ManipulatorEffect::GetSSAOOffsetScale() const
{
	return m_ssaoOffsetScale;
}

float ManipulatorEffect::GetSSAOEdgeHighlight() const
{
	return m_ssaoEdgeHighlight;
}

float ManipulatorEffect::GetSSAODefaultAccessibility() const
{
	return m_ssaoDefaultAccessibility;
}

std::vector<std::wstring> ManipulatorEffect::GetParticleTmpNames() const
{
	std::vector<std::wstring> ret;

	Ogre::FileInfoListPtr fileinfo = Ogre::ResourceGroupManager::getSingleton().findResourceFileInfo(
		"ParticleUniverse", "*.pu");

	for(auto iter=fileinfo->begin(); iter!=fileinfo->end(); ++iter)
	{
		const Ogre::FileInfo& info = *iter;
		ret.push_back(Utility::EngineToUnicode(info.basename));
	}

	return std::move(ret);
}

std::vector<std::wstring> ManipulatorEffect::GetAnimationNames() const
{
	Ogre::Entity* pEntity = ManipulatorSystem.GetObject().GetSelection();
	assert(pEntity);
	std::vector<std::wstring> vecRet;
	Ogre::Skeleton* pSkeleton = pEntity->getSkeleton();

	//û�п��ö���
	if(!pSkeleton || pSkeleton->getNumAnimations()==0)
		return std::move(vecRet);

	for(size_t i=0; i<pSkeleton->getNumAnimations(); ++i)
		vecRet.push_back(Utility::EngineToUnicode(pSkeleton->getAnimation(i)->getName()));

	return std::move(vecRet);
}

void ManipulatorEffect::PlayAnimation( int animIndex, bool bPlayOrStop )
{
	Ogre::Entity* ent = ManipulatorSystem.GetObject().GetSelection();
	assert(ent);

	if (bPlayOrStop)
	{
		const Ogre::String& animName = ent->getSkeleton()->getAnimation(animIndex)->getName();
		m_effects[ent]->PlayAnimation(animName, true);
	}
	else
	{
		m_effects[ent]->StopAnimation();
	}

	m_bIsPlayAnim = bPlayOrStop;
}

void ManipulatorEffect::SetCurAnimationName( const std::string& anim )
{
	Ogre::Entity* ent = ManipulatorSystem.GetObject().GetSelection();
	SetActiveEffect("", "");
	m_curAnim = anim;
}

const std::string ManipulatorEffect::GetCurAnimationName()
{
	return m_curAnim;
}

std::vector<std::wstring> ManipulatorEffect::GetLocatorNames() const
{
	Ogre::Entity* ent = ManipulatorSystem.GetObject().GetSelection();
	assert(ent);

	std::vector<std::wstring> ret;
	//M3ģ�ʹ�max����ʱlocator����ΪRef_xxx��ʽ
	Ogre::SkeletonPtr skel = ent->getMesh()->getSkeleton();
	Ogre::Skeleton::BoneIterator iter = skel->getBoneIterator();

	while (iter.hasMoreElements())
	{
		Ogre::Bone* pBone = iter.peekNext();
		if(pBone->getName().find("Ref_") != Ogre::String::npos)
			ret.push_back(Utility::EngineToUnicode(pBone->getName()));

		iter.getNext();
	}

	return std::move(ret);
}

bool ManipulatorEffect::SetEffectParam( const std::string& param, const std::string& value )
{
	if(!m_curEditEffect)
		return false;

	bool ret = m_curEditEffect->setParameter(param, value);
	assert(ret);

	return true;
}

const std::string ManipulatorEffect::GetEffectParam( const std::string& param ) const
{
	if(!m_curEditEffect)
		return Ogre::StringUtil::BLANK;

	return m_curEditEffect->getParameter(param);
}

void ManipulatorEffect::SetActiveEffect( const std::string& animName, const std::string& locator )
{
	Ogre::Entity* ent = ManipulatorSystem.GetObject().GetSelection();
	//��ȡ������
	auto iter = m_effects.find(ent);
	if (iter == m_effects.end())
		iter = m_effects.insert(std::make_pair(ent, new Kratos::EffectController(ent))).first;

	if (!animName.empty() && !locator.empty())
	{
		//��ȡ��Ч
		Kratos::EffectController* controller = iter->second;
		m_curEditEffect = controller->GetEffect(animName, locator);
		if(!m_curEditEffect)
		{
			m_curEditEffect = new Kratos::ParticleEffect(ent);
			controller->AddEffect(animName, locator, m_curEditEffect);
		}
	}
}

void ManipulatorEffect::OnFrameMove( float dt )
{
	Ogre::Entity* ent = ManipulatorSystem.GetObject().GetSelection();
	auto iter = m_effects.find(ent);
	if(iter != m_effects.end())
		iter->second->Update(dt);
}

bool ManipulatorEffect::GetIsPlayingAnim() const
{
	return m_bIsPlayAnim;
}
