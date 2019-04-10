// BlockChainDemo.cpp : 定义应用程序的入口点。
/*
    类简介:实现一个简单的区块链的demo
    1.弹出一个窗口（两个按钮 一个图）
    2.创建线程池
    3.一个线程绑定一个用户
    4.用户(线程)之间随机进行交易
    5.其他线程进行校验
*/
#include "stdafx.h"
#include "BlockChainDemo.h"
#include "sha256.h"
#include "CStr.h"

#define MAX_LOADSTRING 100
#define IDB_ADD 1101
#define IDB_DEL 1102
#define IDB_START 1103

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND hWnd,hAnd,hDnd,hSnd;                       //窗口句柄和按钮的句柄

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
POINT FindNextPosByAHMDSpiral(int index, int step, int x = 0, int y = 0,int direction = 0);
void DrawCircle(HDC hDC, int x, int y, int len, COLORREF color);

struct User
{
    POINT p;
    HANDLE hThread;
    double btc;
    wstring acceptMessage; //接受消息
    wstring publicKey;
    wstring privateKey;
};
vector<User> users;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
    
    //初始化线程池

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BLOCKCHAINDEMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

    
	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BLOCKCHAINDEMO));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int) msg.wParam;
}

DWORD WINAPI MyFunc(LPVOID lpParam)
{
    User* user = (User*)lpParam;
    /*while(user)
    {
        int size = (int)user->acceptMessage.size();
        if(size > 0) //处理接受的消息
        {
            //处理逻辑
            ::Sleep(1000);
            
        }
        else//没事干,考虑去交易一波
        {
            bool hasMood = rand()%2 == 0 ? false : true;
            if(hasMood)
            {
                size = (int)users.size();
                //users[size];
            }
            ::Sleep(1000);
        }

    }*/
    //pthread_mutex_lock(&m_mutex);
    //要做的事情
    
    

    //pthread_mutex_unlock(&m_mutex);
    //sleep();
    return 0;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLOCKCHAINDEMO));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= CreateSolidBrush(RGB(3, 9, 60));//(HBRUSH)GetStockObject(BLACK_BRUSH);//(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;//MAKEINTRESOURCE(IDC_BLOCKCHAINDEMO);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassEx(&wcex);
}
/*颜色：244,254,239
        252,255,250(最亮)
*/


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   wstring str = L"BlockChain";
   hWnd = CreateWindow(L"BlockChainDemo", str.c_str(), WS_OVERLAPPEDWINDOW,
      448, 156, 1024, 768, NULL, NULL, hInstance, NULL);

   hAnd = CreateWindow(L"Button", L"新  增", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  
    852, 20, 120, 40, hWnd, (HMENU)IDB_ADD, hInst, NULL);  
   hDnd = CreateWindow(L"Button", L"删  除", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  
    852, 80, 120, 40, hWnd, (HMENU)IDB_DEL, hInst, NULL);  
   hSnd = CreateWindow(L"Button", L"开  始", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  
    852, 600, 120, 40, hWnd, (HMENU)IDB_START, hInst, NULL);
   HFONT hFont = CreateFont(-18, -9, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
    , OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, _T("微软雅黑"));
   SendMessage(hAnd, WM_SETFONT, (WPARAM)hFont, NULL);
   SendMessage(hDnd, WM_SETFONT, (WPARAM)hFont, NULL);
   SendMessage(hSnd, WM_SETFONT, (WPARAM)hFont, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, SW_SHOW);
   UpdateWindow(hWnd);
   
   return TRUE;
}

DWORD WINAPI RegisterUser(LPVOID lpParam)
{
    int count = 0,type = 0;
    while(count < 400)
    {
        count++;
        if(count - type * 50 > 75)
	    ::GetClientRect(hWnd, &rect);
        ::InvalidateRect(hWnd, &rect, true);
        Sleep(50);
    }
    return 0;
}

/*
index 点的下标
step 步长
x 原点的x 
y 原点的y
direction方向(4个方向一个方向两种 共8种)
    下左上  下右上
    左上右  右上左
    上右下  上左下
    右下左  左下右
*/
POINT FindNextPosByAHMDSpiral(int index, int step, int x, int y, int direction)//默认方向 下左上
{
    POINT nextPos,lastPos;
    if(index < 1)
    {
        //第一个点默认原点
        nextPos.x = x,nextPos.y = y;
    }
    else
    {
        lastPos.x = x,lastPos.y = y;//最后一个点的坐标
        int count = 1;//找第几个点
        while(count <= index)
        {
            if(count != 1)
            {
                lastPos.x = nextPos.x;
                lastPos.y = nextPos.y;
            }
            int sum = 1;
            int n = 0;
            while(count > sum)
            {
                sum += n + 1;
                n++;
            }
            int nextDir = n % 4;// 0:左下 1:左上 2:右上 3:右下
            if(direction < 4)
            {
                nextDir += direction;
            }
            else if (direction < 8)
            {
                int d = direction - 4;
                nextDir = abs(nextDir - 3);
                nextDir += d;
            }
            nextDir = nextDir >= 4 ? nextDir - 4 : nextDir;

            nextDir = 8 - nextDir;
            switch(nextDir)
            {
                case 0:
                    {
                        nextPos.x = lastPos.x - step / 2;
                        nextPos.y = lastPos.y + step / 2;
                        break;
                    }
                case 1:
                    {
                        nextPos.x = lastPos.x - step / 2;
                        nextPos.y = lastPos.y - step / 2;
                        break;
                    }
                case 2:
                    {
                        nextPos.x = lastPos.x + step / 2;
                        nextPos.y = lastPos.y - step / 2;
                        break;
                    }
                case 3:
                    {
                        nextPos.x = lastPos.x + step / 2;
                        nextPos.y = lastPos.y + step / 2;
                        break;
                    }
            }
            count++;
        }
    }
    return nextPos;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
        case IDB_ADD:
			//RegisterUser();
            ::CreateThread(NULL, 0, RegisterUser, 0, 0, NULL);
			break;
        case IDB_DEL:
			//DelBlock();
			break;
        case IDB_START:
			//StartDemo();
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
		    // TODO: 在此添加任意绘图代码...
            int size = (int)users.size();
            if(size > 0)
            {
                for(int i = 0; i < size; ++i)
                {
                    ::DrawCircle(hdc, users[i].p.x, users[i].p.y, 10, RGB(255,255,255)); 
                }
            }
		    EndPaint(hWnd, &ps);
		    break;
        }
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//绘制实心圆
void DrawCircle(HDC hDC, int x, int y, int len, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	HPEN hPen = CreatePen(PS_SOLID, 1, color);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	Ellipse(hDC, x-len/2, y-len/2, x+len/2, y+len/2);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hPen);

	SelectObject(hDC, hOldPen);
	DeleteObject(hOldBrush);
}