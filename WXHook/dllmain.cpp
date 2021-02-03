// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "Dialog.h"
#include "hook.h"



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		// 获取dll基址
		InitFun();

		// 创建窗口
		HANDLE hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ShowDialog, hModule, 0, NULL);
		Sleep(100);
		// 直接显示二维码
		// refreshQrcode();
		if (hThread2 != 0 || hThread2 != 0) {
			CloseHandle(hThread2);
		}
		else
		{
			// showDbgInfo(L"创建线程失败", L"error");
		}
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
