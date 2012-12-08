-------Unit״̬��

----------------------
--��������
----------------------
eUnitState_Idle		=	0
eUnitState_Move		=	1
eUnitState_Attack	=	2
eUnitState_Collect	=	3
eUnitState_Return	=	4
eUnitState_Build	=	5

eCommandType_Move	=	0
eCommandType_Attack	=	1
eCommandType_Harvest =	2
eCommandType_Build	=	3

resX, resY, resZ	=	0, 0, 0
collectResX, collectResY, collectResZ	=	-1.25, 0, 9.64
returnResX, returnResY, returnResZ	= 0, 0, 16

---------------------
---Idle State
---------------------
function IdleState_Enter()
	Unit0:PlayAnimation("IdleTop", "");
end

function IdleState_Update(dt)
end

function IdleState_Exit()
	Unit0:StopAnimation();
end

---------------------
---Move State
---------------------

function MoveState_Enter()
	if not Unit0:FindPath(Unit0:GetDestPosition()) then
		--Ѱ·ʧ��,ת�����״̬
		Unit0:SetState(eUnitState_Idle);
	end

	--���ܶ���
	Unit0:PlayAnimation("RunTop", "RunBase");
end

function MoveState_Update(dt)
	--Ѱ·����,����Ŀ�ĵ�
	if Unit0:UpdatePathFinding(dt) then
		cmdType = Unit0:GetCurCommandType();
		if cmdType == eCommandType_Move then
			--��ͨ�ƶ�����,ת������״̬
			Unit0:SetState(eUnitState_Idle);
		elseif cmdType == eCommandType_Harvest then
			--ת��ɼ�״̬
			Unit0:SetState(eUnitState_Collect);
		end
	end
end

function MoveState_Exit()
	Unit0:StopAnimation();
end

---------------------
---CollectRes State
---------------------
local pastTime = 0;
--�ɼ�ʱ��
local collectTime = 3;

function CollectResState_Enter()
	Unit0:PlayAnimation("SliceHorizontal", "");
	Unit0:Lookat(0, 0, -1.8);
	pastTime = 0;
end

function CollectResState_Update(dt)
	pastTime = pastTime + dt;
	--ת�뷵����Դ״̬
	if pastTime >= collectTime then
		Unit0:SetDestPosition(returnResX, returnResY, returnResZ);
		Unit0:SetState(eUnitState_Return);
	end
end

function CollectResState_Exit()
	Unit0:StopAnimation();
end

---------------------
---ReturnRes State
---------------------

function ReturnResState_Enter()
	Unit0:PlayAnimation("", "RunBase");
	if Unit0:FindPath(returnResX, returnResY, returnResZ) then
		--����һ����Դ����..
		Unit0:AttachRes("knot.mesh", 0, 5, 0, 0.02);
	end
end

function ReturnResState_Update(dt)
	if Unit0:UpdatePathFinding(dt) then
		--����ȥ�ɼ���Դ
		Unit0:SetDestPosition(collectResX, collectResY, collectResZ);
		Unit0:SetState(eUnitState_Move);
	end
end

function ReturnResState_Exit()
	Unit0:StopAnimation();
	Unit0:DetachRes();
end