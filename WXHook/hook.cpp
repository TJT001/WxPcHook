#include "pch.h"
#include "hook.h"
// #include "Resource.h"

#include "resource1.h"

// #define WXVERSION(StrVersion) GetModuleFileNameW(GetModuleHandleW(L"WeChatWin.dll"),strVersion,256)

//#ifdef WXVERSION = 2.9.5
//#include "offsetAddr2.9.5.h"
//
//#else
//#include "OffsetAddr3.0.1.h"
//
//#endif

// WeChatWin.dll��ַ
static DWORD weChatWinAddr = 0;

DWORD showDbgInfo(const wchar_t * erorrInfo, const wchar_t * infoType)
{
	
	MessageBoxW(NULL, erorrInfo, infoType, MB_OK);
	DWORD dw = GetLastError();
	return dw;
}

//int CDECL MessageBoxPrintf(const char* szCaption, const char* szFormat, ...)
//{
//	TCHAR szBuff[MAX_BUFF];
//	va_list args;
//	va_start(args, szFormat);
//	_vsnprintf_s(szBuff, sizeof(szBuff) / sizeof(TCHAR), szFormat, args);
//	// vsprintf_s(szBuff,szFormat,args);
//	va_end(args);
//	return MessageBox(NULL, szBuff, szCaption, 0);
//}

HMODULE getWeChatDLLAddr()
{
	HMODULE hModule = GetModuleHandleA("WeChatWin.dll");
	// HMODULE hModule = GetModuleHandleW(L"wechat.exe"); E:\SoftWare\WeChat\WeChatWin.dll
	if (hModule == NULL)
	{
		::MessageBoxW(NULL, L"getWeChatDLLAddr->�Ҳ���ָ��ģ��", L"��ʾ", MB_OK);
	}
	return hModule;
}

void GotoQrCode()
{
	// DWORD dwCallAddr1 = (DWORD)getWeChatDLLAddr() + GOTOQRCODE1;
	// DWORD dwCallAddr2 = (DWORD)getWeChatDLLAddr() + GOTOQRCODE2;
	DWORD dwCallAddr1 = weChatWinAddr + GOTOQRCODE1;
	DWORD dwCallAddr2 = weChatWinAddr + GOTOQRCODE2;
	int iRet = -1;
	_asm {
		pushad;
		call dwCallAddr1;
		mov ecx, eax;
		call dwCallAddr2;
		mov eax, iRet;
		popad;
	}
}

void InlineHook(DWORD dwHookAddr, LPVOID pFunAddr)
{
	BYTE backCode[5] = { 0 };
	BYTE jmpCode[5] = { 0xE9 };
	//����ƫ��
	*(DWORD*)(&jmpCode[1]) = (DWORD)pFunAddr - dwHookAddr - 5;

	// ������ǰ���������ڻ�ԭ
	DWORD OldProtext = 0;

	// ��ΪҪ�������д�����ݣ�����Ϊ������ǲ���д�ģ�������Ҫ�޸�����
	VirtualProtect((LPVOID)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);

	memcpy(backCode, (void*)dwHookAddr, 5);

	memcpy((void*)dwHookAddr, jmpCode, 5);

	VirtualProtect((LPVOID)dwHookAddr, 5, OldProtext, &OldProtext);
}

/**********************�õ���ά����Ϣ**************************/
DWORD dwRetAddr1 = (DWORD)GetModuleHandleW(L"WeChatWin.dll") + QRCODEPICTURE + 5;			//	 ����ȥ�ĵ�ַ
DWORD dwOverWrite = (DWORD)GetModuleHandleW(L"WeChatWin.dll") + QRCODEHOOKADDR;
DWORD* dwQrcodePicure = NULL;
DWORD dwQRCodeSize = 0;

void  __declspec(naked) GetWxQRCodePicture()
{
	__asm  pushad
	__asm  xor eax, eax;
	__asm  mov eax, ds:[esi + 0x30];
	__asm  mov dwQrcodePicure, eax;
	__asm  mov eax, ds:[esi + 0x34];
	__asm  mov dwQRCodeSize, eax;
	SaveQRCodeData(dwQrcodePicure, dwQRCodeSize);
	__asm  popad
	//��ת�����ص�ַ
	__asm  call dwOverWrite;
	__asm jmp dwRetAddr1;
}

void HookWxQRCode()
{
	DWORD dwHookAddr = weChatWinAddr + QRCODEPICTURE;
	InlineHook(dwHookAddr, GetWxQRCodePicture);
}

void getQrCodeLink()
{
	/*DWORD linkAddr = weChatWinAddr + QRCODEWEB;

	char* strLink = (char*)*((DWORD*)(weChatWinAddr + QRCODEWEB));
	if (strLink == NULL)
	{
		showDbgInfo(L"���»�ȡ", L"��ʾ");
	}
	MessageBoxA(NULL, strLink, "��ʾ", MB_OK);*/
}

DWORD IsUserLogin()
{
	DWORD* isLoginAddr = (DWORD*)(weChatWinAddr + ISLOGIN);
	if (*isLoginAddr == 0)
	{
		showDbgInfo(L"δ��¼", L"��ʾ");
		return 0;
	}
	else if (*isLoginAddr == 1)
	{
		showDbgInfo(L"���ڵ�¼", L"��ʾ");
		return 1;
	}
	else if (*isLoginAddr == 2)
	{
		showDbgInfo(L"�Ѿ���¼", L"��ʾ");
		return 2;
	}
	char* userWxId = (char*)(DWORD*)(isLoginAddr + 4); // ��¼�û��� WX_Id
}

DWORD getLoginStatus()
{
	return *(DWORD*)(weChatWinAddr + ISLOGIN);
}

void gotoBackupBtn()
{
	DWORD dwCallAddr1 = (DWORD)getWeChatDLLAddr() + GOTOBACKUP1;
	DWORD dwCallAddr2 = (DWORD)getWeChatDLLAddr() + GOTOBACKUP2;
	_asm {
		push 0x0;
		push 0x0;
		push 0x1;
		push 0x3A5;
		call dwCallAddr1;
		mov ecx, eax;
		call dwCallAddr2;
	}
}

void mbBackupToCom()
{
	DWORD dwCallAddr1 = weChatWinAddr + BACKUPTOCOMPUTER1;
	DWORD dwCallAddr2 = weChatWinAddr + BACKUPTOCOMPUTER2;
	DWORD dwCallAddr3 = weChatWinAddr + BACKUPTOCOMPUTER3;
	_asm {
		pushad;
		push 0x460;
		call dwCallAddr1;
		add esp, 4;
		push 0;
		mov ecx, eax;
		push 0x1706FC;
		call dwCallAddr2;
		mov ecx, eax;
		call dwCallAddr3
		popad;
	}
}


DWORD SaveQRCodeData(DWORD * QrPtr, DWORD dwSize)
{
	char szPicPath[MAX_PATH] = { 0 };
	FILE *fp = NULL;
	sprintf_s(szPicPath, "E:\\SourceCode\\WxPcHook\\bin\\%s", "WXQRCode.png");

	fopen_s(&fp, szPicPath, "wb");				//	�����Զ����Ƶķ�ʽ����
	if (fwrite(QrPtr, 1, dwSize, fp))
	{
		fclose(fp);
		// showImage();								// ��ά�뻭��ȥ
		return 1;
	}
	return -1;
}


void ShowQRCode()
{
	//char szTempPath[MAX_PATH] = { 0 };
	//char szPicPath[MAX_PATH] = { 0 };

	//CImage image;
	//CRect rect;

	//GetCurrentDirectoryW(MAX_PATH, (LPWSTR)szTempPath);
	//sprintf_s(szPicPath, "%s%s", szTempPath, "QRCode.png");
	//// HWND hDlg = ::GetDlgItem(hWnd, IDD_DIALOG1);
	//HWND hDlg = ::FindWindowW(NULL, L"΢�ű���2.9.5.56");
	//HWND hPic = GetDlgItem(hDlg, IDC_QRSTATIC);
	//// HDC hDc = ::GetDC(hWnd);
	//// HDC hDc = GetWindowDC(hWnd);
	//HDC hDc = GetDC(hPic);
	//GetClientRect(hPic, &rect);
	//image.Load((LPCTSTR)szPicPath);
	//image.Draw(hDc, rect);
	//
	//ReleaseDC(hPic, hDc);
	//image.Destroy();
	// char szTempPath[MAX_PATH] = { 0 };
	LPCTSTR szPicPath = _T("E:\\SourceCode\\WxPcHook\\bin\\WXQRCode.png");

	CImage image;
	CRect rect;
	HRESULT hResult;
	HWND hDlg = ::FindWindowW(NULL, L"΢�ű���3.0.1");
	HWND hPic = GetDlgItem(hDlg, IDC_QRPICTURESTATIC);
	DWORD dwRet = GetLastError();
	HDC hDc = GetDC(hPic);
	GetClientRect(hPic, &rect);
	hResult = image.Load(szPicPath);
	if (FAILED(hResult))
	{
		showDbgInfo(L"ShowQRCodePic->����ͼƬʧ��", L"��ʾ");
	}

	hResult = image.Draw(hDc, rect);
	if (FAILED(hResult))
	{
		showDbgInfo(L"ShowQRCodePic->��ͼʧ��", L"��ʾ");
	}
	ReleaseDC(hPic, hDc);
	image.Destroy();
}

void RefreshQrcode()
{
	// HookQrCode();
	// Sleep(100);
	GotoQrCode();
	// ��ȡ��Կ
	// HookDBPwd();
}

/**************��ȡ������Կ***************/
DWORD dwOverCall = (DWORD)GetModuleHandleW(L"WeChatWin.dll") + BACKUPKEY1;
DWORD dwRetAddr = (DWORD)GetModuleHandleW(L"WeChatWin.dll") + DBHOOKADDR + 0x5;
DWORD dwPwdPrt = 0;
DWORD dwPwdLen = 0;

void  __declspec(naked) SendPwd()
{
	__asm	pushad
	__asm   mov dwPwdPrt, edx
	__asm   mov dwPwdLen, eax

	SavePwd(dwPwdPrt, dwPwdLen);
	__asm	popad
	__asm call dwOverCall;
	//��ת�����ص�ַ
	__asm jmp dwRetAddr;
}


void HookDBPwd()
{
	DWORD dwHookAddr = (DWORD)GetModuleHandleW(L"WeChatWin.dll") + DBHOOKADDR;
	InlineHook(dwHookAddr, SendPwd);
}

void SavePwd(DWORD dwPwdPrt, DWORD dwPwdLen)
{
	if (dwPwdLen == 0x20)
	{
		char szTempPath[MAX_PATH] = { 0 };
		char szPwdPath[MAX_PATH] = { 0 };
		FILE* pFile = NULL;

		GetCurrentDirectoryW(MAX_PATH, (LPWSTR)szTempPath);
		sprintf_s(szPwdPath, "%s%s", szTempPath, "wechatpwd.bin");
		fopen_s(&pFile,szPwdPath, "ab");
		fwrite((const void*)dwPwdPrt, 1, dwPwdLen, pFile);
		fclose(pFile);
	}
}

void NewMobToComp()
{
	DWORD dwCall1 = weChatWinAddr + CONNECTBACKUP1;
	DWORD dwCall2 = weChatWinAddr + CONNECTBACKUP2;
	DWORD dwCall3 = weChatWinAddr + CONNECTBACKUP3;
	DWORD dwCall4 = weChatWinAddr + CONNECTBACKUP4;

	__asm {
		pushad;
		push 0x0;
		push 0x0;
		call dwCall1;
		mov ecx, eax;
		call dwCall2;
		mov eax, 0x1;
		push 0x0;
		cdq;
		push edx;
		push eax;
		push 0x275C;
		push 0x4E20;
		call dwCall3;
		mov ecx, eax;
		call dwCall4;
		popad;
	}
}

void InitFun()
{
	weChatWinAddr = (DWORD)getWeChatDLLAddr();
}