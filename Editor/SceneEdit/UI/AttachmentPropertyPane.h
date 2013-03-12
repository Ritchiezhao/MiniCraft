/********************************************************************
	created:	11:3:2013   1:52
	filename: 	F:\MiniCraft\Editor\SceneEdit\UI\AttachmentPropertyPane.h
	author:		maval
	
	purpose:	ģ�͹ҽ����������,attachment����ӦM3ģ����max�е�attachment�ڵ�
*********************************************************************/

#ifndef AttachmentPropertyPane_h__
#define AttachmentPropertyPane_h__

#include "PropertiesPane.h"

class PropertyPaneAttachment : public CPropertiesPane
{
public:
	enum ePropertyID
	{
		////property range [propStart, propEnd)
		propStart = 0,
		////These are ReadOnly items
		propAnimName = propStart,						//ģ�͵�ǰ����
		////////These are Mutable items					
		propMutableItemStart,							
		propLocator = propMutableItemStart,				//�ҽӵ�ѡ��
		propParticle,									//�ҽ�������Ч
		propStartTime,									//��Ч��Զ�����ʼ��ʱ��
		propLifeTime,									//��Чʱ��
		propMutableItemEnd,
		propEnd = propMutableItemEnd,
	};

public:
	PropertyPaneAttachment():CPropertiesPane() {}
	~PropertyPaneAttachment() {}

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


#endif // AttachmentPropertyPane_h__














