//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Window.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>

// Local Includes
#include "resource.h"

// Framework
#include "MessageManager.h"
#include "BackBuffer.h"
#include "Clock.h"
#include "PerformanceClock.h"
#include "DebugDialog.h"

// Core

// Game
#include "MainMenu.h"
#include "GameScene.h"
#include "HighScoreTable.h"
#include "SubmitScore.h"

// This Include
#include "Window.h"

// Static Variables
#define WINDOW_CLASS_NAME L"MYWINCLASS"

// Static Function Prototypes

// Implementation
CWindow* g_pWindowClassTemp = 0;
LRESULT CALLBACK WinowProcWrapper(HWND _hWindow, UINT _Message, WPARAM _wParam, LPARAM _lParam)
{
	return g_pWindowClassTemp->WindowProc(_hWindow, _Message, _wParam, _lParam);
}

CWindow::CWindow(HINSTANCE _hInstance)
: m_iWidth(0)
, m_iHeight(0)
, m_hInstance(_hInstance)
, m_hWindow(0)
, m_hIcon(0)
, m_hCursor(0)
, m_hMenu(0)
, m_pClock(0)
, m_pBackBuffer(0)
, m_eCurrentScene(SCENE_INVALID)
, m_pScene(0)
, m_pMessageManager(0)
{
	g_pWindowClassTemp = this;

	m_hCursor = LoadCursor( NULL , IDC_ARROW );
	m_hIcon = LoadIcon(NULL, IDI_APPLICATION );
}

CWindow::~CWindow()
{
	delete m_pClock;
	m_pClock = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pScene;
	m_pScene = 0;

	delete m_pMessageManager;
	m_pMessageManager = 0;
}

bool
CWindow::InitialiseWinClass()
{
	WNDCLASSEX WinClass;

	WinClass.cbSize			= sizeof(WNDCLASSEX);
	WinClass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WinClass.lpfnWndProc	= WinowProcWrapper;
	WinClass.cbClsExtra		= 0;
	WinClass.cbWndExtra		= 0;
	WinClass.hInstance		= m_hInstance;
	WinClass.hIcon			= m_hIcon;
	WinClass.hCursor		= m_hCursor;
	WinClass.hbrBackground	= static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	WinClass.lpszMenuName	= NULL;
	WinClass.lpszClassName	= WINDOW_CLASS_NAME;
	WinClass.hIconSm		= m_hIcon;

	if (!RegisterClassEx(&WinClass)) //Could not create class
	{
		return (false);
	}
	else
	{
		return (true);
	}
}

HWND
CWindow::Initialise(LPCWSTR _kcpTitle, DWORD _iStyle, int _iPosX, int _iPosY,
					int _iWidth, int _iHeight, HMENU hwndMenu, HWND hwndParent)
{
	assert(m_hWindow == 0);//Class is already or not initialised

	InitialiseWinClass();

	m_hWindow = CreateWindowEx(NULL,					//Extended style
							   WINDOW_CLASS_NAME,		//Class
							   _kcpTitle,				//Title
							   _iStyle,					//_iStyle
							   _iPosX  , _iPosY,		//Initial x,y
							   _iWidth , _iHeight,		//Initial width, height
							   hwndParent,				//Handle to parent
							   hwndMenu,				//Handle to menu
							   m_hInstance,				//Instance of this application
							   NULL);					//Extra creation parameters
	
	if (!m_hWindow)
	{
		return (false);
	}

	m_iWidth  = _iWidth;
	m_iHeight = _iHeight;

	m_rectBounds.top = 0;
	m_rectBounds.bottom = m_iHeight;
	m_rectBounds.left = 0;
	m_rectBounds.right = m_iWidth;

	__int64 i64CountsPerSecond = 0;
	bool bUsePerformanceCounter = (QueryPerformanceFrequency((LARGE_INTEGER*)&i64CountsPerSecond) != 0);

	if (bUsePerformanceCounter == true)
	{
		m_pClock = new CPerformanceClock(i64CountsPerSecond);
	}
	else
	{
		m_pClock = new CClock();
	}

	m_pClock->Initialise();

	m_pBackBuffer = new CBackBuffer();
	m_pBackBuffer->Initialise(m_hWindow, _iWidth, _iHeight);

	m_pMessageManager = new CMessageManager();

	return (m_hWindow);
}

LRESULT CALLBACK
CWindow::WindowProc(HWND _hWindow, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMessage)
	{
		case WM_SETCURSOR:
			SetCursor(m_hCursor);
			break;

		case WM_MOUSEMOVE:
			m_pMessageManager->SendMsgToTargets(MSG_MOUSE_MOVE, _wParam, _lParam);
			break;

		case WM_LBUTTONDOWN:
			m_pMessageManager->SendMsgToTargets(MSG_MOUSE_LBUTTONDWN, _wParam, _lParam);
			break;

		case WM_LBUTTONUP:
			m_pMessageManager->SendMsgToTargets(MSG_MOUSE_LBUTTONUP, _wParam, _lParam);
			break;

		case WM_RBUTTONDOWN:
			m_pMessageManager->SendMsgToTargets(MSG_MOUSE_RBUTTONUP, _wParam, _lParam);
			break;

		case WM_RBUTTONUP:
			m_pMessageManager->SendMsgToTargets(MSG_MOUSE_RBUTTONDWN, _wParam, _lParam);
			break;

		case WM_KEYDOWN:
			{
				switch (_wParam)
				{
					case 0x57://W
						m_pMessageManager->SendMsgToTargets(MSG_KEY_W_DWN, _wParam, _lParam);
						break;
						
					case 0x53://S
						m_pMessageManager->SendMsgToTargets(MSG_KEY_S_DWN, _wParam, _lParam);
						break;

					case 0x41://A
						m_pMessageManager->SendMsgToTargets(MSG_KEY_A_DWN, _wParam, _lParam);
						break;
						
					case 0x44://D
						m_pMessageManager->SendMsgToTargets(MSG_KEY_D_DWN, _wParam, _lParam);
						break;

					case 0x52://R
						m_pMessageManager->SendMsgToTargets(MSG_KEY_R_DWN, _wParam, _lParam);
						break;

					case 0x51://Q
						m_pMessageManager->SendMsgToTargets(MSG_KEY_Q_DWN, _wParam, _lParam);
						break;

					case 0x45://E
						m_pMessageManager->SendMsgToTargets(MSG_KEY_E_DWN, _wParam, _lParam);
						break;

					case 0x54://T
						m_pMessageManager->SendMsgToTargets(MSG_KEY_T_DWN, _wParam, _lParam);
						break;

					case 0x59://Y
						m_pMessageManager->SendMsgToTargets(MSG_KEY_Y_DWN, _wParam, _lParam);
						break;

					case 0x55://U
						m_pMessageManager->SendMsgToTargets(MSG_KEY_U_DWN, _wParam, _lParam);
						break;

					case 0x49://I
						m_pMessageManager->SendMsgToTargets(MSG_KEY_I_DWN, _wParam, _lParam);
						break;

					case 0x4F://O
						m_pMessageManager->SendMsgToTargets(MSG_KEY_O_DWN, _wParam, _lParam);
						break;

					case 0x50://P
						m_pMessageManager->SendMsgToTargets(MSG_KEY_P_DWN, _wParam, _lParam);
						break;

					case 0x46://F
						m_pMessageManager->SendMsgToTargets(MSG_KEY_F_DWN, _wParam, _lParam);
						break;

					case 0x47://G
						m_pMessageManager->SendMsgToTargets(MSG_KEY_G_DWN, _wParam, _lParam);
						break;

					case 0x48://H
						m_pMessageManager->SendMsgToTargets(MSG_KEY_H_DWN, _wParam, _lParam);
						break;

					case 0x4A://J
						m_pMessageManager->SendMsgToTargets(MSG_KEY_J_DWN, _wParam, _lParam);
						break;

					case 0x4B://K
						m_pMessageManager->SendMsgToTargets(MSG_KEY_K_DWN, _wParam, _lParam);
						break;

					case 0x4C://L
						m_pMessageManager->SendMsgToTargets(MSG_KEY_L_DWN, _wParam, _lParam);
						break;

					case 0x5A://Z
						m_pMessageManager->SendMsgToTargets(MSG_KEY_Z_DWN, _wParam, _lParam);
						break;

					case 0x58://X
						m_pMessageManager->SendMsgToTargets(MSG_KEY_X_DWN, _wParam, _lParam);
						break;

					case 0x43://C
						m_pMessageManager->SendMsgToTargets(MSG_KEY_C_DWN, _wParam, _lParam);
						break;

					case 0x56://V
						m_pMessageManager->SendMsgToTargets(MSG_KEY_V_DWN, _wParam, _lParam);
						break;

					case 0x42://B
						m_pMessageManager->SendMsgToTargets(MSG_KEY_B_DWN, _wParam, _lParam);
						break;

					case 0x4E://N
						m_pMessageManager->SendMsgToTargets(MSG_KEY_N_DWN, _wParam, _lParam);
						break;

					case 0x4D://M
						m_pMessageManager->SendMsgToTargets(MSG_KEY_M_DWN, _wParam, _lParam);
						break;

					case 0x1B://Esc
						m_pMessageManager->SendMsgToTargets(MSG_KEY_ESC_DWN, _wParam, _lParam);
						break;

					case 0x08://BackSpace
						m_pMessageManager->SendMsgToTargets(MSG_KEY_BACKSPACE_DWN, _wParam, _lParam);
						break;

					case 0x0D://BackSpace
						m_pMessageManager->SendMsgToTargets(MSG_KEY_ENTER_DWN, _wParam, _lParam);
						break;
				}
				break;
			}

		case WM_KEYUP:
			{
				switch (_wParam)
				{
					case 0x57://W
						m_pMessageManager->SendMsgToTargets(MSG_KEY_W_UP, _wParam, _lParam);
						break;
						
					case 0x53://S
						m_pMessageManager->SendMsgToTargets(MSG_KEY_S_UP, _wParam, _lParam);
						break;

					case 0x41://A
						m_pMessageManager->SendMsgToTargets(MSG_KEY_A_UP, _wParam, _lParam);
						break;
						
					case 0x44://D
						m_pMessageManager->SendMsgToTargets(MSG_KEY_D_UP, _wParam, _lParam);
						break;

					case 0x52://R
						m_pMessageManager->SendMsgToTargets(MSG_KEY_R_UP, _wParam, _lParam);
						break;

					case 0x1B://Esc
						break;
				}
				break;
			}

		case WM_CREATE: //Do initialization stuff here
			break;

		case WM_PAINT:
			break;

		case WM_DESTROY: //Kill the application, this sends a WM_QUIT message
			PostQuitMessage(0);
			break;

		default:
			return (DefWindowProc(_hWindow, _uiMessage, _wParam, _lParam));
			break;
	}

	return (0);
}

void
CWindow::SetScene(EWINDOWSCENE _eScene)
{
	m_pMessageManager->ClearMsgTargets();

	if (m_pScene != 0)
	{
		delete m_pScene;
		m_pScene = 0;
	}

	switch (_eScene)
	{
		case SCENE_MAINMENU:
		{
			m_pScene = new CMainMenu();
			break;
		}
		case SCENE_HIGHSCORETABLE:
		{
			m_pScene = new CHighScoreTable();
			break;
		}
		case SCENE_GAME:
		{
			m_pScene = new CGameScene();
			break;
		}
		case SCENE_SUBMITSCORE:
		{
			m_pScene = new CSubmitScore();
			break;
		}
		default:
		{
			assert(false);//Scene could not be found
			break;
		}
	}

	m_pScene->Initialise();
}

void
CWindow::ExecuteOneFrame()
{
	assert(m_pScene);//Scene was not set or is invalid

	m_pClock->Process();

	m_pBackBuffer->Clear();

	m_pScene->Process(m_pClock->GetDeltaTick());
	m_pScene->Draw();

	m_pClock->Draw();

	m_pBackBuffer->Present();
}