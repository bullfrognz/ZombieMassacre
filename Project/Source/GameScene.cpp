//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   GameScene.cpp
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
#include "IniParser.h"
#include "MessageManager.h"
#include "Window.h"
#include "DebugDialog.h"

// Core
#include "Button.h"
#include "Projectile.h"
#include "BloodSplatter.h"
#include "SpriteEntity.h"
#include "Text.h"

// Game
#include "Turret.h"
#include "Zombie.h"
#include "Bullet.h"
#include "HolyGrenade.h"
#include "Weapon.h"

// This Include
#include "GameScene.h"

// Static Variables
int CGameScene::s_iScoreOfLastGame = 0;

// Static Function Prototypes

// Implementation
CGameScene::CGameScene()
: cTextBuffer(0)
, m_pTurret(0)
, m_pBtnOpenMenu(0)
, m_pBtnContinue(0)
, m_pBtnMainMenu(0)
, m_pPlayerInfoBar(0)
, m_pTxtPlayerHealth(0)
, m_pTxtPlayerBulletDamage(0)
, m_pTxtPlayerScore(0)
, m_pTxtPlayerCriticalRating(0)
, m_pTxtPlayerFireRate(0)
, m_pTxtPlayerNumGrenades(0)
, m_pPlayerInfoBarBottom(0)
, m_pTxtGameLevel(0)
, m_pTxtPlayerExperience(0)
, m_pTxtPlayerExperienceRequired(0)
, m_pTxtPlayerNumUpgradePoints(0)
, m_pTxtPlayerNumUpgradePointsExt(0)
, m_pEtyUpgradeMenu(0)
, m_pTxtButtetDamage(0)
, m_pTxtCriticleRating(0)
, m_pTxtFiringRate(0)
, m_pTxtHealth(0)
, m_pTxtNumUpgradePointsLeft(0)
, m_pBtnButtetDamage(0)
, m_pBtnCriticleRating(0)
, m_pBtnFiringRate(0)
, m_pBtnHealth(0)
, m_mBtnCloseUpgradeMenu(0)
, m_iPlayerScore(0)
, m_iGameLevel(0)
, m_fLevelTimeElapsed(0.0f)
, m_fNextLevelTime(0.0f)
, m_fSpawnTimeElapsed(0.0f)
, m_fZombieSpawnRate(0.0f)
, m_iNumZombiesAlive(0)
, m_bGameMenuOpen(false)
, m_bTurretUpgradeMenuOpen(false)
, m_bGameOver(false)
{
	ZeroMemory(&m_rectBounds, sizeof(RECT));

	s_iScoreOfLastGame = 0;
}

CGameScene::~CGameScene()
{
	s_iScoreOfLastGame = m_iPlayerScore;

	Deinitialise();
}

bool
CGameScene::Initialise()
{
	InitialiseTextBuffer();
	IntiailiseLevel();
	InitialiseBounds();
	InitialiseTurret();
	InitialisePlayerInfoBar();
	InitialisePlayerInfoBarBottom();
	InitialiseTurretUpgradeMenu();
	InitialiseGameMenu();
	InitialiseZombies();
	IntiialiseGameText();
	InitialiseBloodSplatter();
	InitialiseTurretUpgradeMenuPreOpen();

	CMessageManager& rMessageManager = CApplication::GetInstance().GetGameWindow().GetMsgManager();
	rMessageManager.AddMsgTarget(MSG_KEY_ESC_DWN, this);

	CDebugDialog::GetInstance().SetGameScene(this);
	
	return true;
}

bool
CGameScene::Deinitialise()
{
	DeinitialiseTextBuffer();
	DeinitialisePlayerInfoBar();
	DeinitialisePlayerInfoBarBottom();
	DeinitialiseTurretUpgradeMenu();
	DeinitialiseGameMenu();
	DeinitialiseTurret();
	DeinitialiseZombies();
	DeinitialiseGameText();
	DeinitialiseBloodSplatter();
	DeinitialiseTextBuffer();

	CDebugDialog::GetInstance().ForgetTurret();
	CDebugDialog::GetInstance().ForgetGameScene();

	CApplication::GetInstance().GetGameWindow().GetMsgManager().RemoveMsgTarget(this);

	return (true);
}

#include <windows.h>

void
CGameScene::Process(float _fDeltaTick)
{
	ProcessPlayerInfoBar(_fDeltaTick);
	ProcessPlayerInfoBarBottom(_fDeltaTick);
	ProcessGameText(_fDeltaTick);

	if (m_bTurretUpgradeMenuOpen == false && m_bGameMenuOpen == false)
	{
		ProcessLevel(_fDeltaTick);
		ProcessTurret(_fDeltaTick);
		ProcessZombies(_fDeltaTick);
		ProcessTurretZombieCollision();
		ProcessBulletZombieCollision();
		ProcessGrenadeZombieCollision();
		ProcessBloodSplatter(_fDeltaTick);
	}


	if (m_bGameMenuOpen == true)
	{
		ProcessGameMenu(_fDeltaTick);
	}
	else if (m_bTurretUpgradeMenuOpen == true)
	{
		ProcessTurretUpgradeMenu(_fDeltaTick);
	}

	if (m_bGameOver == true)
	{
		CApplication::GetInstance().GetGameWindow().SetScene(SCENE_MAINMENU);
	}
}

void
CGameScene::Draw()
{
	DrawBloodSplatter();
	DrawZombies();
	m_pTurret->Draw();
	DrawGameText();
	DrawPlayerInfoBar();
	DrawPlayerInfoBarBottom();

	if (m_bTurretUpgradeMenuOpen == true)
	{
		DrawTurretUpgradeMenu();
	}

	if (m_bGameMenuOpen == true)
	{
		DrawGameMenu();
	}
}

bool
CGameScene::InitialiseTextBuffer()
{
	cTextBuffer = new char[g_iTextBufferSize];

	return (true);
}

bool
CGameScene::IntiailiseLevel()
{
	m_fNextLevelTime = 30;
	m_iGameLevel = 1;

	return (true);
}

bool
CGameScene::InitialiseBounds()
{
	int iWindowWidth  = CApplication::GetInstance().GetGameWindow().GetWidth();
	int iWindowHeight = CApplication::GetInstance().GetGameWindow().GetHeight();

	m_rectBounds.top = 80;
	m_rectBounds.bottom = iWindowHeight;
	m_rectBounds.left = 0;
	m_rectBounds.right = iWindowWidth;

	return (true);
}

bool
CGameScene::InitialisePlayerInfoBar()
{
	const int iWindowWidth  = CApplication::GetInstance().GetGameWindow().GetWidth();

	m_pPlayerInfoBar = new CSpriteEntity;
	m_pPlayerInfoBar->Initialise(IDB_PLAYERINFOBAR, IDB_PLAYERINFOBARMASK);
	m_pPlayerInfoBar->SetPosition(iWindowWidth / 2, 40);

	const int iFontWidth = 13;
	const int iFontHeight = 26;

	m_pTxtPlayerHealth = new CText();
	m_pTxtPlayerHealth->Initialise();
	m_pTxtPlayerHealth->SetPosition(125, 11);
	m_pTxtPlayerHealth->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlayerHealth->SetDisplay(true);

	m_pTxtPlayerScore = new CText();
	m_pTxtPlayerScore->Initialise();
	m_pTxtPlayerScore->SetPosition(125, 44);
	m_pTxtPlayerScore->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlayerScore->SetDisplay(true);

	m_pTxtPlayerBulletDamage = new CText();
	m_pTxtPlayerBulletDamage->Initialise();
	m_pTxtPlayerBulletDamage->SetPosition(460, 11);
	m_pTxtPlayerBulletDamage->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlayerBulletDamage->SetDisplay(true);

	m_pTxtPlayerCriticalRating = new CText();
	m_pTxtPlayerCriticalRating->Initialise();
	m_pTxtPlayerCriticalRating->SetPosition(460, 44);
	m_pTxtPlayerCriticalRating->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlayerCriticalRating->SetDisplay(true);

	m_pTxtPlayerFireRate = new CText();
	m_pTxtPlayerFireRate->Initialise();
	m_pTxtPlayerFireRate->SetPosition(720, 11);
	m_pTxtPlayerFireRate->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlayerFireRate->SetDisplay(true);

	m_pTxtPlayerNumGrenades = new CText();
	m_pTxtPlayerNumGrenades->Initialise();
	m_pTxtPlayerNumGrenades->SetPosition(720, 44);
	m_pTxtPlayerNumGrenades->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlayerNumGrenades->SetDisplay(true);

	m_pBtnOpenMenu = new CButton();
	m_pBtnOpenMenu->Initialise(IDB_INGAME_MENU, IDB_INGAME_MENUMASK);
	m_pBtnOpenMenu->SetPosition(iWindowWidth - 100, 40);
	m_pBtnOpenMenu->UpdateBounds();

	return (true);
}

bool
CGameScene::InitialisePlayerInfoBarBottom()
{
	const int iWindowWidth  = CApplication::GetInstance().GetGameWindow().GetWidth();
	const int iWindowHeight = CApplication::GetInstance().GetGameWindow().GetHeight();

	m_pPlayerInfoBarBottom = new CSpriteEntity;
	m_pPlayerInfoBarBottom->Initialise(IDB_PLAYERINFOBAR_BOTTOM, IDB_PLAYERINFOBAR_BOTTOMMASK);
	m_pPlayerInfoBarBottom->SetPosition(iWindowWidth / 2, iWindowHeight - 43);

	const int iFontWidth = 10;
	const int iFontHeight = 24;

	const int iPaddingBottom = iWindowHeight - 53;

	m_pTxtGameLevel = new CText();
	m_pTxtGameLevel->Initialise();
	m_pTxtGameLevel->SetPosition(135, iPaddingBottom);
	m_pTxtGameLevel->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtGameLevel->SetDisplay(true);

	m_pTxtPlayerExperience = new CText();
	m_pTxtPlayerExperience->Initialise();
	m_pTxtPlayerExperience->SetPosition(300, iPaddingBottom);
	m_pTxtPlayerExperience->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlayerExperience->SetDisplay(true);

	m_pTxtPlayerExperienceRequired = new CText();
	m_pTxtPlayerExperienceRequired->Initialise();
	m_pTxtPlayerExperienceRequired->SetPosition(538, iPaddingBottom);
	m_pTxtPlayerExperienceRequired->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlayerExperienceRequired->SetDisplay(true);

	m_pTxtPlayerNumUpgradePoints = new CText();
	m_pTxtPlayerNumUpgradePoints->Initialise();
	m_pTxtPlayerNumUpgradePoints->SetPosition(820, iPaddingBottom);
	m_pTxtPlayerNumUpgradePoints->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlayerNumUpgradePoints->SetDisplay(true);

	m_pTxtPlayerNumUpgradePointsExt = new CText();
	m_pTxtPlayerNumUpgradePointsExt->Initialise();
	m_pTxtPlayerNumUpgradePointsExt->SetText("PRESS 'R'");
	m_pTxtPlayerNumUpgradePointsExt->SetPosition(865, iPaddingBottom);
	m_pTxtPlayerNumUpgradePointsExt->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtPlayerNumUpgradePointsExt->SetTextColour(TEXTCOLOUR_ORANGE);
	m_pTxtPlayerNumUpgradePointsExt->SetDisplay(false);

	return (true);
}


bool
CGameScene::InitialiseTurretUpgradeMenu()
{
	const int iWindowWidth  = CApplication::GetInstance().GetGameWindow().GetWidth();

	const int iFontWidth = 9;
	const int iFontHeight = 19;

	const int iBulletDamageIncrement = m_pTurret->GetWeapon().GetBulletDamageIncrement();
	const int iCriticalRatingIncrement = m_pTurret->GetWeapon().GetCriticalRatingIncrement();
	const float fFiringRateIncrement = m_pTurret->GetFireRateIncrement();
	const int iMaxHealthIncrement = m_pTurret->GetMaxHealthIncrement();

	m_pEtyUpgradeMenu = new CSpriteEntity();
	m_pEtyUpgradeMenu->Initialise(IDB_UPGRADEMENU, IDB_UPGRADEMENUMASK);
	m_pEtyUpgradeMenu->SetPosition(iWindowWidth / 2, 300);

	sprintf_s(cTextBuffer, g_iTextBufferSize, "Increase Bullet Damage by %d", iBulletDamageIncrement);
	m_pTxtButtetDamage = new CText();
	m_pTxtButtetDamage->Initialise();
	m_pTxtButtetDamage->SetText(cTextBuffer);
	m_pTxtButtetDamage->SetPosition(290, 225);
	m_pTxtButtetDamage->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtButtetDamage->SetDisplay(true);

	sprintf_s(cTextBuffer, g_iTextBufferSize, "Increase Critical Rating by %d", iCriticalRatingIncrement);
	m_pTxtCriticleRating = new CText();
	m_pTxtCriticleRating->Initialise();
	m_pTxtCriticleRating->SetText(cTextBuffer);
	m_pTxtCriticleRating->SetPosition(290, 275);
	m_pTxtCriticleRating->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtCriticleRating->SetDisplay(true);

	sprintf_s(cTextBuffer, g_iTextBufferSize, "Increase Firing Rate by %0.2fs", fFiringRateIncrement);
	m_pTxtFiringRate = new CText();
	m_pTxtFiringRate->Initialise();
	m_pTxtFiringRate->SetText(cTextBuffer);
	m_pTxtFiringRate->SetPosition(290, 325);
	m_pTxtFiringRate->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtFiringRate->SetDisplay(true);

	m_pTxtHealth = new CText();
	m_pTxtHealth->Initialise();
	m_pTxtHealth->SetText("Restore Health to 100%");
	m_pTxtHealth->SetPosition(290, 375);
	m_pTxtHealth->SetFont(iFontWidth, iFontHeight, TEXTWEIGHT_HEAVY);
	m_pTxtHealth->SetDisplay(true);

	m_pTxtNumUpgradePointsLeft = new CText();
	m_pTxtNumUpgradePointsLeft->Initialise();
	m_pTxtNumUpgradePointsLeft->SetPosition(427, 415);
	m_pTxtNumUpgradePointsLeft->SetFont(12, 26, TEXTWEIGHT_HEAVY);
	m_pTxtNumUpgradePointsLeft->SetTextColour(TEXTCOLOUR_BLUE);
	m_pTxtNumUpgradePointsLeft->SetDisplay(true);

	m_pBtnButtetDamage = new CButton;
	m_pBtnButtetDamage->Initialise(IDB_BUTTON_SELECT, IDB_BUTTON_SELECTMASK);
	m_pBtnButtetDamage->SetPosition(700, 233);
	m_pBtnButtetDamage->UpdateBounds();

	m_pBtnCriticleRating = new CButton;
	m_pBtnCriticleRating->Initialise(IDB_BUTTON_SELECT, IDB_BUTTON_SELECTMASK);
	m_pBtnCriticleRating->SetPosition(700, 283);
	m_pBtnCriticleRating->UpdateBounds();

	m_pBtnFiringRate = new CButton;
	m_pBtnFiringRate->Initialise(IDB_BUTTON_SELECT, IDB_BUTTON_SELECTMASK);
	m_pBtnFiringRate->SetPosition(700, 333);
	m_pBtnFiringRate->UpdateBounds();

	m_pBtnHealth = new CButton;
	m_pBtnHealth->Initialise(IDB_BUTTON_SELECT, IDB_BUTTON_SELECTMASK);
	m_pBtnHealth->SetPosition(700, 383);
	m_pBtnHealth->UpdateBounds();

	m_mBtnCloseUpgradeMenu = new CButton;
	m_mBtnCloseUpgradeMenu->Initialise(IDB_BUTTON_CLOSE, IDB_BUTTON_SELECTMASK);
	m_mBtnCloseUpgradeMenu->SetPosition(700, 428);
	m_mBtnCloseUpgradeMenu->UpdateBounds();
	
	CMessageManager& rMessageManager = CApplication::GetInstance().GetGameWindow().GetMsgManager();
	rMessageManager.AddMsgTarget(MSG_KEY_R_DWN, this);

	return (true);
}

bool 
CGameScene::InitialiseGameMenu()
{
	const int iWindowWidth  = CApplication::GetInstance().GetGameWindow().GetWidth();

	int iHalfWindowWidth = iWindowWidth / 2;

	m_pBtnContinue = new CButton();
	m_pBtnContinue->Initialise(IDB_BUTTON_CONTINUE, IDB_BUTTON_MAINMENUMASK);
	m_pBtnContinue->SetPosition(iHalfWindowWidth, 350);
	m_pBtnContinue->UpdateBounds();

	m_pBtnMainMenu = new CButton();
	m_pBtnMainMenu->Initialise(IDB_BUTTON_MAINMENU, IDB_BUTTON_MAINMENUMASK);
	m_pBtnMainMenu->SetPosition(iHalfWindowWidth, 500);
	m_pBtnMainMenu->UpdateBounds();

	return (true);
}

bool
CGameScene::InitialiseTurret()
{
	int iWindowWidth  = CApplication::GetInstance().GetGameWindow().GetWidth();
	int iWindowHeight = CApplication::GetInstance().GetGameWindow().GetHeight();

	m_pTurret = new CTurret();
	m_pTurret->Initialise();
	m_pTurret->SetPosition(iWindowWidth / 2, iWindowHeight / 2);
	m_pTurret->SetPlayBounds(m_rectBounds);
	m_pTurret->SetAlive(true);

	CDebugDialog::GetInstance().SetTurret(m_pTurret);

	return (true);
}

bool
CGameScene::InitialiseZombies()
{
	float fZombieSpawnRate = 0.0f;

	CIniParser& rIniParser = CApplication::GetInstance().GetIniParser();
	rIniParser.GetValue("Zombie", "SpawnRate", fZombieSpawnRate);

	// Zombie Spawn Rate
	m_fZombieSpawnRate = fZombieSpawnRate;

	// Initialise Zombies
	int iZombieType = 0;
	for (int i = 0; i < g_iMaxZombies; ++i)
	{
		m_pZombie[i] = new CZombie;

		iZombieType = GenerateRandomNumber(1, 11);

		if (iZombieType >= 1 && iZombieType <= 7)
		{
			m_pZombie[i]->Initialise(ZOMBIE_GREEN);
		}
		else if (iZombieType <= 9)
		{
			m_pZombie[i]->Initialise(ZOMBIE_ORANGE);
		}
		else
		{
			m_pZombie[i]->Initialise(ZOMBIE_RED);
		}
		
		m_pZombie[i]->SetAlive(false);
	}

	return (true);
}

bool
CGameScene::IntiialiseGameText()
{
	//Initialse Game Text
	for (int i = 0; i < g_iMaxGameText; ++i)
	{
		m_pGameText[i] = new CText;
		m_pGameText[i]->Initialise();
		m_pGameText[i]->SetTextAlign(TEXTALIGN_CENTER);
		m_pGameText[i]->SetFont(11, 23, TEXTWEIGHT_HEAVY);
	}

	return (true);
}

bool
CGameScene::InitialiseBloodSplatter()
{
	// Initialise Blood Splatter
	for (int i = 0; i < g_iMaxBloodSplatter; ++i)
	{
		m_pBloodSplatter[i] = new CBloodSplatter;
		m_pBloodSplatter[i]->Initialise();
	}

	return (true);
}

bool
CGameScene::InitialiseTurretUpgradeMenuPreOpen()
{
	if (m_pTurret->GetNumUpgradePoints() > 0)
	{
		CApplication::GetInstance().GetGameWindow().GetMsgManager().SendMsgToTargets(MSG_KEY_R_DWN, NULL, NULL);
	}

	return (true);
}

bool
CGameScene::DeinitialiseTextBuffer()
{
	delete cTextBuffer;
	cTextBuffer = 0;

	return (true);
}

bool
CGameScene::DeinitialisePlayerInfoBar()
{
	delete m_pPlayerInfoBar;
	m_pPlayerInfoBar = 0;

	delete m_pTxtPlayerHealth;
	m_pTxtPlayerHealth = 0;

	delete m_pTxtPlayerBulletDamage;
	m_pTxtPlayerBulletDamage = 0;

	delete m_pTxtPlayerScore;
	m_pTxtPlayerScore = 0;

	delete m_pTxtPlayerCriticalRating;
	m_pTxtPlayerCriticalRating = 0;

	delete m_pTxtPlayerFireRate;
	m_pTxtPlayerFireRate = 0;

	delete m_pTxtPlayerNumGrenades;
	m_pTxtPlayerNumGrenades = 0;

	delete m_pBtnOpenMenu;
	m_pBtnOpenMenu = 0;

	return (true);
}

bool
CGameScene::DeinitialisePlayerInfoBarBottom()
{
	delete m_pPlayerInfoBarBottom;
	m_pPlayerInfoBarBottom = 0;

	delete m_pTxtGameLevel;
	m_pTxtGameLevel = 0;

	delete m_pTxtPlayerExperience;
	m_pTxtPlayerExperience = 0;

	delete m_pTxtPlayerExperienceRequired;
	m_pTxtPlayerExperienceRequired = 0;

	delete m_pTxtPlayerNumUpgradePoints;
	m_pTxtPlayerNumUpgradePoints = 0;

	delete m_pTxtPlayerNumUpgradePointsExt;
	m_pTxtPlayerNumUpgradePointsExt = 0;

	return (true);
}

bool
CGameScene::DeinitialiseTurretUpgradeMenu()
{
	delete m_pTxtNumUpgradePointsLeft;
	m_pTxtNumUpgradePointsLeft = 0;

	delete m_pEtyUpgradeMenu;
	m_pEtyUpgradeMenu = 0;
	
	delete m_pTxtButtetDamage;
	m_pTxtButtetDamage = 0;

	delete m_pTxtCriticleRating;
	m_pTxtCriticleRating = 0;

	delete m_pTxtFiringRate;
	m_pTxtFiringRate = 0;

	delete m_pTxtHealth;
	m_pTxtHealth = 0;

	delete m_pBtnButtetDamage;
	m_pBtnButtetDamage = 0;

	delete m_pBtnCriticleRating;
	m_pBtnCriticleRating = 0;

	delete m_pBtnFiringRate;
	m_pBtnFiringRate = 0;

	delete m_pBtnHealth;
	m_pBtnHealth = 0;

	delete m_mBtnCloseUpgradeMenu;
	m_mBtnCloseUpgradeMenu = 0;

	return (true);
}

bool
CGameScene::DeinitialiseGameMenu()
{
	delete m_pBtnContinue;
	m_pBtnContinue = 0;

	delete m_pBtnMainMenu;
	m_pBtnMainMenu = 0;

	return (true);
}

bool
CGameScene::DeinitialiseTurret()
{
	delete m_pTurret;
	m_pTurret = 0;

	return (true);
}

bool
CGameScene::DeinitialiseZombies()
{
	// Delete Zombies
	for (int i = 0; i < g_iMaxZombies; ++i)
	{
		delete m_pZombie[i];
		m_pZombie[i] = 0;
	}

	return (true);
}

bool
CGameScene::DeinitialiseGameText()
{
	// Delete Game Text
	for (int i = 0; i < g_iMaxGameText; ++i)
	{
		delete m_pGameText[i];
		m_pGameText[i] = 0;
	}

	return (true);
}

bool
CGameScene::DeinitialiseBloodSplatter()
{
	// Delete Blood Splatter
	for (int i = 0; i < g_iMaxBloodSplatter; ++i)
	{
		delete m_pBloodSplatter[i];
		m_pBloodSplatter[i] = 0;
	}

	return (true);
}

void
CGameScene::ProcessLevel(float _fDeltaTick)
{
	// Increase Elapsed Time
	m_fLevelTimeElapsed += _fDeltaTick;

	if (m_fLevelTimeElapsed > m_fNextLevelTime)
	{
		++ m_iGameLevel;

		if (m_fNextLevelTime > 15.0f)
		{
			m_fNextLevelTime -= 0.25f;
		}
		m_fZombieSpawnRate -= 0.025f;

		m_fLevelTimeElapsed = 0.0f;
	}
}

void
CGameScene::ProcessTurret(float _fDeltaTick)
{
	if (m_pTurret->IsAlive() == false)
	{
		m_bGameOver = true;
	}

	if (m_pTurret->HasLeveledup() == true)
	{
		sprintf_s(cTextBuffer, g_iTextBufferSize, "+1 UPGRADE POINT!");
		DisplayGameText(cTextBuffer, m_pTurret->GetPositionX(), m_pTurret->GetPositionY() - 30, 0, 55, 200, TEXTCOLOUR_LBLUE);
	}

	m_pTurret->Process(_fDeltaTick);
}

void
CGameScene::ProcessPlayerInfoBar(float _fDeltaTick)
{
	int iTurretHealth = m_pTurret->GetCurrentHealth();
	float fFireRate   = m_pTurret->GetFireRate();

	CWeapon& rWeapon = (*m_pTurret).GetWeapon();
	int iTurretDamageMin = rWeapon.GetBulletDamageMin();
	int iTurretDamageMax = rWeapon.GetBulletDamageMax();
	int iTurretCriticalRating = rWeapon.GetCriticalRating();
	int iWeaponGrenadeAmmo = rWeapon.GetHolyGrenadeAmmo();

	sprintf_s(cTextBuffer, g_iTextBufferSize, "%d", iTurretHealth);
	(*m_pTxtPlayerHealth).SetText(cTextBuffer);

	sprintf_s(cTextBuffer, g_iTextBufferSize, "%d", m_iPlayerScore);
	(*m_pTxtPlayerScore).SetText(cTextBuffer);

	sprintf_s(cTextBuffer, g_iTextBufferSize, "%d - %d", iTurretDamageMin, iTurretDamageMax);
	(*m_pTxtPlayerBulletDamage).SetText(cTextBuffer);

	sprintf_s(cTextBuffer, g_iTextBufferSize, "%d%%", iTurretCriticalRating);
	(*m_pTxtPlayerCriticalRating).SetText(cTextBuffer);

	sprintf_s(cTextBuffer, g_iTextBufferSize, "%.2fs", fFireRate);
	(*m_pTxtPlayerFireRate).SetText(cTextBuffer);

	sprintf_s(cTextBuffer, g_iTextBufferSize, "%d", iWeaponGrenadeAmmo);
	(*m_pTxtPlayerNumGrenades).SetText(cTextBuffer);

	m_pPlayerInfoBar->Process(_fDeltaTick);
	m_pTxtPlayerHealth->Process(_fDeltaTick);
	m_pTxtPlayerBulletDamage->Process(_fDeltaTick);
	m_pTxtPlayerScore->Process(_fDeltaTick);
	m_pTxtPlayerCriticalRating->Process(_fDeltaTick);
	m_pTxtPlayerFireRate->Process(_fDeltaTick);
	m_pTxtPlayerNumGrenades->Process(_fDeltaTick);

	m_pBtnOpenMenu->Process(_fDeltaTick);

	if (m_pBtnOpenMenu->HasBeenClicked() == true)
	{
		m_bGameMenuOpen = true;
	}
}

void
CGameScene::ProcessPlayerInfoBarBottom(float _fDeltaTick)
{
	const int iCurrentXp = m_pTurret->GetCurrentXp();
	const int iXpRequired = m_pTurret->GetXpRequired();
	const int iNumUpgradePoints = m_pTurret->GetNumUpgradePoints();

	sprintf_s(cTextBuffer, g_iTextBufferSize, "%d", m_iGameLevel);
	m_pTxtGameLevel->SetText(cTextBuffer);

	sprintf_s(cTextBuffer, g_iTextBufferSize, "%d", iCurrentXp);
	m_pTxtPlayerExperience->SetText(cTextBuffer);

	sprintf_s(cTextBuffer, g_iTextBufferSize, "%d XP", iXpRequired);
	m_pTxtPlayerExperienceRequired->SetText(cTextBuffer);

	sprintf_s(cTextBuffer, g_iTextBufferSize, "%d", iNumUpgradePoints);
	m_pTxtPlayerNumUpgradePoints->SetText(cTextBuffer);

	m_pPlayerInfoBarBottom->Process(_fDeltaTick);
	m_pTxtGameLevel->Process(_fDeltaTick);
	m_pTxtPlayerExperience->Process(_fDeltaTick);
	m_pTxtPlayerExperienceRequired->Process(_fDeltaTick);
	m_pTxtPlayerNumUpgradePoints->Process(_fDeltaTick);
	m_pTxtPlayerNumUpgradePointsExt->Process(_fDeltaTick);

	if (iNumUpgradePoints > 0)
	{
		m_pTxtPlayerNumUpgradePointsExt->SetDisplay(true);
	}
	else
	{
		m_pTxtPlayerNumUpgradePointsExt->SetDisplay(false);
	}
}


void
CGameScene::ProcessTurretUpgradeMenu(float _fDeltaTick)
{
	m_pBtnButtetDamage->Process(_fDeltaTick);
	m_pBtnCriticleRating->Process(_fDeltaTick);
	m_pBtnFiringRate->Process(_fDeltaTick);
	m_pBtnHealth->Process(_fDeltaTick);
	m_mBtnCloseUpgradeMenu->Process(_fDeltaTick);

	const bool bSelBulletDamage   = m_pBtnButtetDamage->HasBeenClicked();
	const bool bSelCriticalRating = m_pBtnCriticleRating->HasBeenClicked();
	const bool bSelFiringRate     = m_pBtnFiringRate->HasBeenClicked();
	const bool bSelIncreaseHealth = m_pBtnHealth->HasBeenClicked();
	const bool bSelCloseMenu      = m_mBtnCloseUpgradeMenu->HasBeenClicked();

	if (true == bSelCloseMenu)
	{
		m_bTurretUpgradeMenuOpen = false;
		return ;
	}

	if (true == bSelBulletDamage)
	{
		m_pTurret->GetWeapon().UpgradeBulletdamage();
		m_pTurret->UpdateNumUpgradePoints(-1);

		sprintf_s(cTextBuffer, g_iTextBufferSize, "+%d DAMAGE!", m_pTurret->GetWeapon().GetBulletDamageIncrement());
		DisplayGameText(cTextBuffer, m_pTurret->GetPositionX(), m_pTurret->GetPositionY(), 0, 55, 200, TEXTCOLOUR_LBLUE);
	}
	else if (true == bSelCriticalRating)
	{
		const int iCriticalRating = m_pTurret->GetWeapon().GetCriticalRating();
		
		if (iCriticalRating < 100)
		{
			m_pTurret->GetWeapon().UpgradeCriticalRating();
			m_pTurret->UpdateNumUpgradePoints(-1);

			sprintf_s(cTextBuffer, g_iTextBufferSize, "+%d CRITICAL CHANCE!", m_pTurret->GetWeapon().GetCriticalRatingIncrement());
			DisplayGameText(cTextBuffer, m_pTurret->GetPositionX(), m_pTurret->GetPositionY(), 0, 55, 200, TEXTCOLOUR_LBLUE);
		}

		if (m_pTurret->GetWeapon().GetCriticalRating() >= 100)
		{
			m_pBtnCriticleRating->SetDisplay(false);
			m_pTxtCriticleRating->SetFontStrikeOut(true);
		}
	}
	else if (true == bSelFiringRate)
	{
		const float fFiringRate = (*m_pTurret).GetFireRate();
		const float fFiringRateIncrement = (*m_pTurret).GetFireRateIncrement();

		if ((fFiringRate + fFiringRateIncrement) > 0.0f)
		{
			m_pTurret->UpdateFireRate(fFiringRateIncrement);
			m_pTurret->UpdateNumUpgradePoints(-1);

			sprintf_s(cTextBuffer, g_iTextBufferSize, "%.2f FIRE INTERVAL!", fFiringRateIncrement);
			DisplayGameText(cTextBuffer, m_pTurret->GetPositionX(), m_pTurret->GetPositionY(), 0, 55, 200, TEXTCOLOUR_LBLUE);
		}

		if ((m_pTurret->GetFireRate() + fFiringRateIncrement) <= 0.0f)
		{
			m_pBtnFiringRate->SetDisplay(false);
			m_pTxtFiringRate->SetFontStrikeOut(true);
		}
	}
	else if (true == bSelIncreaseHealth)
	{
		m_pTurret->ReplenishCurrentHealth();
		m_pTurret->UpdateNumUpgradePoints(-1);

		sprintf_s(cTextBuffer, g_iTextBufferSize, "RESTORED HEALTH!");
		DisplayGameText(cTextBuffer, m_pTurret->GetPositionX(), m_pTurret->GetPositionY(), 0, 55, 200, TEXTCOLOUR_LBLUE);
	}

	const int iNumUpgradePoints = m_pTurret->GetNumUpgradePoints();
	sprintf_s(cTextBuffer, g_iTextBufferSize, "%d", iNumUpgradePoints);
	m_pTxtNumUpgradePointsLeft->SetText(cTextBuffer);

	if (m_pTurret->GetNumUpgradePoints() == 0)
	{
		m_bTurretUpgradeMenuOpen = false;
	}
}

void
CGameScene::ProcessGameMenu(float _fDeltaTick)
{
	m_pBtnContinue->Process(_fDeltaTick);
	m_pBtnMainMenu->Process(_fDeltaTick);

	if (m_pBtnContinue->HasBeenClicked() == true)
	{
		m_bGameMenuOpen = false;
	}
	else if (m_pBtnMainMenu->HasBeenClicked() == true)
	{
		CApplication::GetInstance().GetGameWindow().SetScene(SCENE_MAINMENU);
	}
}
void
CGameScene::ProcessZombies(float _fDeltaTick)
{
	m_fSpawnTimeElapsed += _fDeltaTick;

	if (m_fSpawnTimeElapsed > m_fZombieSpawnRate)
	{
		SpawnZombie();
		m_fSpawnTimeElapsed = 0.0f;
	}

	float fTurretPositionX = (*m_pTurret).GetPositionX();
	float fTurretPositionY = (*m_pTurret).GetPositionY();;

	for (int i = 0; i < g_iMaxZombies; ++i)
	{
		if ((*m_pZombie[i]).IsAlive() == true)
		{
			(*m_pZombie[i]).SetTargetPosition(fTurretPositionX, fTurretPositionY);
			(*m_pZombie[i]).Process(_fDeltaTick);
		}
	}
}

void
CGameScene::ProcessGameText(float _fDeltaTick)
{
	for (int i = 0; i < g_iMaxGameText; ++i)
	{
		if ((*m_pGameText[i]).IsDisplaying() == true)
		{
			(*m_pGameText[i]).Process(_fDeltaTick);
		}
	}

}

void
CGameScene::ProcessBloodSplatter(float _fDeltaTick)
{
	for (int i = 0; i < g_iMaxBloodSplatter; ++i)
	{
		if ((*m_pBloodSplatter[i]).IsInUse() == true)
		{
			m_pBloodSplatter[i]->Process(_fDeltaTick);
		}
	}
}

void
CGameScene::ProcessTurretZombieCollision()
{
	const float fTurretPositionX = m_pTurret->GetPositionX();
	const float fTurretPositionY = m_pTurret->GetPositionY();
	const float fTurretRadius = m_pTurret->GetRadius();

	float fZombiePositionX = 0.0f;
	float fZombiePositionY = 0.0f;
	float fZombieRadius = 0.0f;
	int iZombieDamage = 0;

	bool bCollision = false;

	for (int i = 0; i < g_iMaxZombies; ++i)
	{
		if (m_pZombie[i]->IsAlive() != true)
		{
			continue;
		}

		fZombiePositionX = m_pZombie[i]->GetPositionX();
		fZombiePositionY = m_pZombie[i]->GetPositionY();
		fZombieRadius = m_pZombie[i]->GetRadius();

		bCollision = IsCollisionBetweenCircles(fTurretPositionX, fTurretPositionY, fZombiePositionX,
											   fZombiePositionY, fTurretRadius, fZombieRadius);

		if (bCollision == true)
		{
			iZombieDamage = m_pZombie[i]->GetDamage();

			m_pTurret->UpdateCurrentHealth(-iZombieDamage);

			sprintf_s(cTextBuffer, g_iTextBufferSize, "-%d", iZombieDamage);
			DisplayGameText(cTextBuffer, fTurretPositionX, fTurretPositionY, 0, 55, 200, TEXTCOLOUR_RED);

			SprayBlood(fTurretPositionX, fTurretPositionY, 100);

			m_pZombie[i]->SetAlive(false);
			-- m_iNumZombiesAlive;
		}
	}
}

void
CGameScene::ProcessBulletZombieCollision()
{
	float fBulletPositionX = 0.0f;
	float fBulletPositionY = 0.0f;
	float fBulletRadius = 0.0f;

	float fZombiePositionX = 0.0f;
	float fZombiePositionY = 0.0f;
	float fZombieRadius = 0.0f;

	bool bCollision = false;

	for (int i = 0; i < g_iMaxBullets; ++i)
	{
		CBullet& rBullet = m_pTurret->GetWeapon().GetBullet(i);

		if (rBullet.IsAlive() != true)
		{
			continue;
		}

		fBulletPositionX = rBullet.GetPositionX();
		fBulletPositionY = rBullet.GetPositionY();
		fBulletRadius = rBullet.GetRadius();

		for (int j = 0; j < g_iMaxZombies; ++j)
		{
			if (m_pZombie[j]->IsAlive() != true)
			{
				continue;
			}

			fZombiePositionX = m_pZombie[j]->GetPositionX();
			fZombiePositionY = m_pZombie[j]->GetPositionY();
			fZombieRadius = m_pZombie[j]->GetRadius();

			bCollision = IsCollisionBetweenCircles(fBulletPositionX, fBulletPositionY, fZombiePositionX,
												   fZombiePositionY, fBulletRadius, fZombieRadius);

			if (true == bCollision)
			{
				ProcessBulletZombieDamage(rBullet, (*m_pZombie[j]));

				break;
			}
		}
	}
}

void
CGameScene::ProcessBulletZombieDamage(CBullet& _rBullet, CZombie& _rZombie)
{
	int iBulletDamage = _rBullet.GetDamage();
	bool bCritical = _rBullet.IsCritical();

	float fZombiePositionX = _rZombie.GetPositionX();
	float fZombiePositionY = _rZombie.GetPositionY();

	_rZombie.UpdateCurrentHealth(-iBulletDamage);

	int iNumBloodParticles = 0;

	if (_rZombie.IsAlive() == false) //Zombie died due to damage
	{
		-- m_iNumZombiesAlive;

		if (bCritical == true) //The bullet did critical damage
		{
			sprintf_s(cTextBuffer, g_iTextBufferSize, "%d! OVERKILL!", iBulletDamage);
			DisplayGameText(cTextBuffer, fZombiePositionX, fZombiePositionY, 0, 55, 200, TEXTCOLOUR_LRED);

			sprintf_s(cTextBuffer, g_iTextBufferSize, "+1 GRENADE", iBulletDamage);
			DisplayGameText(cTextBuffer, m_pTurret->GetPositionX(), m_pTurret->GetPositionY(), 0, 55, 200, TEXTCOLOUR_LBLUE);
			m_pTurret->GetWeapon().UpdateHolyGrenadeAmmo(+1);
			
			iNumBloodParticles = iBulletDamage;
		}
		else
		{
			iNumBloodParticles = iBulletDamage / 2;
		}

		UpdateTurretExpierence(_rZombie);
		UpdatePlayerPoints(_rZombie);
	}
	else
	{
		if (bCritical == true)
		{
			sprintf_s(cTextBuffer, g_iTextBufferSize, "%d!", iBulletDamage);
			DisplayGameText(cTextBuffer, fZombiePositionX, fZombiePositionY, 0, 55, 200, TEXTCOLOUR_LRED);

			iNumBloodParticles = iBulletDamage / 3;
		}
		else
		{
			iNumBloodParticles = iBulletDamage / 5;
		}
	}

	SprayBlood(fZombiePositionX, fZombiePositionY, iNumBloodParticles);

	_rBullet.Kill();
}

void
CGameScene::ProcessGrenadeZombieCollision()
{
	for (int i = 0; i < g_iMaxHolyGrenades; ++i)
	{
		CHolyGrenade& rHolyGrenade = m_pTurret->GetWeapon().GetHolyGrenade(i);

		if (rHolyGrenade.IsAlive() != true)
		{
			continue;
		}

		float fGrenadeX = rHolyGrenade.GetPositionX();
		float fGrenadeY = rHolyGrenade.GetPositionY();
		float fGrenadeRadius = rHolyGrenade.GetRadius();

		for (int i = 0; i < g_iMaxZombies; ++i)
		{
			if ((*m_pZombie[i]).IsAlive() != true)
			{
				continue;
			}

			float fZombieX = (*m_pZombie[i]).GetPositionX();
			float fZombieY = (*m_pZombie[i]).GetPositionY();
			float fZombieRadius = (*m_pZombie[i]).GetRadius();

			bool bCollision = IsCollisionBetweenCircles(fGrenadeX, fGrenadeY, fZombieX, fZombieY, fGrenadeRadius, fZombieRadius);

			if (bCollision == true)
			{
				ProcessGrenadeBlastZombie(rHolyGrenade);
			}
		}
	}
}

void
CGameScene::ProcessGrenadeBlastZombie(CHolyGrenade& _rGrenade)
{
	float fGrenadePositionX = _rGrenade.GetPositionX();
	float fGrenadePositionY = _rGrenade.GetPositionY();
	float fGrenadeBlastRadius = _rGrenade.GetBlastRadius();
	int iGrenadeDamage = _rGrenade.GetDamage();
	bool bCritical = _rGrenade.IsCritical();

	float fZombiePositionX = 0.0f;
	float fZombiePositionY = 0.0f;

	float fDistance = 0.0f;

	int iNumHitZombies = 0;
	for (int i = 0; i < g_iMaxZombies; ++ i)
	{
		if (m_pZombie[i]->IsAlive() != true)
		{
			continue;
		}

		fZombiePositionX = m_pZombie[i]->GetPositionX();
		fZombiePositionY = m_pZombie[i]->GetPositionY();

		fDistance = GetDistanceBetweenTwoPoints(fGrenadePositionX, fGrenadePositionY, fZombiePositionX, fZombiePositionY);

		if (fGrenadeBlastRadius >= fDistance)
		{
			m_pZombie[i]->UpdateCurrentHealth(-iGrenadeDamage);

			if ((*m_pZombie[i]).IsAlive() != true)
			{
				-- m_iNumZombiesAlive;

				SprayBlood(fZombiePositionX, fZombiePositionY, 150);

				UpdateTurretExpierence((*m_pZombie[i]));
				UpdatePlayerPoints((*m_pZombie[i]));
			}
			else
			{
				SprayBlood(fZombiePositionX, fZombiePositionY, 75);
			}

			++ iNumHitZombies;
		}
	}

	if (bCritical == true)
	{
		sprintf_s(cTextBuffer, g_iTextBufferSize, "CRITICAL %d x %d!", iGrenadeDamage, iNumHitZombies);
	}
	else
	{
		sprintf_s(cTextBuffer, g_iTextBufferSize, "%d x %d!", iGrenadeDamage, iNumHitZombies);
	}

	DisplayGameText(cTextBuffer, fGrenadePositionX, fGrenadePositionY, 0, 55, 200, TEXTCOLOUR_LRED);

	_rGrenade.Kill();
}

void
CGameScene::DrawPlayerInfoBar()
{
	m_pPlayerInfoBar->Draw();

	m_pTxtPlayerHealth->Draw();
	m_pTxtPlayerBulletDamage->Draw();
	m_pTxtPlayerScore->Draw();
	m_pTxtPlayerCriticalRating->Draw();
	m_pTxtPlayerFireRate->Draw();
	m_pTxtPlayerNumGrenades->Draw();

	m_pBtnOpenMenu->Draw();
}

void
CGameScene::DrawPlayerInfoBarBottom()
{
	m_pPlayerInfoBarBottom->Draw();
	m_pTxtGameLevel->Draw();
	m_pTxtPlayerExperience->Draw();
	m_pTxtPlayerExperienceRequired->Draw();
	m_pTxtPlayerNumUpgradePoints->Draw();
	m_pTxtPlayerNumUpgradePointsExt->Draw();
}

void
CGameScene::DrawTurretUpgradeMenu()
{
	m_pEtyUpgradeMenu->Draw();
	m_pTxtButtetDamage->Draw();
	m_pTxtCriticleRating->Draw();
	m_pTxtFiringRate->Draw();
	m_pTxtHealth->Draw();
	m_pTxtNumUpgradePointsLeft->Draw();
	m_pBtnButtetDamage->Draw();
	m_pBtnCriticleRating->Draw();
	m_pBtnFiringRate->Draw();
	m_pBtnHealth->Draw();
	m_mBtnCloseUpgradeMenu->Draw();
}

void
CGameScene::DrawGameMenu()
{
	m_pBtnContinue->Draw();
	m_pBtnMainMenu->Draw();
}

void
CGameScene::DrawZombies()
{
	for (int i = 0; i < g_iMaxZombies; ++i)
	{
		if (m_pZombie[i]->IsAlive() == true)
		{
			m_pZombie[i]->Draw();
		}
	}
}

void
CGameScene::DrawGameText()
{
	for (int i = 0; i < g_iMaxGameText; ++i)
	{
		if ((*m_pGameText[i]).IsDisplaying() == true)
		{
			(*m_pGameText[i]).Draw();
		}
	}
}

void
CGameScene::DrawBloodSplatter()
{
	for (int i = 0; i < g_iMaxBloodSplatter; ++i)
	{
		if ((*m_pBloodSplatter[i]).IsInUse() == true)
		{
			(*m_pBloodSplatter[i]).Draw();
		}
	}
}

void
CGameScene::SpawnZombie()
{
	if (m_iNumZombiesAlive >= g_iMaxZombies - 1)
	{
		return ;
	}

	int iRandZombieIndex = 0;
	do
	{
		iRandZombieIndex = GenerateRandomNumber(0, (g_iMaxZombies - 1));
	}
	while ((*m_pZombie[iRandZombieIndex]).IsAlive() == true);

	CZombie& rZombie = (*m_pZombie[iRandZombieIndex]);

	EZombieType eZombieType = rZombie.GetType();

	if (eZombieType == ZOMBIE_GREEN)
	{
		rZombie.SetMaxHealth(20 * m_iGameLevel);
	}
	else if (eZombieType == ZOMBIE_ORANGE)
	{
		rZombie.SetMaxHealth(45 * m_iGameLevel);
	}
	else if (eZombieType == ZOMBIE_RED)
	{
		rZombie.SetMaxHealth(85 * m_iGameLevel);
	}

	int iRandomSide = GenerateRandomNumber(0, 5);
	int iPositionX = 0;
	int iPositionY = 0;
	
	if (iRandomSide == 0) //North
	{
		iPositionX = GenerateRandomNumber(0, m_rectBounds.right);
		iPositionY = -50;
	}
	else if (iRandomSide == 1) //East
	{
		iPositionX = m_rectBounds.right + 50;
		iPositionY = GenerateRandomNumber(0, m_rectBounds.bottom);
	}
	else if (iRandomSide == 2) //South
	{
		iPositionX = GenerateRandomNumber(0, m_rectBounds.right);
		iPositionY = m_rectBounds.bottom + 50;
	}
	else //West
	{
		iPositionX = m_rectBounds.left - 50;
		iPositionY = GenerateRandomNumber(0, m_rectBounds.bottom);
	}

	rZombie.ReplenishCurrentHealth();
	rZombie.SetPosition(iPositionX, iPositionY),
	rZombie.SetAlive(true);

	++ m_iNumZombiesAlive;
}

void
CGameScene::UpdateTurretExpierence(CZombie& _rZombie)
{
	EZombieType eZombieType = _rZombie.GetType();

	if (eZombieType == ZOMBIE_GREEN)
	{
		m_pTurret->UpdateCurrentXp(2);
	}
	else if (eZombieType == ZOMBIE_ORANGE)
	{
		m_pTurret->UpdateCurrentXp(5);
	}
	else if (eZombieType == ZOMBIE_RED)
	{
		m_pTurret->UpdateCurrentXp(11);
	}
}

void
CGameScene::UpdatePlayerPoints(CZombie& _rZombie)
{
	EZombieType eZombieType = _rZombie.GetType();

	if (eZombieType == ZOMBIE_GREEN)
	{
		m_iPlayerScore += 5;
	}
	else if (eZombieType == ZOMBIE_ORANGE)
	{
		m_iPlayerScore += 20;
	}
	else if (eZombieType == ZOMBIE_RED)
	{
		m_iPlayerScore += 40;
	}
}

void
CGameScene::SprayBlood(float _fPositionX, float _fPositionY, int _iNumParticles)
{
	for (int i = 0; i < g_iMaxBloodSplatter; ++i)
	{
		if (m_pBloodSplatter[i]->IsInUse() == false)
		{
			m_pBloodSplatter[i]->SetPosition(_fPositionX, _fPositionY);
			m_pBloodSplatter[i]->SetNumParticlesToUse(_iNumParticles);
			m_pBloodSplatter[i]->ReleaseParticles();

			break;
		}
	}
}

void 
CGameScene::DisplayGameText(const char* _kcText, float _fPositionX, float _fPositionY, int _iVelocityX,
						   int _iVelocityY, int _fFrameLifeSpan, ETextColour _eColor)
{
	for (int i = 0; i < g_iMaxGameText; ++i)
	{
		if ((*m_pGameText[i]).IsDisplaying() == false)
		{
			CText& rText = (*m_pGameText[i]);

			rText.SetText(_kcText);
			rText.SetTextColour(_eColor);
			rText.SetPositionX(_fPositionX);
			rText.SetPositionY(_fPositionY);
			rText.SetVelocityX(_iVelocityX);
			rText.SetVelocityY(_iVelocityY);
			rText.SetFrameLifeSpan(_fFrameLifeSpan);

			rText.SetDisplay(true);
			break;
		}
	}
}


void
CGameScene::HandleMessage(EMESSAGECODE _eMessageCode, WPARAM _wParam, LPARAM _lParam)
{
	switch (_eMessageCode)
	{
		case MSG_KEY_R_DWN:
		{
			if ((*m_pTurret).GetNumUpgradePoints() > 0)
			{
				m_bTurretUpgradeMenuOpen = true;
			}
			break;
		}

		case MSG_KEY_ESC_DWN:
			CDebugDialog::GetInstance().SetValues();
			CDebugDialog::GetInstance().Display();
			break;

		default:
			break;
	}
}