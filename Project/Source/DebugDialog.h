//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DebugDialog.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_DEBUGDIALOG_H__
#define __IGFEB11_IG120_DEBUGDIALOG_H__

// Library Includes
#include <windows.h>

// Local Includes

// Types

// Constants

// Prototypes
class CTurret;
class CGameScene;

class CDebugDialog
{
    // Member Functions
public:
	~CDebugDialog();

	static CDebugDialog& GetInstance();
	static void DestroyInstance();

	HWND Initialise(HINSTANCE _hInstance, HWND _hWindow , int _iDialog);
	BOOL CALLBACK DialogProc(HWND _hDialog, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam);
	void Display();

	void SetValues();
	void ApplyValues();

	HWND GetHandle();

	void SetInputValue(const int _iIDC, int _iValue);
	void SetInputValue(const int _iIDC, float _fValue);

	void GetInputValue(const int _iIDC, int& _iValue);
	void GetInputValue(const int _iIDC, float& _fValue);

	void SetTurret(CTurret* _pTurret);
	void ForgetTurret();
	void SetGameScene(CGameScene* _pGameScene);
	void ForgetGameScene();

protected:

private:
	CDebugDialog();
	CDebugDialog(const CDebugDialog& _kr);
	CDebugDialog& operator= (const CDebugDialog& _kr);

    // Member Variables
public:

protected:

private:
	HINSTANCE m_hInstance;

	HWND m_hWindow;
	HWND m_hDialog;

	int m_iDialog;

	CTurret* m_pTurret;
	CGameScene* m_pGameScene;

	static CDebugDialog* s_pDebugDialog;

};

#endif // __IGFEB11_IG120_DEBUGDIALOG_H__
