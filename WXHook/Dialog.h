#pragma once
#include "framework.h"

// ���úͻ�ȡȫ�־��
void setGlobalHwnd(HWND hWnd);
HWND getGlobalHwnd();

// ���ش���==��δ�õ�����ʱ����
void hideWindow();

//��ʾ����
DWORD WINAPI ShowDialog(HMODULE hModule);
INT_PTR CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);