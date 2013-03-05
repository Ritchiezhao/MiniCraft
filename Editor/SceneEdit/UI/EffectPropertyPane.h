/********************************************************************
	created:	5:3:2013   1:36
	filename: 	F:\MiniCraft\Editor\SceneEdit\UI\EffectPropertyPane.h
	author:		maval
	
	purpose:	ͼ��Ч���������
*********************************************************************/

#ifndef EffectPropertyPane_h__
#define EffectPropertyPane_h__


#include "PropertiesPane.h"

class PropertyPaneEffect : public CPropertiesPane
{
public:
	enum ePropertyID
	{
		////property range [propStart, propEnd)
		propStart = 0,
		////////These are Mutable items
		propMutableItemStart = propStart,
		propShadowFarDist = propMutableItemStart,
		propShadowSplitPadding,
		propShadowOptimalAdjustFactor,
		propShadowUseSimpleOptimalAdjust,
		propShadowCameraLightDirectionThreshold,
		propShadowMapSize,
		propShadowSelfShadow,
		propShadowCasterRenderBackFaces,
		propShadowLambda,
		propShadowDirectionalLightExtrusionDistance,
		propSSAOSampleLength,
		propSSAOOffsetScale,
		propSSAOEdgeHighlight,
		propSSAODefaultAccessibility,
		propMutableItemEnd,
		propEnd = propMutableItemEnd,

		//Auto managed property
		propOptimalAdjustFactor0, propOptimalAdjustFactor1, propOptimalAdjustFactor2,
		propShadowMapSize0, propShadowMapSize1, propShadowMapSize2
	};

public:
	PropertyPaneEffect():CPropertiesPane() {}
	~PropertyPaneEffect() {}

	//�������пؼ�����
	void	UpdateAllFromEngine();
	//���¿ؼ�����
	void	UpdateProperty(int id);
	//����/��ֹ�༭Mutable����(ReadOnly���ݲ���Ҫ��,�����Ͳ��ܱ༭)
	void	EnableMutableProperty(BOOL bEnable);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnGridNotify(WPARAM, LPARAM);

private:
	std::unordered_map<int, CXTPPropertyGridItem*>	m_mapItem;
};


#endif // EffectPropertyPane_h__














