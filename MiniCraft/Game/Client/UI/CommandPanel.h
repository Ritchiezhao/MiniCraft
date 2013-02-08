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

//���ܲ�״̬
enum eSlotState
{
	eSlotState_Normal,
	eSlotState_Highlight,
	eSlotState_Disable,
	eSlotState_Empty
};

class UiCommandPanel
{
public:
	UiCommandPanel();
	~UiCommandPanel() {}

public:
	void	Init();
	void	Destroy();
	//����������ͼ��
	void	CEGUI_SetAbilitySlot(int slotIndex, eSlotState state, const std::string& imgName = "");

private:
	CEGUI::Window*	m_pLayout;
};


#endif // CommandPanel_h__