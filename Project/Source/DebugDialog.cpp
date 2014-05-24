//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DebugDialog.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>
#include <iostream>

// Local Includes
#include "resource.h"

// Framework
#include "Application.h"
#include "Window.h"
#include "Scene.h"
#include "Utilities.h"

// Core

// Content
#include "GameScene.h"
#include "Turret.h"
#include "Weapon.h"

// This Include
#include "DebugDialog.h"

// Static Variables
CDebugDialog* CDebugDialog::s_pDebugDialog = 0;

// Static Function Prototypes

// Implementation
CDebugDialog* g_DialogWrapperInstance = 0;

CDebugDialog::CDebugDialog()
: m_hInstance(0)
, m_hWindow(0)
, m_hDialog(0)
, m_iDialog(0)
, m_pTurret(0)
, m_pGameScene(0)
{
	g_DialogWrapperInstance = this;
}

CDebugDialog::~CDebugDialog()
{
	DestroyWindow(m_hDialog);
}

BOOL CALLBACK
DialogProcWrapper(HWND _hDialog, UINT _Message, WPARAM _wParam, LPARAM _lParam)
{
	return g_DialogWrapperInstance->DialogProc(_hDialog, _Message, _wParam, _lParam);
}

HWND
CDebugDialog::Initialise(HINSTANCE _hInstance, HWND _hWindow , int _iDialog)
{
	m_hInstance = _hInstance;
	m_hWindow = _hWindow;
	m_iDialog = _iDialog;

	m_hDialog = CreateDialog(m_hInstance, MAKEINTRESOURCE(m_iDialog), m_hWindow, DialogProcWrapper);

	return m_hDialog;
}

BOOL CALLBACK
CDebugDialog::DialogProc(HWND _hDialog, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam)
{

	switch (_uiMessage)
	{
	case WM_COMMAND:
		switch (LOWORD(_wParam))
		{
		case ID_APPLY:
			ApplyValues();
			break;

		case ID_CLOSE:
			ShowWindow(m_hDialog, SW_HIDE);
			break;

		default:
			break;
		}
		break;

	case WM_CLOSE:
		ShowWindow(m_hDialog, SW_HIDE);
		return (TRUE);
		break;

	default:
		break;
	}

	return (FALSE);
}

void
CDebugDialog::Display()
{
	ShowWindow(m_hDialog, SW_SHOW);
}

HWND
CDebugDialog::GetHandle()
{
	return (m_hDialog);
}

void
CDebugDialog::SetValues()
{
	float fFireRate		 = m_pTurret->GetFireRate();
	int iCriticalChange	 = m_pTurret->GetWeapon().GetCriticalRating();
	int iBulletDamageMax = m_pTurret->GetWeapon().GetBulletDamageMax();
	int iBulletDamageMin = m_pTurret->GetWeapon().GetBulletDamageMin();
	int iGrenadeAmmo	 = m_pTurret->GetWeapon().GetHolyGrenadeAmmo();
	int iExperience		 = m_pTurret->GetCurrentXp();
	int iUpgradePoints	 = m_pTurret->GetNumUpgradePoints();
	int iMaxHealth		 = m_pTurret->GetMaxHealth();
	int iCurrentHealth	 = m_pTurret->GetCurrentHealth();
	int iGameLevel		 = m_pGameScene->GetGameLevel();
	float fZombieSpawnRate = m_pGameScene->GetZombieSpawnRate();

	SetInputValue(IDC_INPUT_FIRERATE, fFireRate);
	SetInputValue(IDC_INPUT_CRITICALCHANCE, iCriticalChange);
	SetInputValue(IDC_INPUT_BULLETDAMAGEMAX, iBulletDamageMax);
	SetInputValue(IDC_INPUT_BULLETDAMAGEMIN, iBulletDamageMin);
	SetInputValue(IDC_INPUT_GRENADEAMMO, iGrenadeAmmo);
	SetInputValue(IDC_INPUT_EXPERIENCE, iExperience);
	SetInputValue(IDC_INPUT_UPGRADEPOINTS, iUpgradePoints);
	SetInputValue(IDC_INPUT_MAXHEALTH, iMaxHealth);
	SetInputValue(IDC_INPUT_CURRENTHEALTH, iCurrentHealth);
	SetInputValue(IDC_INPUT_GAMELEVEL, iGameLevel);
	SetInputValue(IDC_INPUT_ZOMBIESPAWNRATE, fZombieSpawnRate);
}

void
CDebugDialog::ApplyValues()
{
	if (m_pTurret != 0)
	{
		float fFireRate		 = 0.0f;
		int iCriticalChange	 = 0;
		int iBulletDamageMax = 0;
		int iBulletDamageMin = 0;
		int iGrenadeAmmo	 = 0;
		int iExperience		 = 0;
		int iUpgradePoints	 = 0;
		int iMaxHealth		 = 0;
		int iCurrentHealth	 = 0;
		int iGameLevel = 0;
		float fZombieSpawnRate = 0.0f;

		GetInputValue(IDC_INPUT_FIRERATE, fFireRate);
		GetInputValue(IDC_INPUT_CRITICALCHANCE, iCriticalChange);
		GetInputValue(IDC_INPUT_BULLETDAMAGEMAX, iBulletDamageMax);
		GetInputValue(IDC_INPUT_BULLETDAMAGEMIN, iBulletDamageMin);
		GetInputValue(IDC_INPUT_GRENADEAMMO, iGrenadeAmmo);
		GetInputValue(IDC_INPUT_EXPERIENCE, iExperience);
		GetInputValue(IDC_INPUT_UPGRADEPOINTS, iUpgradePoints);
		GetInputValue(IDC_INPUT_MAXHEALTH, iMaxHealth);
		GetInputValue(IDC_INPUT_CURRENTHEALTH, iCurrentHealth);
		GetInputValue(IDC_INPUT_GAMELEVEL, iGameLevel);
		GetInputValue(IDC_INPUT_ZOMBIESPAWNRATE, fZombieSpawnRate);
		
		CWeapon& rWeapon = m_pTurret->GetWeapon();

		m_pTurret->SetFireRate(fFireRate);
		rWeapon.SetCriticalRating(iCriticalChange);
		rWeapon.SetBulletDamageMax(iBulletDamageMax);
		rWeapon.SetBulletDamageMin(iBulletDamageMin);
		rWeapon.SetHolyGrenadeAmmo(iGrenadeAmmo);
		m_pTurret->SetCurrentXp(iExperience);
		m_pTurret->SetNumUpgradePoints(iUpgradePoints);
		m_pTurret->SetMaxHealth(iMaxHealth);
		m_pTurret->SetCurrentHealth(iCurrentHealth);
		m_pGameScene->SetGameLevel(iGameLevel);
		m_pGameScene->SetZombieSpawnRate(fZombieSpawnRate);
		
	}
}

void
CDebugDialog::SetInputValue(const int _iIDC, int _iValue)
{
	HWND hInput = GetDlgItem(m_hDialog, _iIDC);

	char* cpBuffer = new char[128];
	wchar_t* wcpBuffer = 0;

	sprintf_s(cpBuffer, 128, "%d", _iValue);
	wcpBuffer = ConvertConstCharToWchart(cpBuffer);
	SetWindowText(hInput, wcpBuffer);

	delete wcpBuffer;
	wcpBuffer = 0;

	delete cpBuffer;
	cpBuffer = 0;
}

void
CDebugDialog::SetInputValue(const int _iIDC, float _fValue)
{
	HWND hInput = GetDlgItem(m_hDialog, _iIDC);

	char* cpBuffer = new char[128];
	wchar_t* wcpBuffer = 0;

	sprintf_s(cpBuffer, 128, "%.3f", _fValue);
	wcpBuffer = ConvertConstCharToWchart(cpBuffer);
	SetWindowText(hInput, wcpBuffer);

	delete wcpBuffer;
	wcpBuffer = 0;

	delete cpBuffer;
	cpBuffer = 0;
}


void
CDebugDialog::GetInputValue(const int _iIDC, int& _iValue)
{
	HWND hInput = GetDlgItem(m_hDialog, _iIDC);

	char* cpBuffer = 0;
	wchar_t* wcpBuffer = new wchar_t[256];
	
	GetWindowText(hInput, wcpBuffer, 256);
	cpBuffer = ConvertWchartToChar(wcpBuffer);
	_iValue = atoi(cpBuffer);

	delete cpBuffer;
	cpBuffer = 0;
	
	delete wcpBuffer;
	wcpBuffer = 0;
}

void
CDebugDialog::GetInputValue(const int _iIDC, float& _fValue)
{
	HWND hInput = GetDlgItem(m_hDialog, _iIDC);

	char* cpBuffer = 0;
	wchar_t* wcpBuffer = new wchar_t[256];
	
	GetWindowText(hInput, wcpBuffer, 256);
	cpBuffer = ConvertWchartToChar(wcpBuffer);
	_fValue = static_cast<float>(atof(cpBuffer));

	delete cpBuffer;
	cpBuffer = 0;
	
	delete wcpBuffer;
	wcpBuffer = 0;
}




CDebugDialog&
CDebugDialog::GetInstance()
{
	if (s_pDebugDialog == 0)
	{
		s_pDebugDialog = new CDebugDialog();
	}

	return (*s_pDebugDialog);
}

void
CDebugDialog::DestroyInstance()
{
	delete s_pDebugDialog;
	s_pDebugDialog = 0;
}

void
CDebugDialog::SetTurret(CTurret* _pTurret)
{
	m_pTurret = _pTurret;
}

void
CDebugDialog::ForgetTurret()
{
	m_pTurret = 0;
}

void
CDebugDialog::SetGameScene(CGameScene* _pGameScene)
{
	m_pGameScene = _pGameScene;
}

void
CDebugDialog::ForgetGameScene()
{
	m_pGameScene = 0;
}