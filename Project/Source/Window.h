//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Window.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_WINDOW_H__
#define __IGFEB11_IG120_WINDOW_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "Scene.h"

// Types

// Constants

// Prototypes
class CClock;
class CBackBuffer;
class CMessageManager;

class CWindow
{
    // Member Functions
public:
	CWindow(HINSTANCE _hInstance);
	~CWindow();

	HWND Initialise(LPCWSTR _kcpTitle, DWORD _iStyle, int _iPosX, int _iPosY, int _iWidth,
					int _iHeight, HMENU hwndMenu = NULL, HWND hwndParent = NULL);

	LRESULT CALLBACK WindowProc(HWND _hWindow, UINT _Message, WPARAM _wParam, LPARAM _lParam);

	void SetScene(EWINDOWSCENE _eScene);

	void ExecuteOneFrame();

	// Member Inline Functions
	inline int GetWidth();
	inline int GetHeight();

	inline CBackBuffer& GetBackBuffer();
	inline CMessageManager& GetMsgManager();

	inline HWND GetHandle();

	inline RECT GetBounds();

	inline IScene& GetScene();

protected:

private:
	bool InitialiseWinClass();

    // Member Variables
public:

protected:

private:
	RECT m_rectBounds;

	int m_iWidth;
	int m_iHeight;

	HINSTANCE m_hInstance;
	
	HWND	  m_hWindow;
	HICON     m_hIcon;
	HCURSOR   m_hCursor;
	HMENU     m_hMenu;

	CClock*      m_pClock;
	CBackBuffer* m_pBackBuffer;

	EWINDOWSCENE m_eCurrentScene;
	IScene*      m_pScene;

	CMessageManager* m_pMessageManager;

};

#include "Window.inl"

#endif // __IGFEB11_IG120_WINDOW_H__
