/********************************************************************
	created:	8:1:2013   1:26
	filename: 	F:\MiniCraft\Editor\SceneEdit\UI\XTPCustomPropertyGridItem.h
	author:		maval
	
	purpose:	XTP属性控件扩展
*********************************************************************/

#ifndef XTPCustomPropertyGridItem_h__
#define XTPCustomPropertyGridItem_h__


//
//Vector3属性控件
//
class CXTPPropertyGridItemVec3 : public CXTPPropertyGridItem
{
public:
	CXTPPropertyGridItemVec3(CString strCaption, const Ogre::Vector3& value);

public:
	virtual void SetReadOnly(BOOL bReadOnly = TRUE);
	virtual void SetValue(CString strValue);

	void		SetChildItemID(int idX, int idY, int idZ);
	CString		GetStrX() const { return m_X->GetValue(); }
	CString		GetStrY() const { return m_Y->GetValue(); }
	CString		GetStrZ() const { return m_Z->GetValue(); }

protected:
	virtual void OnAddChildItem();

private:
	CXTPPropertyGridItem* m_X;
	CXTPPropertyGridItem* m_Y;
	CXTPPropertyGridItem* m_Z;

	Ogre::Vector3	m_value;
};

//
//Vector4属性控件
//
class CXTPPropertyGridItemVec4 : public CXTPPropertyGridItem
{
public:
	CXTPPropertyGridItemVec4(CString strCaption, const Ogre::Vector4& value);

public:
	virtual void SetReadOnly(BOOL bReadOnly = TRUE);
	virtual void SetValue(CString strValue);

	void		SetChildItemID(int idX, int idY, int idZ, int idW);
	CString		GetStrX() const { return m_X->GetValue(); }
	CString		GetStrY() const { return m_Y->GetValue(); }
	CString		GetStrZ() const { return m_Z->GetValue(); }
	CString		GetStrW() const { return m_W->GetValue(); }

protected:
	virtual void OnAddChildItem();

private:
	CXTPPropertyGridItem* m_X;
	CXTPPropertyGridItem* m_Y;
	CXTPPropertyGridItem* m_Z;
	CXTPPropertyGridItem* m_W;

	Ogre::Vector4	m_value;
};

//helper
Ogre::Vector3	UpdateVec3ItemProperty(CXTPPropertyGridItemVec3* pItem);

#endif // XTPCustomPropertyGridItem_h__














