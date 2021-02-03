#include "pch.h"
#include "Dialog.h"
#include "hook.h"
// #include "Resource.h"
#include "resource1.h"

HWND globalHWnd;

void setGlobalHwnd(HWND hWnd)
{
	globalHWnd = hWnd;
}

HWND getGlobalHwnd()
{
	return globalHWnd;
}

void hideWindow()
{
	while (true)
	{
		// ������
		HWND hWnd1 = ::FindWindowW(L"WeChatMainWndForPC", L"΢��");
		// ���ݴ���
		HWND hWnd2 = ::FindWindowW(L"BackupRestoreWnd", L"������ָ�");
		if (hWnd2 != NULL)
		{
			ShowWindow(hWnd1, SW_HIDE);
			ShowWindow(hWnd2, SW_HIDE);
		}
	}
}


DWORD WINAPI ShowDialog(HMODULE hModule)
{
	::DialogBoxA(hModule, (LPCSTR)MAKEINTRESOURCE(IDD_WXBACKUPDLG), NULL, &DialogProc);
	return TRUE;
}


// �ص�
INT_PTR CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_REFRESHQRCODEBTN:
		{
			if (getLoginStatus() == 0)
			{
				// ��ά��ʧЧ�� ˢ��
				HookWxQRCode();
				// RefreshQrcode();
				GotoQrCode();
				Sleep(0x100);
				ShowQRCode();
				return TRUE;
			}
			else if (getLoginStatus() == 1)
			{
				MessageBoxW(NULL, L"��½��...", L"����", MB_OK);
				return false;
			}
			else if (getLoginStatus() == 2)
			{
				MessageBoxW(NULL, L"�ѵ�¼", L"����", MB_OK);
				return false;
			}
			
		}
		break;
		case IDC_LOGINSTATUSBTN:
		{
			IsUserLogin();
			return true;
		}
		break;
		case IDC_BACKUPBTN:
		{

			if (getLoginStatus() == 0 || getLoginStatus() == 1)
			{
				MessageBoxW(NULL, L"���ȵ�¼", L"��ʾ", MB_OK);
				return false;
			}
			else
			{
				// gotoBackupBtn();
				// Sleep(200);
				// mbBackupToCom();
				HookDBPwd();
				Sleep(0x50);
				NewMobToComp();
				return true;
			}

		}
		break;
		default:
			break;
		}
		break;
	}

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		break;
	}
	return (INT_PTR)FALSE;
}