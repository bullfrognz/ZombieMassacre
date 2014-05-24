//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Bullet.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_BULLET_H__
#define __IGFEB11_IG120_BULLET_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "Projectile.h"
#include "RotationEntity.h"

// Types

// Constants

// Prototypes

class CBullet : public CProjectile, public CRotationEntity
{
    // Member Functions
public:
	 CBullet();
	~CBullet();

	virtual bool Initialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	virtual void Kill();

	virtual void ResetVariables();

	// Member Inline Functions

protected:

private:

    // Member Variables
public:

protected:

private:

};

#endif // __IGFEB11_IG120_BULLET_H__
