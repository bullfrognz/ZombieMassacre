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
#include <iostream>

// Local Includes
#include "resource.h"

// Framework
#include "Application.h"
#include "IniParser.h"
#include "Window.h"
#include "MessageManager.h"

// Core
#include "Text.h"
#include "Button.h"
#include "SpriteEntity.h"

// Game
#include "GameScene.h"

// This Include
#include "SubmitScore.h"

// Static Variables

// Static Function Prototypes

// Implementation

CSubmitScore::CSubmitScore()
: m_iPlace1Score(0)
, m_iPlace2Score(0)
, m_iPlace3Score(0)
, m_iPlace4Score(0)
, m_iPlace5Score(0)
, m_pScore(0)
, m_pPlayerName(0)
{
	CMessageManager& rMessageManager = CApplication::GetInstance().GetGameWindow().GetMsgManager();
	rMessageManager.AddMsgTarget(MSG_KEY_Q_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_W_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_E_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_R_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_T_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_Y_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_U_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_I_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_O_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_P_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_A_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_S_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_D_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_F_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_G_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_H_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_J_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_K_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_L_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_Z_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_X_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_C_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_V_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_B_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_N_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_M_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_BACKSPACE_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_ENTER_DWN, this);


}

CSubmitScore::~CSubmitScore()
{
	CApplication::GetInstance().GetGameWindow().GetMsgManager().RemoveMsgTarget(this);

	Deinitialise();
}


bool
CSubmitScore::Initialise()
{
	InitialiseScores();
		
	m_kcpPlayerName = new char[256];

	m_kcpPlayerName[0] = '\0';

	const int kiFontWidth = 14;
	const int kiFontHeight = 32;

	sprintf_s(m_kcpPlayerName, 256, "Final Score: %d", CGameScene::s_iScoreOfLastGame);

	m_pScore = new CText;
	m_pScore->Initialise();
	m_pScore->SetText(m_kcpPlayerName);
	m_pScore->SetFont(kiFontWidth, kiFontHeight, TEXTWEIGHT_HEAVY);
	m_pScore->SetPosition(325, 200);
	m_pScore->SetDisplay(true);

	m_kcpPlayerName[0] = '\0';

	m_pPlayerName = new CText;
	m_pPlayerName->Initialise();
	m_pPlayerName->SetFont(kiFontWidth, kiFontHeight, TEXTWEIGHT_HEAVY);
	m_pPlayerName->SetPosition(425, 200);
	m_pPlayerName->SetDisplay(true);

	m_pMessage = new CText;
	m_pMessage->Initialise();
	m_pMessage->SetFont(kiFontWidth, kiFontHeight, TEXTWEIGHT_HEAVY);
	m_pMessage->SetPosition(425, 200);
	m_pMessage->SetDisplay(true);

	return (true);
}

bool
CSubmitScore::Deinitialise()
{
	delete m_pScore;
	m_pScore = 0;

	delete m_pPlayerName;
	m_pPlayerName = 0;

	delete m_kcpPlayerName;
	m_kcpPlayerName = 0;

	delete m_pMessage;
	m_pMessage = 0;

	return (true);
}

void
CSubmitScore::Process(float _fDeltatick)
{
	m_pScore->Process(_fDeltatick);
	m_pPlayerName->SetText(m_kcpPlayerName);
	m_pPlayerName->Process(_fDeltatick);
}

void
CSubmitScore::Draw()
{
	m_pScore->Draw();
	m_pPlayerName->Draw();
}

void
CSubmitScore::AddLetter(char _cLetter)
{
	if (strlen(m_kcpPlayerName) <= 12)
	{
		sprintf_s(m_kcpPlayerName, 256, "%s%c", m_kcpPlayerName, _cLetter);
		
	}
}

void 
CSubmitScore::Backspace()
{
	if (strlen(m_kcpPlayerName) >= 1)
	{
		m_kcpPlayerName[strlen(m_kcpPlayerName) - 1] = '\0';
	}
}

void 
CSubmitScore::AcceptName()
{
	CApplication::GetInstance().GetGameWindow().SetScene(SCENE_HIGHSCORETABLE);
}

bool
CSubmitScore::InitialiseScores()
{
	int m_iPlace1Score = 0;
	int m_iPlace2Score = 0;
	int m_iPlace3Score = 0;
	int m_iPlace4Score = 0;
	int m_iPlace5Score = 0;

	const char cHighScores[] = "HighScores";

	CIniParser& rIniParser = CApplication::GetInstance().GetIniParser();

	rIniParser.GetValue(cHighScores, "Place1Score", m_iPlace1Score);
	rIniParser.GetValue(cHighScores, "Place2Score", m_iPlace2Score);
	rIniParser.GetValue(cHighScores, "Place3Score", m_iPlace3Score);
	rIniParser.GetValue(cHighScores, "Place4Score", m_iPlace4Score);
	rIniParser.GetValue(cHighScores, "Place5Score", m_iPlace5Score);

	if (CGameScene::s_iScoreOfLastGame < m_iPlace1Score &&
		CGameScene::s_iScoreOfLastGame < m_iPlace2Score &&
		CGameScene::s_iScoreOfLastGame < m_iPlace3Score &&
		CGameScene::s_iScoreOfLastGame < m_iPlace4Score &&
		CGameScene::s_iScoreOfLastGame < m_iPlace5Score)
	{
		//m_pMessage->SetText("Sorry you did get a high score.");
		Sleep(3000);
		CApplication::GetInstance().GetGameWindow().SetScene(SCENE_MAINMENU);
	}
	else
	{
		//m_pMessage->SetText("You reached a new high score! Enter your name and press enter");
	}

	return (true);
}

void
CSubmitScore::HandleMessage(EMESSAGECODE _eMessageCode, WPARAM _wParam, LPARAM _lParam)
{
	switch (_eMessageCode)
	{
		case MSG_KEY_Q_DWN:
			AddLetter('Q');
			break;

		case MSG_KEY_W_DWN:
			AddLetter('W');
			break;

		case MSG_KEY_E_DWN:
			AddLetter('E');
			break;

		case MSG_KEY_R_DWN:
			AddLetter('R');
			break;

		case MSG_KEY_T_DWN:
			AddLetter('T');
			break;

		case MSG_KEY_Y_DWN:
			AddLetter('Y');
			break;

		case MSG_KEY_U_DWN:
			AddLetter('U');
			break;

		case MSG_KEY_I_DWN:
			AddLetter('I');
			break;

		case MSG_KEY_O_DWN:
			AddLetter('O');
			break;

		case MSG_KEY_P_DWN:
			AddLetter('P');
			break;

		case MSG_KEY_A_DWN:
			AddLetter('A');
			break;

		case MSG_KEY_S_DWN:
			AddLetter('S');
			break;

		case MSG_KEY_D_DWN:
			AddLetter('D');
			break;

		case MSG_KEY_F_DWN:
			AddLetter('F');
			break;

		case MSG_KEY_G_DWN:
			AddLetter('G');
			break;

		case MSG_KEY_H_DWN:
			AddLetter('H');
			break;

		case MSG_KEY_J_DWN:
			AddLetter('J');
			break;

		case MSG_KEY_K_DWN:
			AddLetter('K');
			break;

		case MSG_KEY_L_DWN:
			AddLetter('L');
			break;

		case MSG_KEY_Z_DWN:
			AddLetter('Z');
			break;

		case MSG_KEY_X_DWN:
			AddLetter('X');
			break;

		case MSG_KEY_C_DWN:
			AddLetter('C');
			break;

		case MSG_KEY_V_DWN:
			AddLetter('V');
			break;

		case MSG_KEY_B_DWN:
			AddLetter('B');
			break;

		case MSG_KEY_N_DWN:
			AddLetter('N');
			break;

		case MSG_KEY_M_DWN:
			AddLetter('M');
			break;

		case MSG_KEY_BACKSPACE_DWN:
			Backspace();
			break;

		case MSG_KEY_ENTER_DWN:
			AcceptName();
			break;

		default:
			break;
	}
}