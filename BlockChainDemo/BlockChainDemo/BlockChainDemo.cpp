// BlockChainDemo.cpp : ����Ӧ�ó������ڵ㡣
/*
    ����:ʵ��һ���򵥵���������demo
    1.����һ�����ڣ�������ť һ��ͼ��
    2.�����̳߳�
    3.һ���̰߳�һ���û�
    4.�û�(�߳�)֮��������н���
    5.�����߳̽���У��
*/
#include "stdafx.h"
#include "BlockChainDemo.h"
#include "sha256.h"
#include "CStr.h"

#define MAX_LOADSTRING 100
#define IDB_ADD 1101
#define IDB_DEL 1102
#define IDB_START 1103

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND hWnd,hAnd,hDnd,hSnd;                       //���ھ���Ͱ�ť�ľ��

// �˴���ģ���а����ĺ�����ǰ������:
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
    wstring acceptMessage; //������Ϣ
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
    
    //��ʼ���̳߳�

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BLOCKCHAINDEMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

    
	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BLOCKCHAINDEMO));

	// ����Ϣѭ��:
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
        if(size > 0) //������ܵ���Ϣ
        {
            //�����߼�
            ::Sleep(1000);
            
        }
        else//û�¸�,����ȥ����һ��
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
    //Ҫ��������
    
    

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
/*��ɫ��244,254,239
        252,255,250(����)
*/


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   wstring str = L"BlockChain";
   hWnd = CreateWindow(L"BlockChainDemo", str.c_str(), WS_OVERLAPPEDWINDOW,
      448, 156, 1024, 768, NULL, NULL, hInstance, NULL);

   hAnd = CreateWindow(L"Button", L"��  ��", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  
    852, 20, 120, 40, hWnd, (HMENU)IDB_ADD, hInst, NULL);  
   hDnd = CreateWindow(L"Button", L"ɾ  ��", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  
    852, 80, 120, 40, hWnd, (HMENU)IDB_DEL, hInst, NULL);  
   hSnd = CreateWindow(L"Button", L"��  ʼ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  
    852, 600, 120, 40, hWnd, (HMENU)IDB_START, hInst, NULL);
   HFONT hFont = CreateFont(-18, -9, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
    , OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, _T("΢���ź�"));
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
index ����±�
step ����
x ԭ���x 
y ԭ���y
direction����(4������һ���������� ��8��)
    ������  ������
    ������  ������
    ������  ������
    ������  ������
*/
POINT FindNextPosByAHMDSpiral(int index, int step, int x, int y, int direction)//Ĭ�Ϸ��� ������
{
    POINT nextPos,lastPos;
    if(index < 1)
    {
        //��һ����Ĭ��ԭ��
        nextPos.x = x,nextPos.y = y;
    }
    else
    {
        lastPos.x = x,lastPos.y = y;//���һ���������
        int count = 1;//�ҵڼ�����
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
            int nextDir = n % 4;// 0:���� 1:���� 2:���� 3:����
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
		// �����˵�ѡ��:
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
		    // TODO: �ڴ���������ͼ����...
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

//����ʵ��Բ
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