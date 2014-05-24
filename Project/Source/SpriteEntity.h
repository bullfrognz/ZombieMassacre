//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   SpriteEntity.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_SPRITEENTITY_H__
#define __IGFEB11_IG120_SPRITEENTITY_H__

// Library Includes

// Local Includes
#include "Entity.h"

// Types

// Constants

// Prototypes
class CSprite;

class CSpriteEntity : public CEntity
{
    // Member Functions
public:
	         CSpriteEntity();
	virtual ~CSpriteEntity();

	virtual bool Initialise(const int _kiSpriteId, const int _kiMaskId);
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	// Member Inline Functions
	inline CSprite& GetSprite();

protected:

private:

    // Member Variables
public:

protected:
	CSprite* m_pSprite;

private:

};

#include "SpriteEntity.inl"

#endif // __IGFEB11_IG120_SPRITEENTITY_H__
