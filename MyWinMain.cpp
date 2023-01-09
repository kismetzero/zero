#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

LRESULT CALLBACK WindowProc(	// ���ڴ������ڹ��̣����� ����
	HWND hwnd,					// hwnd �Ǵ��ڵľ����
	UINT uMsg,					// uMsg ����Ϣ���롣
	WPARAM wParam,				// wParam �� lParam ��������Ϣ��ص��������ݡ�
	LPARAM lParam				// wParam �� lParam ��������Ϣ��ص��������ݡ�
);

int WINAPI wWinMain(						// WINAPI �ǵ���Լ����		wWinMain ������ WinMain ��ͬ��wWinMain�����в�����Ϊ Unicode �ַ�������
	_In_ HINSTANCE hInstance,				// hInstance ��Ϊ��ʵ���������ģ��������
	_In_opt_ HINSTANCE hPrevInstance,		// hPrevInstance û�����塣 ���� 16 λWindows��ʹ�ã�������ʼ��Ϊ�㡣
	_In_ PWSTR pCmdLine,					// pCmdLine ���������в�����Ϊ Unicode �ַ�����
	_In_ int nCmdShow						// nCmdShow ��һ����־��ָʾ��Ӧ�ó��򴰿�����С������󻯻���������ʾ��
)
{
	// Register the window class.
	// ע�ᴰ���ࡣ
	const TCHAR CLASS_NAME[] = TEXT("My Test Window Class");	// ��������

	WNDCLASS wndClass = { };				// ���������ಢ��ʼ��Ϊ��

	wndClass.lpfnWndProc = WindowProc;		// lpfnWndProc ��ָ����Ϊ ���ڹ��� ��Ӧ�ó����庯����ָ�롣WindowProc �Ǵ��ڴ�������
	wndClass.hInstance = hInstance;			// hInstance ��Ӧ�ó���ʵ���ľ����
	wndClass.lpszClassName = CLASS_NAME;	// lpszClassName �Ǳ�ʶ��������ַ�����

	wndClass.style = CS_HREDRAW | CS_VREDRAW;			// ��������ʽ
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// ��������

	RegisterClass(&wndClass);				// �����ϵͳע�ᴰ���ࡣ

	// Create the window.
	// �������ڡ�
	HWND hwnd = CreateWindowEx(			// �������ں����������´��ڵľ�� hwnd ��
		0,                              // Optional window styles.	��ѡ������ʽ��
		CLASS_NAME,                     // Window class				������
		TEXT("�ҵĵ�һ��Win����"),		// Window text				�����ı�������
		WS_OVERLAPPEDWINDOW,            // Window style				������ʽ

		// Size and position	λ�úʹ�С	X, Y, nWidth, nHeight,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window				������
		NULL,       // Menu							���ڵĲ˵�
		hInstance,  // Instance handle				ʵ�����
		NULL        // Additional application data	����Ӧ�ó�������
	);

	if (hwnd == NULL)	// �жϴ����Ƿ񴴽��ɹ�
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);		// ��ʾ���ڣ� nCmdShow ������������С������󻯴��ڡ�

	// Run the message loop.
	// ������Ϣѭ����
	MSG msg = { };								// msg �ṹ,���������̵߳���Ϣ���е���Ϣ��Ϣ��
	while (GetMessage(&msg, NULL, 0, 0) > 0)	// GetMessage �����Ӷ�����ȡ��Ϣ��
	{
		TranslateMessage(&msg);					// ��������Կ��Ϣת��Ϊ�ַ���Ϣ��
		DispatchMessage(&msg);					// ����Ϣ���ȵ����ڹ��� WindowProc ��
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

			int flag = MessageBox(NULL, TEXT("�Ƿ��˳�������"), TEXT("�˳�ȷ�ϣ�"), MB_YESNOCANCEL);
			if (flag == IDOK || flag == IDYES)
			{
				DestroyWindow(hwnd);	// ����ָ���Ĵ��ڡ�
			}
		}
		return 0;

	case WM_DESTROY:
		{
//			WCHAR testStr2[] = TEXT("MyTestWindows: in WM_DESTROY \n");
//			OutputDebugString(testStr2);

			PostQuitMessage(0);		// ��ϵͳָʾ�߳��ѷ�����ֹ (�˳�) ������
		}
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.
			// ���л��ƶ�������BeginPaint��EndPaint֮�䡣

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);
		}
		return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// ����Ĭ�ϴ��ڹ��̣�ΪӦ�ó���δ������κδ�����Ϣ�ṩĬ�ϴ���
}