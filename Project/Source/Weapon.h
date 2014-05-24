//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Weapon.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_WEAPON_H__
#define __IGFEB11_IG120_WEAPON_H__

// Library Includes

// Local Includes

// Types

// Constants
const unsigned g_iMaxBullets = 950;
const unsigned g_iMaxHolyGrenades = 25;

// Prototypes
class CBullet;
class CHolyGrenade;
class CZombie;

class CWeapon
{
    // Member Functions
public:
	 CWeapon();
	~CWeapon();

	bool Initialise();
	bool Deinitialise();
	void Process(float _fDeltaTick);
	void Draw();

	bool InitialiseVariables();
	bool InitialiseBullets();
	bool InitialiseHolyGrenades();

	bool DeinitialiseBullets();
	bool DeinitialiseHolyGrenades();

	void ProcessBullets(float _fDeltaTick);
	void ProcessHolyGrenades(float _fDeltaTick);

	void DrawBullets();
	void DrawHolyGrenades();

	void FireBullet(float _fPositionX, float _fPositionY, float _fFacingAngle, float _fNormalisedX, float _fNormalisedY);
	bool ThrowGrenade(float _fPositionX, float _fPositionY, float _fNormalisedX, float _fNormalisedY);

	// Member Inline Functions
	inline void UpgradeBulletdamage();
	inline void UpgradeCriticalRating();

	inline void SetBulletDamageMin(int _iDamage);
	inline void SetBulletDamageMax(int _iDamage);
	inline void UpdateBulletDamage(int _iDamage);
	inline void SetHolyGrenadeAmmo(int _iAmmo);
	inline void UpdateHolyGrenadeAmmo(int _iAmount);
	inline void SetCriticalRating(int _iCriticalRating);
	inline void UpdateCriticalRating(int _iCriticalRating);

	inline int GetBulletDamageMin() const;
	inline int GetBulletDamageMax() const;
	inline int GetBulletDamageIncrement() const;
	inline int GetHolyGrenadeAmmo() const;
	inline int GetCriticalRating() const;
	inline int GetCriticalRatingIncrement() const;

	inline CBullet& GetBullet(int _iIndex) const;
	inline CHolyGrenade& GetHolyGrenade(int _iIndex)  const;

protected:

private:

    // Member Variables
public:

protected:

private:
	CBullet* m_pBullets[g_iMaxBullets];
	CHolyGrenade* m_pHolyGrenades[g_iMaxHolyGrenades];

	int m_iCriticalRating;
	int m_iCriticalRatingIncrement;

	int m_iBulletDamageMin;
	int m_iBulletDamageMax;
	int m_iBulletDamageIncrement;

	int m_iHolyGrenadeAmmo;

};

#include "Weapon.inl"

#endif // __IGFEB11_IG120_WEAPON_H__
