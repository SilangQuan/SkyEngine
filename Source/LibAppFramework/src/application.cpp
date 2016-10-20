/*

#include "../include/application.h"

#include "../include/input.h"
#include "../include/fileio.h"
#include "../include/graphics.h"
#include "../include/scene.h"
#include "../include/resmanager.h"*/

#include "../../SkyEngine/include/SkyEngine.h"
#include "../include/application.h"
#include "../include/Renderer.h"
/*
#include "Render/Renderer.h"
#include "Input/InputManager.h"
#include "Render/Scene.h"
#include "Base/ResourceManager.h"*/

Application::Application()
{
	fFPS = 0.0f;
	fInvFPS = 0.0f;
	fElapsedTime = 0.0f;

	bWindowed = true;
	bActive = false;
	iWindowWidth = 640;
	iWindowHeight = 480;

	frameIdent = 0;

	pAppData = 0;

	pInput = 0;
	//pFileIO = 0;
	pRenderer = 0;
	pScene = 0;
	pResManager = 0;

	/*iTicksPerSecond.QuadPart = 0;
	iStartTime.QuadPart = 0;
	iLastTime.QuadPart = 0;*/


	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);
	freopen("CONIN$", "r+t", stdin);
}

Application::~Application()
{
	SAFE_DELETE_ARRAY(pAppData);

	SAFE_DELETE(pScene);
	SAFE_DELETE(pResManager);
	//SAFE_DELETE(pGraphics);
	//SAFE_DELETE(pFileIO);
	SAFE_DELETE(pInput);
}

bool Application::CreateSubSystems(const CreationFlags &creationFlags)
{

	pInput = new Input(this);
	// NOTE: should handle possible failing! maybe bad_alloc...
	time = new Time();
	time->Start();

	if (!pInput->Initialize())
		return false;

	LightManager::InitializeClass();
	//pFileIO = new CFileIO(this);
	//if (!pFileIO->bInitialize())
	//	return false;

	pRenderer = new Renderer(this);
	if (!pRenderer->Initialize(creationFlags))
		return false;

	pResManager = new ResourceManager();
	/*
	pScene = new Scene(this);
	if (!pScene->Initialize())
		return false;
		*/
	if (!CreateWorld())
	{
		DestroyWorld();
		return false;
	}

	return true;
}

// ----------------------------------------------------------------------------


bool Application::Initialize(const CreationFlags &creationFlags)
{
	bWindowed = creationFlags.isWindowed;

	window = new SdlWindow(creationFlags.title, creationFlags.width, creationFlags.height);

	// Initialize the timer ---------------------------------------------------

	if (!QueryPerformanceFrequency(&ticksPerSecond))
		return false;

	return CreateSubSystems(creationFlags); 


		/*
	// Create the render window -----------------------------------------------
/*
	WNDCLASS windowClass = { 0, &WindowProcedure, 0, 0, GetModuleHandle(0),
		i_creationFlags.hIcon, 0, 0, 0, "<application window>" };
	RegisterClass(&windowClass);

	uint32 iWindowStyle = WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU;

	RECT rc;
	SetRect(&rc, 0, 0, iWindowWidth, iWindowHeight);
	AdjustWindowRect(&rc, iWindowStyle, false);

	hWindowHandle = CreateWindow("<application window>", strWindowTitle.c_str(), iWindowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, (rc.right - rc.left), (rc.bottom - rc.top),
		0, 0, GetModuleHandle(0), 0);

	SetCursor(LoadCursor(0, IDC_WAIT));

	return CreateSubSystems(i_creationFlags);*/
}

int Application::Run()
{

	while (!pInput->QuitRequested())
	{
		time->Update();
		//window->HandleEvents();
		pInput->Update();
		BeginFrame();
		RenderWorld();
		EndFrame();
		//Sleep(1);
	}
		
	window->Quit(0);
	DestroyWorld();

	return 0;
	/*ShowWindow(hWindowHandle, SW_SHOW);
	SetFocus(hWindowHandle);*/
	/*SetCursor(LoadCursor(0, IDC_ARROW));
	bActive = true;

	// Begin application loop -------------------------------------------------

	while (CheckMessages())
	{
		BeginFrame();
		RenderWorld();
		EndFrame();

		Sleep(1);
	}*/
	//getchar();
	// End of application loop = termination of program -----------------------

	//DestroyWorld();

	return 0;
}

void Application::BeginFrame()
{

	if (!startTime.QuadPart)
	{
		QueryPerformanceCounter(&startTime);
		lastTime.QuadPart = startTime.QuadPart;
	}

	++frameIdent;

	//pInput->Update();			// Get latest keyboard and mouse state

	//FrameMove();
	//pScene->FrameMove();
}

bool Application::CheckMessages()
{
	return true;
/*
	while (true)
	{
		MSG msgMessage;

		if (bActive)
		{
			if (!PeekMessage(&msgMessage, 0, 0, 0, PREMOVE))
				break;
		}
		else
		{
			if (!GetMessage(&msgMessage, 0, 0, 0))
				break;
		}

		TranslateMessage(&msgMessage);
		DispatchMessage(&msgMessage);

		if (msgMessage.message == WQUIT)
			return false;
	}

	return true;*/
}

void Application::EndFrame()
{
	LARGE_INTEGER iCurrentTime;
	QueryPerformanceCounter(&iCurrentTime);

	float32 fTimeDifference = (float32)(iCurrentTime.QuadPart - lastTime.QuadPart);
	fElapsedTime += fTimeDifference / (float32)ticksPerSecond.QuadPart;
	fFPS = (float32)ticksPerSecond.QuadPart / fTimeDifference;

	fInvFPS = 1.0f / fFPS;
	lastTime.QuadPart = iCurrentTime.QuadPart;
}

float32 Application::GetFPS() { return 1.0f/ time->deltaTime; }


SdlWindow* Application::GetWindow()
{
	return window;
}

