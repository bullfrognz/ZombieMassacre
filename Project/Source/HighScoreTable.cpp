//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   HighScoreTable.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <string>

// Local Includes
#include "resource.h"

// Framework
#include "Application.h"
#include "IniParser.h"
#include "Window.h"

// Core
#include "Text.h"
#include "Button.h"
#include "SpriteEntity.h"

// Game

// This Include
#include "HighScoreTable.h"

// Static Variables

// Static Function Prototypes

// Implementation

CHighScoreTable::CHighScoreTable()
: m_pSEntTitle(0)
, m_pTxtPlace1(0)
, m_pTxtPlace2(0)
, m_pTxtPlace3(0)
, m_pTxtPlace4(0)
, m_pTxtPlace5(0)
, m_pBtnMainMenu(0)
{
	//Empty
}

CHighScoreTable::~CHighScoreTable()
{
	Deinitialise();
}

bool
CHighScoreTable::Initialise()
{
	m_iMaxHighScores = 5;

	InitialiseTitle();
	InitialiseText();
	InitialiseMainMenuButton();
	InitialiseScores();

	return (true);
}

bool
CHighScoreTable::Deinitialise()
{
	DeinitialiseTitle();
	DeinitialiseText();
	DeinitialiseMainMenuButton();

	return (true);
}

void
CHighScoreTable::Process(float _fDeltatick)
{
	m_pSEntTitle->Process(_fDeltatick);
	m_pTxtPlace1->Process(_fDeltatick);
	m_pTxtPlace2->Process(_fDeltatick);
	m_pTxtPlace3->Process(_fDeltatick);
	m_pTxtPlace4->Process(_fDeltatick);
	m_pTxtPlace5->Process(_fDeltatick);
	m_pBtnMainMenu->Process(_fDeltatick);

	if (m_pBtnMainMenu->HasBeenClicked() == true)
	{
		CApplication::GetInstance().GetGameWindow().SetScene(SCENE_MAINMENU);
	}
}

void
CHighScoreTable::Draw()
{
	m_pSEntTitle->Draw();
	m_pTxtPlace1->Draw();
	m_pTxtPlace2->Draw();
	m_pTxtPlace3->Draw();
	m_pTxtPlace4->Draw();
	m_pTxtPlace5->Draw();
	m_pBtnMainMenu->Draw();
}

bool
CHighScoreTable::InitialiseTitle()
{
	m_pSEntTitle = new CSpriteEntity();
	m_pSEntTitle->Initialise(IDB_TITLE_HIGHSCORE, IDB_TITLE_HIGHSCOREMASK);
	m_pSEntTitle->SetPosition(500, 100);

	return (true);
}

bool
CHighScoreTable::InitialiseText()
{
	const int kiFontWidth = 14;
	const int kiFontHeight = 32;

	m_pTxtPlace1 = new CText;
	m_pTxtPlace1->Initialise();
	m_pTxtPlace1->SetFont(kiFontWidth, kiFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlace1->SetPosition(325, 200);
	m_pTxtPlace1->SetDisplay(true);

	m_pTxtPlace2 = new CText;
	m_pTxtPlace2->Initialise();
	m_pTxtPlace2->SetFont(kiFontWidth, kiFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlace2->SetPosition(325, 250);
	m_pTxtPlace2->SetDisplay(true);

	m_pTxtPlace3 = new CText;
	m_pTxtPlace3->Initialise();
	m_pTxtPlace3->SetFont(kiFontWidth, kiFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlace3->SetPosition(325, 300);
	m_pTxtPlace3->SetDisplay(true);

	m_pTxtPlace4 = new CText;
	m_pTxtPlace4->Initialise();
	m_pTxtPlace4->SetFont(kiFontWidth, kiFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlace4->SetPosition(325, 350);
	m_pTxtPlace4->SetDisplay(true);

	m_pTxtPlace5 = new CText;
	m_pTxtPlace5->Initialise();
	m_pTxtPlace5->SetFont(kiFontWidth, kiFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlace5->SetPosition(325, 400);
	m_pTxtPlace5->SetDisplay(true);

	return (true);
}

bool
CHighScoreTable::InitialiseMainMenuButton()
{
	m_pBtnMainMenu = new CButton();
	m_pBtnMainMenu->Initialise(IDB_BUTTON_MAINMENU_SMALL, IDB_INGAME_MENUMASK);
	m_pBtnMainMenu->SetPosition(800, 500);
	m_pBtnMainMenu->UpdateBounds();

	return (true);
}

bool
CHighScoreTable::InitialiseScores()
{
	std::string strPlace1Name;
	int iPlace1Score;

	std::string strPlace2Name;
	int iPlace2Score;

	std::string strPlace3Name;
	int iPlace3Score;

	std::string strPlace4Name;
	int iPlace4Score;

	std::string strPlace5Name;
	int iPlace5Score;

	const char cHighScores[] = "HighScores";

	CIniParser& rIniParser = CApplication::GetInstance().GetIniParser();

	rIniParser.GetValue(cHighScores, "Place1Name", strPlace1Name);
	rIniParser.GetValue(cHighScores, "Place1Score", iPlace1Score);
	rIniParser.GetValue(cHighScores, "Place2Name", strPlace2Name);
	rIniParser.GetValue(cHighScores, "Place2Score", iPlace2Score);
	rIniParser.GetValue(cHighScores, "Place3Name", strPlace3Name);
	rIniParser.GetValue(cHighScores, "Place3Score", iPlace3Score);
	rIniParser.GetValue(cHighScores, "Place4Name", strPlace4Name);
	rIniParser.GetValue(cHighScores, "Place4Score", iPlace4Score);
	rIniParser.GetValue(cHighScores, "Place5Name", strPlace5Name);
	rIniParser.GetValue(cHighScores, "Place5Score", iPlace5Score);


	char* cpBuffer = new char[128];

	sprintf_s(cpBuffer, 64, "1st %s         %d", strPlace1Name.c_str(), iPlace1Score);
	m_pTxtPlace1->SetText(cpBuffer);

	sprintf_s(cpBuffer, 64, "2nd %s         %d", strPlace2Name.c_str(), iPlace2Score);
	m_pTxtPlace2->SetText(cpBuffer);

	sprintf_s(cpBuffer, 64, "3rd %s         %d", strPlace3Name.c_str(), iPlace3Score);
	m_pTxtPlace3->SetText(cpBuffer);

	sprintf_s(cpBuffer, 64, "4th %s         %d", strPlace4Name.c_str(), iPlace4Score);
	m_pTxtPlace4->SetText(cpBuffer);

	sprintf_s(cpBuffer, 64, "5th %s         %d", strPlace5Name.c_str(), iPlace5Score);
	m_pTxtPlace5->SetText(cpBuffer);

	delete cpBuffer;
	cpBuffer = 0;

	return (true);
}

bool
CHighScoreTable::DeinitialiseTitle()
{
	delete m_pSEntTitle;
	m_pSEntTitle = 0;

	return (true);
}

bool
CHighScoreTable::DeinitialiseText()
{
	delete m_pTxtPlace1;
	m_pTxtPlace1 = 0;

	delete m_pTxtPlace2;
	m_pTxtPlace2 = 0;

	delete m_pTxtPlace3;
	m_pTxtPlace3 = 0;

	delete m_pTxtPlace4;
	m_pTxtPlace4 = 0;

	delete m_pTxtPlace5;
	m_pTxtPlace5 = 0;

	return (true);
}

bool
CHighScoreTable::DeinitialiseMainMenuButton()
{
	delete m_pBtnMainMenu;
	m_pBtnMainMenu = 0;

	return (true);
}