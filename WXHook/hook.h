#pragma once
#include "framework.h"
// #include "OffsetAddr2.9.5.h"
#include "OffsetAddr3_2_1.h"


DWORD showDbgInfo(const wchar_t* erorrInfo, const wchar_t* infoType);
// int CDECL MessageBoxPrintf(const char* szCaption, const char* szFormat, ...);


// ��ȡWeChatWin.dllģ���ַ
HMODULE getWeChatDLLAddr();

// ��ת����ά���¼
void GotoQrCode();

void InlineHook(DWORD dwHookAddr, LPVOID pFunAddr);

void HookWxQRCode();
// ��ȡ��ά������ û�õ�
void getQrCodeLink();

//�ж��Ƿ��ǵ�¼״̬
DWORD IsUserLogin();

// ��ȡ��¼״̬
DWORD getLoginStatus();

// ����һ������
void gotoBackupBtn();

// �ֻ����챸��������==> δ����
void mbBackupToCom();

// �����ά������
DWORD SaveQRCodeData(DWORD * QrPtr, DWORD dwSize);

// ��ʾͼƬ
void ShowQRCode();

// ˢ�¶�ά��
void RefreshQrcode();

/******��ȡ�����Ƿ��ص���Կ*****/
void HookDBPwd();
void SavePwd(DWORD dwPwdPrt, DWORD dwPwdLen);

// �µ��ֻ����ݵ����Ժ���
void NewMobToComp();

// ��ʼ������
void InitFun();