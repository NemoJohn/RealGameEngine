#include "GameEngine.h"

#include "BasePrimitive.h"
#include "SubSystem/TextureCache.h"
#include "SubSystem/StaticMeshCache.h"
#include "SubSystem/LightManager.h"
#include "SubSystem/CameraManager.h"

#include "WorldContext.h"
#include "SubSystem/UMGManager.h"
#include "UMG/UTextBlock.h"

#include "TestButton1.h"

#include "BasePrimitive.h"
#include "MyActor_2.h"

TestButton1* b1 = nullptr;

UTextBlock* tb = nullptr;

BasePrimitive* bp = nullptr;
MyActor_2* actor = nullptr;

LPDIRECT3DDEVICE9 GameEngine::m_pd3dDevice = nullptr;
float GameEngine::deltaTime = 0;
float GameEngine::playTime = 0;
GameTime GameEngine::gameTime;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UMGManager::GetInstance()->ProcessMessage(message, wParam, lParam);

    switch (message)
    {
    case WM_CHAR:
    {
        switch (wParam)
        {
        case 's':
        case 'S':
            WorldContext::GetInstance()->SaveLevel("other1.xml");
            break;
        }
    }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void GameEngine::RegisterWindows()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_REALGAMEENGINE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;// MAKEINTRESOURCEW(IDC_REALGAMEENGINE);
    wcex.lpszClassName = L"MyD3DTest";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassExW(&wcex);
}

void GameEngine::CreateWindows()
{
    //游戏配置文件ini
    int w = GetPrivateProfileInt(L"CONFIG", L"width", 0, L".\\GameConfig.ini");
    int h = GetPrivateProfileInt(L"CONFIG", L"heigth", 0, L".\\GameConfig.ini");

    //获取桌面分辨率
    HWND desk = GetDesktopWindow();
    RECT rc;
    GetWindowRect(desk, &rc);


    hWnd = CreateWindow(L"MyD3DTest", L"hellworld", WS_OVERLAPPEDWINDOW,
        rc.right / 2 - w / 2, rc.bottom / 2 - h / 2, w, h, nullptr, nullptr, GetModuleHandle(NULL), nullptr);
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
}

void GameEngine::CreateDevice()
{
    m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.EnableAutoDepthStencil = true;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

    m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &m_pd3dDevice);

    

    //渲染状态的切换-效率及其低下
    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    //无法线的模型如何看到,关闭光照 给予环境光nolit
    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING,true);
    m_pd3dDevice->SetRenderState(D3DRS_AMBIENT,0xff111111);

    //默认渲染是实体渲染
    //m_pd3dDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);

    //开启深度测试
    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE,true);

   
    TextureCache::GetInstance()->Init();
    StaticMeshCache::GetInstance()->Init();

    //最后一步初始化世界大纲
    WorldContext::GetInstance()->OpenLevel("world.xml");
    
    //b1 = new TestButton1;
    //b1->Init();
    //b1->SetSize(256, 256);
    //b1->AddToViewport(1);
    //b1->SetLocation(400, 150);

    //tb = new UTextBlock;
    //tb->Init(80,200);
    //tb->SetRelativeLocation(80, 100);
   
    //b1->AddChild(tb);

	bp = new BasePrimitive;
	bp->CreateVertex();

    actor = new MyActor_2;
}


void GameEngine::OnUpdate(float dt)
{
    LightManager::GetInstance()->Update();
    CameraManager::GetInstance()->Update();
   // WorldContext::GetInstance()->Tick(dt);


}

void GameEngine::OnRender()
{
    //清屏 渲染到后台 交换链
    m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 0), 1.0f, 0);

    if (SUCCEEDED(m_pd3dDevice->BeginScene()))
    {
        //WorldContext::GetInstance()->Render();
        UMGManager::GetInstance()->OnRender();
        bp->OnRender();
        //actor->Render();
        m_pd3dDevice->EndScene();
    }
    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void GameEngine::RunEngine()
{
    RegisterWindows();
    CreateWindows();
    CreateDevice();
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {

            static float nt = timeGetTime();
            OnUpdate(deltaTime);
            OnRender();
            deltaTime = (timeGetTime() - nt) / 1000.0f;
            nt = timeGetTime();
            playTime += deltaTime;

            //char str[100] = "";
            //sprintf(str,"h=%d m=%d s=%d\n", GetPlayTime().hour, GetPlayTime().min, GetPlayTime().sec);
            //OutputDebugStringA(str);
        }
    }
}

GameTime GameEngine::GetPlayTime()
{
    GameTime t;
    t.hour = GetPlaySecond() / 3600;
    t.min = (GetPlaySecond() % 3600) / 60;
    t.sec = (GetPlaySecond() % 3600) % 60;
    return t;
}
