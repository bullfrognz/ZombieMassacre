//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   AnimatedEntity.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_ANIMATEDENTITY_H__
#define __IGFEB11_IG120_ANIMATEDENTITY_H__

// Library Includes

// Local Includes
#include "Entity.h"

// Types

// Constants

// Prototypes
class CAnimatedSprite;

class CAnimatedEntity : public CEntity
{
    // Member Functions
public:
	         CAnimatedEntity();
	virtual ~CAnimatedEntity();

	virtual bool Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId, int _iFrameWidth);
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	// Member Inline Functions
	inline CAnimatedSprite& GetAnimatedSprite();

protected:

private:

    // Member Variables
public:

protected:
	CAnimatedSprite* m_pAnimatedSprite;

private:

};

#include "AnimatedEntity.inl"

#endif // __IGFEB11_IG120_ANIMATEDENTITY_H__
