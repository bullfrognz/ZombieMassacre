//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   HolyGrenade.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_HOLYGRENADE_H__
#define __IGFEB11_IG120_HOLYGRENADE_H__

// Library Includes
#include <windows.h>

// Local Includes
	//Framework
	//Core
	#include "Projectile.h"
	#include "AnimatedEntity.h"
	//Game


// Types

// Constants

// Prototypes

class CHolyGrenade : public CProjectile, public CAnimatedEntity
{
    // Member Functions
public:
	 CHolyGrenade();
	~CHolyGrenade();

	virtual bool Initialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	virtual void Kill();

	virtual void ResetVariables();

	// Member Inline Functions

	inline float GetBlastRadius() const;

protected:

private:

    // Member Variables
public:

protected:

private:
	bool m_bDeadAnimationPlaying;

	int m_iDeadAnimationFrameWait;
	int m_iFrameCount;

	float m_fBlastRadius;

};

#include "HolyGrenade.inl"

#endif // __IGFEB11_IG120_HOLYGRENADE_H__
