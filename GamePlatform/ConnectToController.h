#pragma once
#include "MT_AsyncSocket.h"

enum DOF_state
{
	dof_stop = 0,			//
	dof_sys_moving = 1,		//
	dof_neutral = 2,		//
	dof_working = 3,		//
	dof_setconf = 3,		//
	dof_select = 8,
	dof_check_id = 55,
	dof_closed = 253,
	dof_emg = 254,
	dof_err = 255
};
enum M_nCmd
{
	S_CMD_RUN = 0,									//��������
	S_CMD_Check = 1,
	S_CMD_Back2MID = 2,								// �׻�����λ
	S_CMD_ToMerg = 3,								//	����ͣ��
	S_CMD_ToWork = 4,								// ����Э��
	S_CMD_JOG = 5,									//�����ֶ�	
	S_CMD_Work = 6,									//�ɵ�λ��������λ
	S_CMD_Stop = 7,									//����λ���䵽��λ
	S_CMD_ChaConf = 8,								//������������Ϣ
	S_CMD_HOM = 9,
	S_CMD_JOYCTRL = 101,
	S_CMD_GAMECTRL = 102,
	S_CMD_GAMESTARTUP=120,

	S_CMD_ENABLE_RUN=168,
};

struct DataToDOF
{
	BYTE nCheckID;
	BYTE nCmd;
	BYTE nAct;
	BYTE nReserved;									//����

	float DOFs[6];									//{��ҡ�����㣬����ǰ�򣬲�������	}
	float Vxyz[3];									//{ǰ�򣬲�������}������Ϊ��������Ϊ��
	float Axyz[3];		//...
};

struct DataToHost
{
	BYTE nCheckID;
	BYTE nDOFStatus;
	BYTE nRev0;										//��Ҫʹ��
	BYTE nRev1;										//��Ҫʹ��

	float attitude[6];								//��Ҫʹ�ã�RotorTrim��MixtureControl
	float para[6];									
	float motor_code[6];							
};

class CConnectToController :
	public CMT_AsyncSocket
{
public:
	CConnectToController();
	~CConnectToController();

	virtual void OnReceive(int nErrorCode);
	//parameter
	const int m_MaxDelay = 6000;					//60000*10ms
	DataToDOF m_preDataToDof;
	DataToDOF m_sToDOFBuf;
	DataToDOF m_sDataFromMainControlToDof;//m_sToDOFBuf2;
	DataToHost	m_sReturnedDataFromDOF;
	TCHAR m_tcaControllerIP[17];
	UINT m_nControllerPort;


	//function

	int DOF_UpToMedian();
	int DOF_ToRun();										//enter the state of running
	int DOF_ToMedian();										//return to the state of median from any state
	int DOF_ToBottom();

};

