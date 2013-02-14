/********************************************************************
	created:	21:1:2013   23:36
	filename: 	F:\MiniCraft\MiniCraft\Game\Client\AI\AiComponent.h
	author:		maval
	
	purpose:	AI���,�߼�����ͨ�����ʹ�ø���
*********************************************************************/

#ifndef AIComponent_h__
#define AIComponent_h__

#include "GameDefine.h"
#include "Command.h"
#include "ObjectState.h"

class SelectableObject;

///AI�������
class AiComponent
{
public:
	AiComponent(SelectableObject* pOwner);
	virtual ~AiComponent();

public:
	void			Update(float dt);
	//ִ������.bForceExecuteΪtrue��ȡ����ǰ����,ֱ��ִ�и�����
	void			GiveCommand(Command& cmd, bool bForceExecute = false);
	//����Ҽ�����
	void			GiveCommand(const OIS::MouseEvent& arg);
	void			CancelCurCommand();
	eCommandType	GetCurCommand() const;
	void			SetCurState(eObjectState state);
	eObjectState	GetCurState() const { return m_curState; }

	//��ǰ�������,�ӵ�֪ͨ
	void			_OnCommandFinished();

private:
	typedef std::vector<ObjectState*>	StateLib;
	StateLib			m_states;		//״̬����.ÿ��״ֻ̬����һ��ʵ���洢�����﹩ȡ��

	typedef std::list<Command> CommandQueue;
	CommandQueue		m_cmdQueue;		//�������

	SelectableObject*	m_pOwner;		//�������������
	bool				m_bExecuting;	//��ǰ�Ƿ���ִ������
	eObjectState		m_curState;		//����ǰ����״̬
};

#endif // AIComponent_h__