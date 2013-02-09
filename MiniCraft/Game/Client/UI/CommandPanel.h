/********************************************************************
	created:	3:2:2013   1:59
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\UI\CommandPanel.h
	author:		maval
	
	purpose:	�������UI���
*********************************************************************/

#ifndef CommandPanel_h__
#define CommandPanel_h__

namespace CEGUI
{
	class Window;
}
class SelectableObject;

class UiCommandPanel
{
public:
	UiCommandPanel();
	~UiCommandPanel() {}

public:
	void	Init();
	void	Destroy();
	//����������ͼ��
	void	CEGUI_SetAbilitySlot(int slotIndex, bool bEnable, const std::string& imgName = "");
	//���õ�ǰѡ������
	void	SetActiveObject(SelectableObject* pObject) { m_pActiveObj = pObject; }

private:
	///UI��Ӧ
	template<int Slot>
	bool CEGUI_OnCommandBtnClicked(const CEGUI::EventArgs& e);

private:
	CEGUI::Window*		m_pLayout;
	SelectableObject*	m_pActiveObj;
};


#endif // CommandPanel_h__