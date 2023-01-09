#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

LRESULT CALLBACK WindowProc(	// 窗口处理（窗口过程）函数 声明
	HWND hwnd,					// hwnd 是窗口的句柄。
	UINT uMsg,					// uMsg 是消息代码。
	WPARAM wParam,				// wParam 和 lParam 包含与消息相关的其他数据。
	LPARAM lParam				// wParam 和 lParam 包含与消息相关的其他数据。
);

int WINAPI wWinMain(						// WINAPI 是调用约定。		wWinMain 函数与 WinMain 相同，wWinMain命令行参数作为 Unicode 字符串传递
	_In_ HINSTANCE hInstance,				// hInstance 称为“实例句柄”或“模块句柄”。
	_In_opt_ HINSTANCE hPrevInstance,		// hPrevInstance 没有意义。 它在 16 位Windows中使用，但现在始终为零。
	_In_ PWSTR pCmdLine,					// pCmdLine 包含命令行参数作为 Unicode 字符串。
	_In_ int nCmdShow						// nCmdShow 是一个标志，指示主应用程序窗口是最小化、最大化还是正常显示。
)
{
	// Register the window class.
	// 注册窗口类。
	const TCHAR CLASS_NAME[] = TEXT("My Test Window Class");	// 窗口类名

	WNDCLASS wndClass = { };				// 声明窗口类并初始化为空

	wndClass.lpfnWndProc = WindowProc;		// lpfnWndProc 是指向名为 窗口过程 的应用程序定义函数的指针。WindowProc 是窗口处理函数。
	wndClass.hInstance = hInstance;			// hInstance 是应用程序实例的句柄。
	wndClass.lpszClassName = CLASS_NAME;	// lpszClassName 是标识窗口类的字符串。

	wndClass.style = CS_HREDRAW | CS_VREDRAW;			// 窗口类样式
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// 窗口类光标

	RegisterClass(&wndClass);				// 向操作系统注册窗口类。

	// Create the window.
	// 创建窗口。
	HWND hwnd = CreateWindowEx(			// 创建窗口函数，返回新窗口的句柄 hwnd 。
		0,                              // Optional window styles.	可选窗口样式。
		CLASS_NAME,                     // Window class				窗口类
		TEXT("我的第一个Win程序"),		// Window text				窗口文本标题栏
		WS_OVERLAPPEDWINDOW,            // Window style				窗口样式

		// Size and position	位置和大小	X, Y, nWidth, nHeight,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window				父窗口
		NULL,       // Menu							窗口的菜单
		hInstance,  // Instance handle				实例句柄
		NULL        // Additional application data	其他应用程序数据
	);

	if (hwnd == NULL)	// 判断窗口是否创建成功
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);		// 显示窗口， nCmdShow 参数可用于最小化或最大化窗口。

	// Run the message loop.
	// 运行消息循环。
	MSG msg = { };								// msg 结构,包含来自线程的消息队列的消息信息。
	while (GetMessage(&msg, NULL, 0, 0) > 0)	// GetMessage 函数从队列拉取消息。
	{
		TranslateMessage(&msg);					// 将虚拟密钥消息转换为字符消息。
		DispatchMessage(&msg);					// 将消息调度到窗口过程 WindowProc 。
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		{
//			WCHAR testStr1[] = TEXT("MyTestWindows: in WM_CLOSE \n");
//			OutputDebugString(testStr1);

			int flag = MessageBox(NULL, TEXT("是否退出本程序"), TEXT("退出确认！"), MB_YESNOCANCEL);
			if (flag == IDOK || flag == IDYES)
			{
				DestroyWindow(hwnd);	// 销毁指定的窗口。
			}
		}
		return 0;

	case WM_DESTROY:
		{
//			WCHAR testStr2[] = TEXT("MyTestWindows: in WM_DESTROY \n");
//			OutputDebugString(testStr2);

			PostQuitMessage(0);		// 向系统指示线程已发出终止 (退出) 的请求。
		}
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.
			// 所有绘制都发生在BeginPaint和EndPaint之间。

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);
		}
		return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// 调用默认窗口过程，为应用程序未处理的任何窗口消息提供默认处理。
}