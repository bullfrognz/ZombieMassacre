//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   GameScene.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_GAMESCENE_H__
#define __IGFEB11_IG120_GAMESCENE_H__

// Library Includes

// Local Includes
#include "Scene.h"
#include "MessageTarget.h"

// Types

// Constants
const int g_iMaxZombies = 50;
const int g_iMaxGameText = 200;
const int g_iMaxBloodSplatter = 20;
const int g_iTextBufferSize = 64;

// Prototypes
class CButton;
class CText;
class CTurret;
class CZombie;
class CBullet;
class CHolyGrenade;
class CBloodSplatter;
class CSpriteEntity;

enum ETextColour;

class CGameScene : public IScene, public IMessageTarget
{
    // Member Functions
public:
	 CGameScene();
	~CGameScene();

	virtual bool Initialise();
	virtual bool Deinitialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	bool InitialiseTextBuffer();
	bool IntiailiseLevel();
	bool InitialiseBounds();
	bool InitialisePlayerInfoBar();
	bool InitialisePlayerInfoBarBottom();
	bool InitialiseTurretUpgradeMenu();
	bool InitialiseGameMenu();
	bool InitialiseTurret();
	bool InitialiseZombies();
	bool IntiialiseGameText();
	bool InitialiseBloodSplatter();
	bool InitialiseTurretUpgradeMenuPreOpen();

	bool DeinitialiseTextBuffer();
	bool DeinitialisePlayerInfoBar();
	bool DeinitialisePlayerInfoBarBottom();
	bool DeinitialiseTurretUpgradeMenu();
	bool DeinitialiseGameMenu();
	bool DeinitialiseTurret();
	bool DeinitialiseZombies();
	bool DeinitialiseGameText();
	bool DeinitialiseBloodSplatter();

	void ProcessLevel(float _fDeltaTick);
	void ProcessTurret(float _fDeltaTick);
	void ProcessPlayerInfoBar(float _fDeltaTick);
	void ProcessPlayerInfoBarBottom(float _fDeltaTick);
	void ProcessTurretUpgradeMenu(float _fDeltaTick);
	void ProcessGameMenu(float _fDeltaTick);
	void ProcessZombies(float _fDeltaTick);
	void ProcessGameText(float _fDeltaTick);
	void ProcessBloodSplatter(float _fDeltaTick);
	void ProcessTurretZombieCollision();
	void ProcessBulletZombieCollision();
	void ProcessBulletZombieDamage(CBullet& _rBullet, CZombie& _rZombie);
	void ProcessGrenadeZombieCollision();
	void ProcessGrenadeBlastZombie(CHolyGrenade& _rGrenade);

	void DrawPlayerInfoBar();
	void DrawPlayerInfoBarBottom();
	void DrawTurretUpgradeMenu();
	void DrawGameMenu();
	void DrawZombies();
	void DrawGameText();
	void DrawBloodSplatter();

	void SpawnZombie();
	void UpdateTurretExpierence(CZombie& _rZombie);
	void UpdatePlayerPoints(CZombie& _rZombie);
	void SprayBlood(float _fPositionX, float _fPositionY, int _iNumParticles);
	void DisplayGameText(const char* _kcText, float _fPositionX, float _fPositionY, int _iVelocityX,
						 int _iVelocityY, int _fFrameLifeSpan, ETextColour _eColor);

	virtual void HandleMessage(EMESSAGECODE _eMessageCode, WPARAM _wParam, LPARAM _lParam);

	// Member Inline Functions
	inline void SetGameLevel(int _iLevel);
	inline void SetZombieSpawnRate(float _fRate);

	inline int GetGameLevel() const;
	inline float GetZombieSpawnRate() const;

protected:

private:

    // Member Variables
public:
	static int s_iScoreOfLastGame;

protected:

private:
	RECT m_rectBounds;

	char* cTextBuffer;

	CTurret* m_pTurret;

	CZombie* m_pZombie[g_iMaxZombies];

	CBloodSplatter* m_pBloodSplatter[g_iMaxBloodSplatter];

	CText* m_pGameText[g_iMaxGameText];

	CButton* m_pBtnContinue;
	CButton* m_pBtnMainMenu;

	CSpriteEntity* m_pPlayerInfoBar;
	CText* m_pTxtPlayerHealth;
	CText* m_pTxtPlayerScore;
	CText* m_pTxtPlayerBulletDamage;
	CText* m_pTxtPlayerCriticalRating;
	CText* m_pTxtPlayerFireRate;
	CText* m_pTxtPlayerNumGrenades;
	CButton* m_pBtnOpenMenu;

	CSpriteEntity* m_pPlayerInfoBarBottom;
	CText* m_pTxtGameLevel;
	CText* m_pTxtPlayerExperience;
	CText* m_pTxtPlayerExperienceRequired;
	CText* m_pTxtPlayerNumUpgradePoints;
	CText* m_pTxtPlayerNumUpgradePointsExt;

	CSpriteEntity* m_pEtyUpgradeMenu;
	CText* m_pTxtButtetDamage;
	CText* m_pTxtCriticleRating;
	CText* m_pTxtFiringRate;
	CText* m_pTxtHealth;
	CText* m_pTxtNumUpgradePointsLeft;
	CButton* m_pBtnButtetDamage;
	CButton* m_pBtnCriticleRating;
	CButton* m_pBtnFiringRate;
	CButton* m_pBtnHealth;
	CButton* m_mBtnCloseUpgradeMenu;

	int m_iPlayerScore;
	int m_iGameLevel;

	float m_fLevelTimeElapsed;
	float m_fNextLevelTime;

	float m_fSpawnTimeElapsed;
	float m_fZombieSpawnRate;
	
	int m_iNumZombiesAlive;

	bool m_bGameMenuOpen;
	bool m_bTurretUpgradeMenuOpen;

	bool m_bGameOver;


};

#include "GameScene.inl"

#endif // __IGFEB11_IG120_GAMESCENE_H__
