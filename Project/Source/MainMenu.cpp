//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MainMenu.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes
#include "Application.h"
#include "Window.h"
#include "resource.h"
#include "Button.h"
#include "SpriteEntity.h"

// This Include
#include "MainMenu.h"

// Static Variables

// Static Function Prototypes

// Implementation
CMainMenu::CMainMenu()
: m_pGameTitle(0)
, m_pButtonPlayGame(0)
, m_pButtonViewHighScores(0)
, m_pButtonQuitGame(0)
{
	//Empty
}

CMainMenu::~CMainMenu()
{
	delete m_pGameTitle;
	m_pGameTitle = 0;

	delete m_pButtonPlayGame;
	m_pButtonPlayGame = 0;

	delete m_pButtonViewHighScores;
	m_pButtonViewHighScores = 0;

	delete m_pButtonQuitGame;
	m_pButtonQuitGame = 0;
}

bool
CMainMenu::Initialise()
{	
	RECT rectWindowBounds = CApplication::GetInstance().GetGameWindow().GetBounds();
	int iHalfWidth = rectWindowBounds.right / 2;

	m_pGameTitle = new CSpriteEntity();
	m_pGameTitle->Initialise(IDB_GAMETITLE, IDB_GAMETITLEMASK);
	m_pGameTitle->SetPosition(iHalfWidth, 100);

	m_pButtonPlayGame = new CButton();
	m_pButtonPlayGame->Initialise(IDB_BUTTON_PLAYGAME, IDB_BUTTON_MAINMENUMASK);
	m_pButtonPlayGame->SetPosition(iHalfWidth, 250);
	m_pButtonPlayGame->UpdateBounds();

	m_pButtonViewHighScores = new CButton();
	m_pButtonViewHighScores->Initialise(IDB_BUTTON_HIGHSCORES, IDB_BUTTON_MAINMENUMASK);
	m_pButtonViewHighScores->SetPosition(iHalfWidth, 335);
	m_pButtonViewHighScores->UpdateBounds();

	m_pButtonQuitGame = new CButton();
	m_pButtonQuitGame->Initialise(IDB_BUTTON_QUIT, IDB_BUTTON_MAINMENUMASK);
	m_pButtonQuitGame->SetPosition(iHalfWidth, 550);
	m_pButtonQuitGame->UpdateBounds();

	return true;
}

void
CMainMenu::Process(float _fDeltaTick)
{
	m_pGameTitle->Process(_fDeltaTick);

	m_pButtonPlayGame->Process(_fDeltaTick);
	m_pButtonViewHighScores->Process(_fDeltaTick);
	m_pButtonQuitGame->Process(_fDeltaTick);

	if (m_pButtonPlayGame->HasBeenClicked() == true)
	{
		CApplication::GetInstance().GetGameWindow().SetScene(SCENE_GAME);
	}
	else if (m_pButtonViewHighScores->HasBeenClicked() == true)
	{
		CApplication::GetInstance().GetGameWindow().SetScene(SCENE_HIGHSCORETABLE);
	}
	else if (m_pButtonQuitGame->HasBeenClicked() == true)
	{
		CApplication::GetInstance().Quit();
	}
}

void
CMainMenu::Draw()
{
	m_pGameTitle->Draw();

	m_pButtonPlayGame->Draw();
	m_pButtonViewHighScores->Draw();
	m_pButtonQuitGame->Draw();
}