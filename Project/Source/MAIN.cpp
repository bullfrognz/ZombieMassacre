//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MAIN.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>
#include <windowsx.h>
//#include <vld.h>

// Local Includes
#include "resource.h"
#include "Application.h"
#include "Window.h"
#include "DebugDialog.h"

// This Include

// Static Variables

// Static Function Prototypes
class CDebugDialog;

// Implementation
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _1pCmdLine, int _iCmdShow)
{
	srand(static_cast<unsigned int>(timeGetTime()));

	CApplication& rApplication = CApplication::GetInstance();
	rApplication.Initialise(_hInstance);

	CWindow& rGameWindow = rApplication.GetGameWindow();
	rGameWindow.Initialise(L"Zombie Massacure",
						   WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
						   100, 100,
						   1024, 768);

	rGameWindow.SetScene(SCENE_MAINMENU);

	CDebugDialog::GetInstance().Initialise(_hInstance, rGameWindow.GetHandle(), IDD_DEBUGDIALOG);
	HWND hDebugDialog = CDebugDialog::GetInstance().GetHandle();

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			if (!IsDialogMessage(hDebugDialog, &msg))
			{
				TranslateMessage(&msg); //Translate any accesserator keys
				DispatchMessage(&msg);  //Send the message to the window proc
			}

		}

		rGameWindow.ExecuteOneFrame();
	
	}

	CApplication::DestroyInstance();
	CDebugDialog::DestroyInstance();

	return (static_cast<int>(msg.wParam)); //Return to windows
}