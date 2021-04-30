// WeChatHookDlg.h: 头文件
//

#pragma once
#include <Windows.h>
#include <TlHelp32.h>

DWORD showDbgInfo(WCHAR* erorrInfo, WCHAR* infoType);
// #define GOTOQRCODE  0x3BE730  //跳转到二维码界面;
// 隐藏登录窗口
void hideLoginWin();

// CWeChatHookDlg 对话框
class CWeChatHookDlg : public CDialogEx
{
	// 构造
public:
	CWeChatHookDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WECHATHOOK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 注入微信
	afx_msg void OnBnClickedButton1();
	// 启动微信
	afx_msg void OnBnClickedButton2();
	// 关闭微信
	afx_msg void OnBnClickedButton3();
	// 卸载DLL文件
	afx_msg void OnBnClickedButton4();
	// 浏览选取文件
	afx_msg void OnBnClickedButton5();
public:
	void CString2Char(CString str, char ch[]);

	// 寻找目标进程
	PROCESSENTRY32 findTargetProcess(WCHAR* szProcessName);

	// 寻找指定的模块
	MODULEENTRY32 findTargetModule(WCHAR* szModuleName, DWORD dwProcessId);

	// 显示放在dll里
	// void showQrPicture(WCHAR* szQRpath);

	// 使用 ZwCreateThreadEx 实现远线程注入
	BOOL ZwCreateThreadExInjectDll(DWORD dwProcessId, WCHAR *pszDllFileName);

	// 提权
	BOOL EnbalePrivileges(HANDLE hProcess, WCHAR *pszPrivilegesName);

private:
	// 组合框显示dll路径
	CComboBox m_Combo;
public:
	// CStatic m_QrPicture;
	// 输出一些信息
	CString m_OutPut;
	CEdit m_Edit;
	// 获取输入的进程id
	CString m_EditPid;

};