#pragma once
#include "framework.h"
// #include "OffsetAddr2.9.5.h"
#include "OffsetAddr3_2_1.h"


DWORD showDbgInfo(const wchar_t* erorrInfo, const wchar_t* infoType);
// int CDECL MessageBoxPrintf(const char* szCaption, const char* szFormat, ...);


// 获取WeChatWin.dll模块地址
HMODULE getWeChatDLLAddr();

// 跳转到二维码登录
void GotoQrCode();

void InlineHook(DWORD dwHookAddr, LPVOID pFunAddr);

void HookWxQRCode();
// 获取二维码链接 没用到
void getQrCodeLink();

//判断是否是登录状态
DWORD IsUserLogin();

// 获取登录状态
DWORD getLoginStatus();

// 跳到一键备份
void gotoBackupBtn();

// 手机聊天备份至电脑==> 未更新
void mbBackupToCom();

// 保存二维码数据
DWORD SaveQRCodeData(DWORD * QrPtr, DWORD dwSize);

// 显示图片
void ShowQRCode();

// 刷新二维码
void RefreshQrcode();

/******获取备份是返回的密钥*****/
void HookDBPwd();
void SavePwd(DWORD dwPwdPrt, DWORD dwPwdLen);

// 新的手机备份到电脑函数
void NewMobToComp();

// 初始化函数
void InitFun();