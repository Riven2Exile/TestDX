#include "stdafx.h"
#include "TestDX.h"
#include "CSprite.h"
#include <time.h>
#include "GameMain.h"
#include "Camera.h"
#include "YanZhengMa\YanZheng.h"
#include "SDKwavefile.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

IDirect3D9* g_pD3D9 = NULL;
D3DCAPS9 g_caps;    
int g_vp = 0;
D3DPRESENT_PARAMETERS g_d3dpp;

IDirect3DDevice9 *g_pDevice = NULL;
IDirect3DTexture9*  g_pTexture = NULL;

/// temp sound
IGraphBuilder *g_pGraph = NULL;
IGraphBuilder *g_pGraph2 = NULL;
IMediaControl *g_pControl = NULL;
IMediaControl *g_pControl2 = NULL;
IMediaEvent   *g_pEvent = NULL;
IDirectSound8  *g_Sound  = NULL;
DSBUFFERDESC  *g_DSBuffDesc = NULL;
IDirectSoundBuffer *g_DSBuff = NULL;



extern int g_nWidth = 1200;
extern int g_nHeight = 800;


// 图2
#define S_SIZE 20/*20*/
CSprite g_sprite[S_SIZE];   //精灵

CSprite g_spriteOffset; //偏移


struct Vertex
{
    float _x, _y, _z;
    float _nx, _ny, _nz;
    float _u, _v;
    static const DWORD FVF;

    Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v)
    {
        _x = x;
        _y = y;
        _z = z;
        _nx = nx;
        _ny = ny;
        _nz = nz;
        _u = u;
        _v = v;
    }
};

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

////// vertex2
struct Vertex2{
    float x, y, z;
    float rhw;
    DWORD color;
    float _u, _v;
    static const DWORD FVF;
    Vertex2(float xx, float yy, float zz, float r, DWORD col, float u, float v)
    {
        x = xx;
        y = yy;
        z = zz;
        rhw = r;
        color = col;
        _u = u;
        _v = v;
    }
};

const DWORD Vertex2::FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

////////////



IDirect3DVertexBuffer9* g_pVb;

IDirect3DVertexBuffer9 *g_pVb2;

CCamera g_camera;



// 启动
bool Setup()
{
    //g_pDevice->SetRenderState( D3DRS_SHADEMODE,D3DSHADE_FLAT ); //平面着色

    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
    g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    //g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);

    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    g_pDevice->SetRenderState(D3DRS_LIGHTING, false); //开灯?

    ////// 2 end

    //g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //填充为白   //如果是:D3DFILL_WIREFRAME（线框）的话, 纹理只会贴在线边框上

//     g_pDevice->SetTexture(0, g_pTexture);
    g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

//    g_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); //前面 背面都看

    // 材质?  (顶点结构默认没有材质属性.. 所以不会反射任何的光, 有光照的时候,  就变成黑色)
//     D3DMATERIAL9 material;
//     ZeroMemory(&material, sizeof(material));
//     g_pDevice->GetMaterial(&material);
// 
//     g_pDevice->SetRenderState(D3DRS_LIGHTING, false); //开灯?
//     D3DXMATRIX proj;
    


    //// !!! 设置矩阵 !!!


    //// 矩阵坐标先起 todo
    // 观察左边系
    D3DXMATRIXA16 view1;
//     D3DXVECTOR3 d1(0.f,0.f,-1.0f);
//     D3DXVECTOR3 d2(0.f,0.f,1.0f);
//     D3DXVECTOR3 d3(0.f,1.0f,0.f);
//     D3DXMatrixLookAtLH(&view1, &d1, &d2, &d3);
    g_camera.SetLookAt3Vecter(D3DXVECTOR3(0.f,0.f,-1.0f), 
                                D3DXVECTOR3(0.f,0.f,1000.0f), 
                                D3DXVECTOR3(0.f,1.0f,0.f));

    view1 = g_camera.GetLookAtMatrix();
    g_pDevice->SetTransform(D3DTS_VIEW, &view1);

    D3DXMATRIXA16 proj1; //3.10826
    D3DXMatrixPerspectiveFovLH(&proj1, 1.5707963, 1200/(float)800/*800/(float)600*/, 1.0f, 100.0f); // 90°
    g_pDevice->SetTransform(D3DTS_PROJECTION, &proj1);

//     D3DVIEWPORT9 vp = {0, 0, 800, 600, 0, 1};
//     g_pDevice->SetViewport(&vp);

    return true;
}



// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	HACCEL hAccelTable;


	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTDX, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTDX));

    //test
    int ntemp = sizeof(std::string);


    CGameMain& inst = CGameMain::Instance();
    inst.init();

    LARGE_INTEGER freq;
    DWORD f;
    float gettickcount = 0;
    QueryPerformanceFrequency(&freq);
    f= freq.LowPart/1000;

    LARGE_INTEGER start;
    LARGE_INTEGER end;
    LARGE_INTEGER endFrame;
    float forFrame = 0;
    const int nExFrame = 30; //期望帧数
    ::QueryPerformanceCounter(&start);
    int nFrame = 0; //帧数
    int nCalcTime = 0;  //累积流逝时间， 1秒后清除一些(清除1秒)
    int nExTimePerFrame = 1000 / (float)nExFrame;//期望每帧最多消耗时间(毫秒);
    BOOL bRef = TRUE;

    // 33毫秒一次
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));



	// Main message loop:
	while (/*GetMessage(&msg, NULL, NULL, NULL)*/msg.message != WM_QUIT)
	{
        
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
        else
        {
            bRef = ::QueryPerformanceCounter(&end);
            if (bRef == FALSE)
            {
                printf("时钟错误!!!!!!!!!!!!!\n");
            }
            float Felasped = ((end.QuadPart - start.QuadPart) / (float)freq.QuadPart) * 1000; //强转
            
            DWORD elasped = Felasped;
            if (elasped == 0)
            {
                elasped = 1; //修正
            }
            //printf("ss :%f  %d\n", Felasped, elasped);

            // windows消息的话，要在消息处理函数中进行处理

            // TODO: 游戏逻辑
            inst.update( elasped );

            inst.draw();

            
            // 帧数控制
            nCalcTime += elasped;
            ++nFrame;

            if (nCalcTime >= 1000)
            {
                nCalcTime -= 1000;
                // 打印帧数 --> 
                //printf("------------> Frame: %d\n", nFrame);

                nFrame = 0; //帧数置0
            }

            if (elasped < nExTimePerFrame)
            {
                //printf("sleep : %d   elasped:%d \n", nExTimePerFrame-elasped, elasped);
                ::Sleep(nExTimePerFrame-elasped+1);
            }
            else
            {
                //printf("%d \n", elasped);
                Sleep(1);
            }
           
            start.QuadPart = end.QuadPart;
        }
        
	}

	return (int) msg.wParam;
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTDX));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TESTDX);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

HWND g_hWnd = 0;

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    char szPath[MAX_PATH] = {0};
    GetModuleFileNameA(NULL, szPath, MAX_PATH);
    std::string strPath = szPath;
    int n = strPath.find_last_of('\\');
    strPath = strPath.substr(0, n+1);
    //strPath.Find()
    printf("位置: %s \n 目录: %s\n", szPath, strPath.c_str());
    ::SetCurrentDirectoryA(strPath.c_str());

    HWND hWnd;
    hInst = hInstance; // Store instance handle in our global variable

    ///// COM组件的初始化
    HRESULT hr /*= CoInitialize(NULL)*/;

#ifdef _DEBUG
    AllocConsole();
    freopen("CONOUT$", "w+t", stdout); // 重定向STDOUT 
    printf("*********start*********\n");
#endif


    RECT rc = {0,0,g_nWidth,g_nHeight};
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, TRUE);


    //////// 试着创建对话框!!
//     hWnd = CreateDialogA(hInstance, MAKEINTRESOURCEA(IDD_ABOUTBOX), NULL, WndProc);
//     LONG nLong = GetWindowLongA(hWnd,GWL_STYLE);
//     SetWindowLongA(hWnd, GWL_STYLE, nLong & (/*WS_OVERLAPPED |*/ WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX|WS_MAXIMIZEBOX/*|WS_CLIPCHILDREN|WS_CLIPSIBLINGS*/) );
//     
//     nLong = GetWindowLongA(hWnd, GWL_EXSTYLE);
//     SetWindowLongA(hWnd, GWL_EXSTYLE, nLong & (WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR));
// 
//     SetWindowPos(hWnd, NULL, 100, 100, g_nWidth, g_nHeight, SWP_SHOWWINDOW);
    
    


    hWnd = CreateWindow(szWindowClass, 
        szTitle, 
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 
        0, 
        rc.right-rc.left, 
        rc.bottom-rc.top, 
        NULL, 
        NULL, 
        hInstance,
        NULL);
    g_hWnd = hWnd;

    if (!hWnd)
    {
        return FALSE;
    }

	// 可以改变窗口风格
// 	LONG nLong = GetWindowLongA(hWnd,GWL_STYLE);
// 	SetWindowLongA(hWnd, GWL_STYLE, nLong & (/*WS_OVERLAPPED |*/ WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX|WS_MAXIMIZEBOX/*|WS_CLIPCHILDREN|WS_CLIPSIBLINGS*/) );
// 	
// 	nLong = GetWindowLongA(hWnd, GWL_EXSTYLE);
// 	SetWindowLongA(hWnd, GWL_EXSTYLE, nLong & (WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR));
// 	
// 	SetWindowPos(hWnd, NULL, 100, 100, g_nWidth, g_nHeight, SWP_SHOWWINDOW);


    // D3D的初始化
    g_pD3D9 = Direct3DCreate9( D3D_SDK_VERSION ); // 初始化 D3D接口
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.BackBufferWidth = g_nWidth;
    g_d3dpp.BackBufferHeight = g_nHeight;
    g_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; //pixel format  D3DFMT_A8R8G8B8
    g_d3dpp.BackBufferCount = 1;
    g_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    g_d3dpp.MultiSampleQuality = 0;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.hDeviceWindow = hWnd; // 窗口
    g_d3dpp.Windowed = true;   // 是否窗口化, false的话就是全屏
    g_d3dpp.EnableAutoDepthStencil = true; //开启深度缓存
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;  // depth format
    g_d3dpp.Flags = 0;
    g_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    ///// PerfHUD 支持
    UINT AdapterToUse=D3DADAPTER_DEFAULT; 
    D3DDEVTYPE DeviceType=D3DDEVTYPE_HAL; 
    for (UINT Adapter=0;Adapter<g_pD3D9->GetAdapterCount();Adapter++)  
    { 
        D3DADAPTER_IDENTIFIER9  Identifier; 
        HRESULT       Res; 

        Res = g_pD3D9->GetAdapterIdentifier(Adapter,0,&Identifier); 
        if (strstr(Identifier.Description,"PerfHUD") != 0) 
        { 
            printf("使用PerfHUD\n");
            AdapterToUse=Adapter; 
            DeviceType=D3DDEVTYPE_REF; 
            break; 
        } 
    } 


   //     if (FAILED(hr))
   //     {
   //         printf("ERROR - Could not initialize COM library");
   //         //return;
   //     }
   // Create the filter graph manager and query for interfaces.
   //     hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
   //         IID_IGraphBuilder, (void **)&g_pGraph);
   // 
   // 
   //     if (FAILED(hr))
   //     {
   //         printf("ERROR - Could not create the Filter Graph Manager.");
   //     }
   //     hr = g_pGraph->QueryInterface(IID_IMediaControl, (void **)&g_pControl);
   //     hr = g_pGraph->QueryInterface(IID_IMediaEvent, (void **)&g_pEvent);
   // 
   //     // Build the graph. IMPORTANT: Change this string to a file on your system.
   //     if (SUCCEEDED(hr)) // S_OK   VFW_S_AUDIO_NOT_RENDERED
   //     {
   //         // Run the graph.
   //         hr = g_pControl->Run();
   //         if (SUCCEEDED(hr))
   //         {
   //             // Wait for completion.
   //             long evCode;
   //             //g_pEvent->WaitForCompletion(INFINITE, &evCode);
   // 
   //             // Note: Do not use INFINITE in a real application, because it
   //             // can block indefinitely.
   //         }
   //     }
   //CoUninitialize();

	/////////// wav start //////////////
//     DirectSoundCreate8(NULL, &g_Sound, NULL);  //只能播放wav格式
//     DSBUFFERDESC desc;
//     ZeroMemory(&desc, sizeof(desc));
//     hr = g_Sound->SetCooperativeLevel(hWnd, DSSCL_NORMAL); //留着
// 
// 	CWaveFile wavFile;
// 	wavFile.QuickOpen(L"Wave/烟花.wav", desc.lpwfxFormat, WAVEFILE_READ, g_Sound, g_DSBuff);

   ///////////////////


   //实验cpp的#define
#ifdef REGISTRT_GUI
   printf("有定义REGISTRT_GUI\n");
#endif // REGISTRT_GUI

   // 创建设备
   hr = g_pD3D9->CreateDevice(
       AdapterToUse/*D3DADAPTER_DEFAULT*/, 
       DeviceType/*D3DDEVTYPE_HAL*/,
       hWnd,
       D3DCREATE_HARDWARE_VERTEXPROCESSING, //D3DCREATE_HARDWARE_VERTEXPROCESSING
       &g_d3dpp,
       &g_pDevice);

   if (FAILED(hr))
   {
       ::MessageBoxA(NULL, "CreateDevice fail", NULL, NULL);
   }


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
    // 
   
   CGameMain::Instance().SetWindowsHandle(hWnd);
   CGameMain::Instance().SetWndSize(rc.right-rc.left, rc.bottom-rc.top);
   CGameMain::Instance().SetPos(0, 0);

    // 读取纹理
 //   D3DXCreateTextureFromFileA(g_pDevice, "Riven_Splash_0.jpg", &g_pTexture);
//     D3DXCreateTextureFromFileExA(g_pDevice, "MyRes/Riven_Splash_0.jpg", D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,1, D3DUSAGE_DYNAMIC,D3DFMT_R8G8B8, 
//         D3DPOOL_DEFAULT, 
//         D3DX_FILTER_TRIANGLE, 
//         D3DX_FILTER_TRIANGLE, 
//         D3DCOLOR_ARGB(255,0,0,0), NULL, NULL, &g_pTexture);
    

    Setup();    //启动

    // 图2
//     g_sprite.LoadImage("SpinningPeas.png", g_pDevice);
//     g_sprite.SetX(500.f);
//     g_sprite.SetY(500.f);

    for (int i = 0 ; i < S_SIZE; i++)
    {
        g_sprite[i].LoadAImage("MyRes/fire.png", g_pDevice);
    }
    
    // 图3
    g_spriteOffset.LoadAImage("MyRes/0050鼓掌.tga", g_pDevice);
    g_spriteOffset.SetX(600.f);
    g_spriteOffset.SetY(400.f);


    srand(time(NULL)); //设置随机种子



    //验证码
    //parseCodeImage("D:/验证码图库/网易/1.jpg");

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
    CGameMain& game = CGameMain::Instance();


	switch (message)
	{
	case WM_PAINT:
        if (g_pDevice)
        {
//             D3DXMatrixPerspectiveFovLH( &proj,  D3DX_PI * 0.5f,  1,  1.0f,   1000.0f);
//             g_pDevice->SetTransform(D3DTS_PROJECTION, &proj);
         //   g_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff000000, 0.f, 0);
/*
            g_pDevice->BeginScene();

            // 设置当前纹理
            g_pDevice->SetTexture(0, g_pTexture);
            g_pDevice->SetStreamSource(0, g_pVb2, 0, sizeof(Vertex2));
            g_pDevice->SetFVF(Vertex2::FVF);

            g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);


            // 图2
            g_sprite[0].Update();
            g_sprite[0].Draw(g_pDevice);

            for (int i = 1 ; i < S_SIZE; i++)
            {
                g_sprite[i].Update();
                g_sprite[i].Draw(g_pDevice);
            }

            
            // 图3
            g_spriteOffset.Update();
            g_spriteOffset.Draw(g_pDevice);
            

            g_pDevice->EndScene();
            g_pDevice->Present(0,0,0,0);*/
        }
        
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    case WM_LBUTTONUP:
        game.OnLButtonUp(wParam, lParam);
        break;
    case WM_LBUTTONDOWN:
        game.OnLButtonDown(wParam, lParam);
        break;
    case WM_RBUTTONUP:
        game.OnRButtonUp(wParam, lParam);
        break;
    case WM_RBUTTONDOWN:
        game.OnRButtonDown(wParam, lParam);
        break;

    case WM_KEYDOWN:
        {
            game.OnKeyDown(wParam, lParam);
        }
        break;
    case WM_CHAR:
        {
            game.OnChar(wParam, lParam);
        }
        break;

    case WM_MOUSEMOVE: {
            game.OnMouseMove(wParam, lParam);
        }
        break;

	case WM_MOUSEWHEEL:{
		game.OnMouseWheel(wParam, lParam);
	}break;

    case WM_ERASEBKGND:
        return 0;
        break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

