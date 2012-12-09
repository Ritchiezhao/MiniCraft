-------Unit״̬��

--[[
			Unit�ർ������
	void PlayAnimation(string, string)		param:top�㶯����,base�㶯����		ret:��
	void StopAnimation()					param:��			ret:��
	bool FindPath(float, float, float)		param:Ŀ������	ret:�ɹ�����true,����false
	void SetState(int)							param:Ҫ�л���״̬��־,�������eUnitState_xx	ret:��
	void SetDestPosition(float, float, float)	param:����Ŀ���	ret:��
	float,float,float GetDestPosition()		param:��			ret:��ȡ��ǰĿ���
	int GetCurCommandType()					param:��			ret:��ȡ��ǰ�����־,�������eCommandType_xx
	bool UpdatePathFinding(float)			param:֡���ʱ��	ret:�����Ѱ·,����Ŀ���򷵻�true
	void Lookat(float, float, float)		param:lookat�����	ret:��
	void AttachRes(string, float, float, float, float)	param:mesh��,�������Unit�ڵ��λ��,���������ϵ��	ret:��
	void DetachRes()						param:��			ret:��
--]]


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
function IdleState_Enter(id)
	UnitTable[id]:PlayAnimation("IdleTop", "");
end

function IdleState_Update(id,dt)
end

function IdleState_Exit(id)
	UnitTable[id]:StopAnimation();
end

---------------------
---Move State
---------------------

function MoveState_Enter(id)
	if not UnitTable[id]:FindPath(UnitTable[id]:GetDestPosition()) then
		--Ѱ·ʧ��,ת�����״̬
		UnitTable[id]:SetState(eUnitState_Idle);
	end

	--���ܶ���
	UnitTable[id]:PlayAnimation("RunTop", "RunBase");
end

function MoveState_Update(id,dt)
	--Ѱ·����,����Ŀ�ĵ�
	if UnitTable[id]:UpdatePathFinding(dt) then
		cmdType = UnitTable[id]:GetCurCommandType();
		if cmdType == eCommandType_Move then
			--��ͨ�ƶ�����,ת������״̬
			UnitTable[id]:SetState(eUnitState_Idle);
		elseif cmdType == eCommandType_Harvest then
			--ת��ɼ�״̬
			UnitTable[id]:SetState(eUnitState_Collect);
		end
	end
end

function MoveState_Exit(id)
	UnitTable[id]:StopAnimation();
end

---------------------
---CollectRes State
---------------------
local pastTime = 0;
--�ɼ�ʱ��
local collectTime = 3;

function CollectResState_Enter(id)
	UnitTable[id]:PlayAnimation("SliceHorizontal", "");
	UnitTable[id]:Lookat(0, 0, -1.8);
	pastTime = 0;
end

function CollectResState_Update(id,dt)
	--FIXME:pastTime��������Ա����,�ǲ�ͬ������е�
	pastTime = pastTime + dt;
	--ת�뷵����Դ״̬
	if pastTime >= collectTime then
		UnitTable[id]:SetDestPosition(returnResX, returnResY, returnResZ);
		UnitTable[id]:SetState(eUnitState_Return);
	end
end

function CollectResState_Exit(id)
	UnitTable[id]:StopAnimation();
end

---------------------
---ReturnRes State
---------------------

function ReturnResState_Enter()
	UnitTable[id]:PlayAnimation("", "RunBase");
	if UnitTable[id]:FindPath(returnResX, returnResY, returnResZ) then
		--����һ����Դ����..
		UnitTable[id]:AttachRes("knot.mesh", 0, 5, 0, 0.02);
	end
end

function ReturnResState_Update(dt)
	if UnitTable[id]:UpdatePathFinding(dt) then
		--����ȥ�ɼ���Դ
		UnitTable[id]:SetDestPosition(collectResX, collectResY, collectResZ);
		UnitTable[id]:SetState(eUnitState_Move);
	end
end

function ReturnResState_Exit()
	UnitTable[id]:StopAnimation();
	UnitTable[id]:DetachRes();
end