//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Weapon.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
	//Framework
	#include "Application.h"
	#include "IniParser.h"
	#include "Utilities.h"
	//Core
	//Game
	#include "Bullet.h"
	#include "HolyGrenade.h"
	#include "Zombie.h"

// This Include
#include "Weapon.h"

// Static Variables

// Static Function Prototypes

// Implementation

CWeapon::CWeapon()
: m_iCriticalRating(0)
, m_iCriticalRatingIncrement(0)
, m_iBulletDamageMin(0)
, m_iBulletDamageMax(0)
, m_iBulletDamageIncrement(0)
, m_iHolyGrenadeAmmo(25)
{
	//Empty
}

CWeapon::~CWeapon()
{
	Deinitialise();
}

bool
CWeapon::Initialise()
{
	InitialiseVariables();
	InitialiseBullets();
	InitialiseHolyGrenades();

	return true;
}

bool
CWeapon::Deinitialise()
{
	DeinitialiseBullets();
	DeinitialiseHolyGrenades();

	return (true);
}

void
CWeapon::Process(float _fDeltaTick)
{
	ProcessBullets(_fDeltaTick);
	ProcessHolyGrenades(_fDeltaTick);
}

void 
CWeapon::Draw()
{
	DrawBullets();
	DrawHolyGrenades();
}

bool
CWeapon::InitialiseVariables()
{
	CIniParser& rIniParser = CApplication::GetInstance().GetIniParser();

	int iCriticalRating = 0;
	int iCriticalRatingIncrement = 2;
	int iBulletDamageMin = 2;
	int iBulletDamageMax = 5;
	int iBulletDamageIncrement = 4;

	const char cTurretInitialise[] = "TurretInitialise";
	const char cTurretUpgrade[] = "TurretUpgrade";

	rIniParser.GetValue(cTurretInitialise, "CriticalRating", iCriticalRating);
	rIniParser.GetValue(cTurretUpgrade, "CriticalRating", iCriticalRatingIncrement);
	rIniParser.GetValue(cTurretInitialise, "BulletDamageMin", iBulletDamageMin);
	rIniParser.GetValue(cTurretInitialise, "BulletDamageMax", iBulletDamageMax);
	rIniParser.GetValue(cTurretUpgrade, "BulletDamage", iBulletDamageIncrement);

	m_iCriticalRating = iCriticalRating;
	m_iCriticalRatingIncrement = iCriticalRatingIncrement;
	m_iBulletDamageMin = iBulletDamageMin;
	m_iBulletDamageMax = iBulletDamageMax;
	m_iBulletDamageIncrement = iBulletDamageIncrement;

	return (true);
}

bool
CWeapon::InitialiseBullets()
{
	for (int i = 0; i < g_iMaxBullets; ++i)
	{
		m_pBullets[i] = new CBullet();
		m_pBullets[i]->Initialise();
	}

	return (true);
}

bool
CWeapon::InitialiseHolyGrenades()
{
	for (int i = 0; i < g_iMaxHolyGrenades; ++i)
	{
		m_pHolyGrenades[i] = new CHolyGrenade();
		m_pHolyGrenades[i]->Initialise();
	}

	return (true);
}

bool
CWeapon::DeinitialiseBullets()
{
	for (int i = 0; i < g_iMaxBullets; ++i)
	{
		delete m_pBullets[i];
		m_pBullets[i] = 0;
	}

	return (true);
}

bool
CWeapon::DeinitialiseHolyGrenades()
{
	for (int i = 0; i < g_iMaxHolyGrenades; ++i)
	{
		delete m_pHolyGrenades[i];
		m_pHolyGrenades[i] = 0;
	}

	return (true);
}

void
CWeapon::ProcessBullets(float _fDeltaTick)
{
	for (int i = 0; i < g_iMaxBullets; ++i)
	{
		if (m_pBullets[i]->IsAlive() == true)
		{
			m_pBullets[i]->Process(_fDeltaTick);
		}
	}
}

void
CWeapon::ProcessHolyGrenades(float _fDeltaTick)
{
	for (int i = 0; i < g_iMaxHolyGrenades; ++i)
	{
		if (m_pHolyGrenades[i]->IsAlive() == true)
		{
			m_pHolyGrenades[i]->Process(_fDeltaTick);
		}
	}
}

void
CWeapon::DrawBullets()
{
	for (int i = 0; i < g_iMaxBullets; ++i)
	{
		if (m_pBullets[i]->IsAlive() == true)
		{
			m_pBullets[i]->Draw();
		}
	}
}

void
CWeapon::DrawHolyGrenades()
{
	for (int i = 0; i < g_iMaxHolyGrenades; ++i)
	{
		if (m_pHolyGrenades[i]->IsAlive() == true)
		{
			m_pHolyGrenades[i]->Draw();
		}
	}
}

void
CWeapon::FireBullet(float _fPositionX, float _fPositionY, float _fFacingAngle, float _fNormalisedX, float _fNormalisedY)
{
	for (int i = 0; i < g_iMaxBullets; ++i)
	{
		if (m_pBullets[i]->IsAlive() == false)
		{
			m_pBullets[i]->SetPosition(_fPositionX, _fPositionY);
			m_pBullets[i]->SetNormalizedX(_fNormalisedX);
			m_pBullets[i]->SetNormalizedY(_fNormalisedY);
			m_pBullets[i]->SetFacingAngle(_fFacingAngle);
			
			int iDamage = GenerateRandomNumber(m_iBulletDamageMin, m_iBulletDamageMax);

			if (GenerateRandomNumber(0, 100) <= m_iCriticalRating)
			{	
				iDamage *= 2;
				m_pBullets[i]->SetCritical(true);
			}
			else
			{
				m_pBullets[i]->SetCritical(false);
			}

			m_pBullets[i]->SetDamage(iDamage);
			m_pBullets[i]->SetAlive(true);

			break;
		}
	}
}

bool
CWeapon::ThrowGrenade(float _fPositionX, float _fPositionY, float _fNormalisedX, float _fNormalisedY)
{
	if (m_iHolyGrenadeAmmo <= 0)
	{
		return (false);
	}

	m_iHolyGrenadeAmmo -= 1;

	for (int i = 0; i < g_iMaxHolyGrenades; ++i)
	{
		if (m_pHolyGrenades[i]->IsAlive() == false)
		{
			m_pHolyGrenades[i]->SetPosition(_fPositionX, _fPositionY);
			m_pHolyGrenades[i]->SetNormalizedX(_fNormalisedX);
			m_pHolyGrenades[i]->SetNormalizedY(_fNormalisedY);
			
			int iDamage = GenerateRandomNumber(m_iBulletDamageMin, m_iBulletDamageMax);

			int iDamageMultiplier = GenerateRandomNumber(3, 5);

			iDamage *= iDamageMultiplier;

			if (GenerateRandomNumber(0, 100) <= m_iCriticalRating)
			{	
				iDamage *= 2;
				m_pHolyGrenades[i]->SetCritical(true);
			}
			else
			{
				m_pHolyGrenades[i]->SetCritical(false);
			}

			m_pHolyGrenades[i]->SetDamage(iDamage);
			m_pHolyGrenades[i]->SetAlive(true);

			break;
		}
	}

	return (true);
}