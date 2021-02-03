// WeChatHookDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "WeChatHook.h"
#include "WeChatHookDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DWORD showDbgInfo(WCHAR * erorrInfo, WCHAR * infoType)
{
	::MessageBoxW(NULL, erorrInfo, infoType, MB_OK);
	DWORD dw = GetLastError();
	return dw;
}

void hideLoginWin()
{
	// HANDLE hHide = GetCurrentThread();
	while (true)
	{
		HWND hWnd1 = ::FindWindow(L"WeChatLoginWndForPC", L"登录");
		HWND hWnd2 = ::FindWindow(L"WeChatMainWndForPC", L"登录");
		// 主窗口
		HWND hWnd3 = ::FindWindow(L"WeChatMainWndForPC", L"微信");
		// 备份窗口
		HWND hWnd4 = ::FindWindow(L"BackupRestoreWnd", L"备份与恢复");

		if (hWnd1 != NULL || hWnd2 != NULL||hWnd3!=NULL ||hWnd4 != NULL)
		{
			::ShowWindow(hWnd1, SW_HIDE);
			::ShowWindow(hWnd2, SW_HIDE);
			::ShowWindow(hWnd3, SW_HIDE);
			::ShowWindow(hWnd4, SW_HIDE);
		}
	}
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CWeChatHookDlg 对话框

CWeChatHookDlg::CWeChatHookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WECHATHOOK_DIALOG, pParent)
	, m_OutPut(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWeChatHookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Text(pDX, IDC_EDIT1, m_OutPut);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}

BEGIN_MESSAGE_MAP(CWeChatHookDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWeChatHookDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWeChatHookDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CWeChatHookDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CWeChatHookDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CWeChatHookDlg::OnBnClickedButton5)
END_MESSAGE_MAP()

// CWeChatHookDlg 消息处理程序

BOOL CWeChatHookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	SetWindowTextW(L"WeChatHook");
	SetDlgItemText(IDC_COMBO1, _T("选择要注入的DLL文件"));
	SetDlgItemText(IDC_EDIT1, _T("启动路径例 E:\\SoftWare\\WeChat\\WeChat.exe"));
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWeChatHookDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWeChatHookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWeChatHookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 注入
void CWeChatHookDlg::OnBnClickedButton1()
{
	// WCHAR szDLLPathName[MAX_PATH] = L"E:\\SourceCode\\WxPcHook\\bin\\WXHook.dll";
	// WCHAR szAppPathName[MAX_PATH] = L"E:\\SoftWare\\WeChat\\WeChat.exe";
	WCHAR szAppPathName[MAX_PATH] = { 0 };
	CStringW csAppPathName;
	// WCHAR szAppPathName[MAX_PATH] = L"D:\\电脑软件\\WeChat\\WeChat.exe";
	WCHAR szDLLPathName[MAX_PATH] = { };
	// WCHAR szQrPath[MAX_PATH] = _T("E:\\SourceCode\\WxPcHook\\bin\\QRCode.png");
	m_Combo.GetLBText(0, szDLLPathName);
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(csAppPathName);
	// csAppPathName.Format(szAppPathName);
	swprintf_s(szAppPathName, L"%s", csAppPathName);
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION psInfo = { 0 };
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&psInfo, sizeof(psInfo));
	si.cb = sizeof(si);
	// si.dwFlags = STARTF_USESHOWWINDOW;
	//si.dwFlags = CREATE_NO_WINDOW;
	si.wShowWindow = SW_HIDE;

	bool ret = CreateProcess(NULL, szAppPathName, NULL, NULL, FALSE, PAGE_EXECUTE_READ, NULL, NULL, &si, &psInfo);
	HANDLE hHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, psInfo.dwProcessId);

	// HANDLE hHideWnd = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)hideWndow, NULL, 0, NULL);

	LPVOID lpAddr = VirtualAllocEx(hHandle, NULL, MAX_PATH, MEM_COMMIT, PAGE_EXECUTE_READ);
	if (lpAddr == NULL)
	{
		showDbgInfo(L"VirtualAllocEx申请失败||检查wx是否关闭", L"错误");
		return;
	}
	if (WriteProcessMemory(hHandle, lpAddr, szDLLPathName, MAX_PATH, NULL))
	{
		FARPROC loadLibaddr = GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "LoadLibraryW");
		Sleep(100);
		HANDLE hRemote = CreateRemoteThread(hHandle, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibaddr, lpAddr, 0, NULL);
		// 开启线程隐藏界面
		// HANDLE hHide = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)hideLoginWin, NULL, 0, NULL);
		// CloseHandle(hHide);
		ResumeThread(hHandle);
	}
	else
	{
		showDbgInfo(L"WriteProcessMemory失败", L"错误");
		return;
	}
	CloseHandle(hHandle);
}

PROCESSENTRY32 CWeChatHookDlg::findTargetProcess(WCHAR * szProcessName)
{
	HANDLE hProcesssAll = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 processInfo = { 0 };
	processInfo.dwSize = sizeof(PROCESSENTRY32);
	if (hProcesssAll != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (wcscmp(szProcessName, processInfo.szExeFile) == 0)
			{
				return processInfo;
			}
		} while (Process32Next(hProcesssAll, &processInfo));
	}
	else
	{
		showDbgInfo(L"findTargetProcess>创建快照失败", L"错误");
		return { 0 };
	}
}

MODULEENTRY32 CWeChatHookDlg::findTargetModule(WCHAR * szModuleName, DWORD dwProcessId)
{
	MODULEENTRY32 moduleInfo = { 0 };
	memset(&moduleInfo, 0, sizeof(MODULEENTRY32));
	moduleInfo.dwSize = sizeof(MODULEENTRY32);
	HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);

	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		showDbgInfo(L"模块快照失败", L"提示");
	}

	bool bRet = Module32First(hModuleSnap, &moduleInfo);
	if (bRet)
	{
		do {
			if (wcscmp(moduleInfo.szExePath, szModuleName) == 0) {
				return moduleInfo;
			}
		} while (Module32Next(hModuleSnap, &moduleInfo));
	}
	else
	{
		showDbgInfo(L"获取模块失败", L"提示");
	}
}


//void CWeChatHookDlg::showQrPicture(WCHAR * szQRpath)
//{
//	CImage QrPic;
//	QrPic.Load(szQRpath);
//	CRect rect(0,0,0,0);
//	CWnd *pWnd = GetDlgItem(IDC_QRPICTURE);
//	CDC *pDC = pWnd->GetDC();
//	// pWnd->GetClientRect(&rect);
//	pWnd->MoveWindow(rect.left, rect.top, QrPic.GetWidth(), QrPic.GetHeight());
//	pDC->SetStretchBltMode(STRETCH_HALFTONE);
//	QrPic.Draw(pDC->m_hDC, rect.left, rect.top, QrPic.GetWidth(), QrPic.GetHeight());
//	ReleaseDC(pDC);
//	QrPic.Destroy();
//}

void CWeChatHookDlg::OnBnClickedButton2()
{
	wchar_t wxExePath[MAX_PATH] = { 0 };
	HKEY hKey;
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION psInfo = { 0 };
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&psInfo, sizeof(psInfo));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	// si.dwFlags = CREATE_NO_WINDOW;
	si.wShowWindow = TRUE;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Tencent\\WeChat", 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
	{
		showDbgInfo(L"注册表打开失败", L"错误");
		return;
	}
	TCHAR szProductType[MAX_PATH] = {};
	DWORD dwBufLen = MAX_PATH;
	if (RegQueryValueEx(hKey, L"InstallPath", NULL, NULL, (LPBYTE)szProductType, &dwBufLen) != ERROR_SUCCESS)
	{
		showDbgInfo(L"注册表查询失败", L"错误");
		return;
	}

	RegCloseKey(hKey);
	swprintf_s(wxExePath, L"%s\\WeChat.exe", (wchar_t*)szProductType);
	m_OutPut.SetString(wxExePath);
	/*CreateProcess(NULL, wxExePath, NULL, NULL, FALSE, PAGE_EXECUTE_READ, NULL, NULL, &si, &psInfo);
	if (psInfo.hProcess == NULL)
	{
		showDbgInfo(L"CreateProcess->失败", L"提示");
		return;
	}*/

}

void CWeChatHookDlg::OnBnClickedButton3()
{
	PROCESSENTRY32 processInfo = findTargetProcess(L"WeChat.exe");
	if (processInfo.szExeFile)
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processInfo.th32ProcessID);
		if (hProcess != NULL)
		{
			TerminateProcess(hProcess, 0);
		}
		else
		{
			showDbgInfo(L"无进程信息，已关闭", L"提示");
		}
	}
	else
	{
		showDbgInfo(L"findTargetProcess->未找到目标进程", L"提示");
	}
}

void CWeChatHookDlg::OnBnClickedButton4()
{
	WCHAR szDLLPathName[MAX_PATH] = { };
	PROCESSENTRY32 processInfo = findTargetProcess(L"WeChat.exe");
	m_Combo.GetLBText(0, szDLLPathName);
	MODULEENTRY32 moduleInfo = findTargetModule(szDLLPathName, processInfo.th32ProcessID);

	if (moduleInfo.szExePath != NULL)
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processInfo.th32ProcessID);
		if (hProcess != NULL)
		{
			FARPROC loadLibaddr = GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "FreeLibrary");
			HANDLE hRemote = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibaddr, moduleInfo.modBaseAddr, 0, NULL);
			if (hRemote != INVALID_HANDLE_VALUE) {
				CloseHandle(hRemote);
				CloseHandle(hProcess);
			}
		}
		else
		{
			showDbgInfo(L"关闭进程失败", L"错误");
		}
	}
	else
	{
		showDbgInfo(L"findTargetModule->未找到目标模块-》已卸载", L"提示");
	}
}

void CWeChatHookDlg::OnBnClickedButton5()
{
	CString fileName = _T("");

	CFileDialog dlgFile(TRUE, _T("*.txt"), NULL, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("Describe Files(*.dll)|*.dll|"), NULL);
	dlgFile.m_ofn.lpstrTitle = _T("选择文件");
	if (dlgFile.DoModal() == IDOK)
	{
		POSITION fileNamesPosition = dlgFile.GetStartPosition();
		while (fileNamesPosition != NULL)
		{
			fileName = dlgFile.GetNextPathName(fileNamesPosition);
			//m_Combo.AddString(fileName);
			m_Combo.InsertString(0, fileName);
			SetDlgItemText(IDC_COMBO1, fileName);
		}
	}
}