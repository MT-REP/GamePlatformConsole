// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DATACONCILIATION_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DATACONCILIATION_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#pragma once
#ifndef DataConciliation_H
#define DataConciliation_H

#ifdef DATACONCILIATION_EXPORTS
#define DATACONCILIATION_API __declspec(dllexport)
#else
#define DATACONCILIATION_API __declspec(dllimport)
#endif

#include <Afxsock.h>

typedef struct DataStruct
{
	unsigned  char checkID; //���͸��Ǹ�ƽ̨
	unsigned  char valid;   //������Ч
	unsigned  char select;  //ӰƬ����Ϸѡ��
	unsigned  char StartPause; //��ʼ��ͣ
	float  kVaule[6];//Kֵ
	float  pVaule[6];//Pֵ
	float  zVaule[6];//Zֵ
	DataStruct()
	{
		checkID = 55; //���͸��Ǹ�ƽ̨
		valid = 0;   //������Ч ��ʼֵΪ0  1ΪӰƬ����Ϸ�л� 2Ϊ��Ϸ��ʼ��ͣ������Ч 3Ϊ������Ч��ѯ  4������Ч��������
		select = 0;  //ӰƬ����Ϸѡ�� ��ʼֵΪ0 ��ЧֵΪ 1��2��3������
		StartPause = 0; //��ʼ��ͣ ��ʼֵΪ0  1��ʼ 2 ��ͣ 3����
		for (int i = 0; i < 6; i++)
		{
			kVaule[i] = 0.0f;//Kֵ
			pVaule[i] = 0.0f;//Pֵ
			zVaule[i] = 0.0f;//Zֵ
		}
	}
}MDataStruct;

// �����Ǵ� DataConciliation.dll ������
class DATACONCILIATION_API CDataConciliation {
public:
	CDataConciliation(void);//���캯��
	~CDataConciliation();//��������
	bool socketInit(char strIP[30], int port);//��ʼ������
	void setRemote(char strIP[30], int port);//����Զ��IP�Ͷ˿�
	bool sendData(void);//��������
	void setData(MDataStruct &Vaule);//��������
	void getDataStruct(MDataStruct *inVaule);
private:
	static UINT ThreadProc(LPVOID pParam);//�̺߳���
	struct sockaddr_in remote_addr;//Զ��ip�Ͷ˿ں�
	int sockfd;  //socket
	bool runFlag;//�߳����б�־
	HANDLE hThread;//�߳̾��
	MDataStruct mMDataStruct;//���յ�������
};
#endif