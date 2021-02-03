#pragma once
#include "framework.h"

// 设置和获取全局句柄
void setGlobalHwnd(HWND hWnd);
HWND getGlobalHwnd();

// 隐藏窗口==》未用到，暂时保留
void hideWindow();

//显示窗口
DWORD WINAPI ShowDialog(HMODULE hModule);
INT_PTR CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);