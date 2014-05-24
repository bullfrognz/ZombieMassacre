//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Zombie.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_ZOMBIE_H__
#define __IGFEB11_IG120_ZOMBIE_H__

// Library Includes

// Local Includes
#include "Character.h"

// Types
enum EZombieType
{
	ZOMBIE_INVALID,
	ZOMBIE_GREEN,
	ZOMBIE_ORANGE,
	ZOMBIE_RED,
	ZOMBIE_MAX
};

// Constants

// Prototypes
class CAnimatedSprite;

class CZombie : public CCharacter
{
    // Member Functions
public:
	 CZombie();
	~CZombie();

	virtual bool Initialise(EZombieType _eZombieType);
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	virtual void ProcessMove(float _fDeltaTick);
	virtual void ProcessRotation();

	virtual void ProcesUpgradeed();

	// Member Inline Functions
	inline void SetDamage(int _iDamage);
	inline void SetTargetPosition(float _fPositionX, float _fPositionY);

	inline int GetDamage() const;
	inline float GetTargetPositionX() const;
	inline float GetTargetPositionY() const;
	inline EZombieType GetType() const;

protected:

private:

    // Member Variables
public:

protected:

private:
	float m_fTargetPositionX;
	float m_fTargetPositionY;

	int m_iDamage;

	EZombieType m_eType;

	static int s_iRefCount;

};

#include "Zombie.inl"

#endif // __IGFEB11_IG120_ZOMBIE_H__
