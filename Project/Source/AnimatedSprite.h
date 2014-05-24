//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   AnimatedSprite.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_ANIMATEDSPRITE_H__
#define __IGFEB11_IG120_ANIMATEDSPRITE_H__

// Library Includes
#include <map>
#include <vector>

// Local Includes
#include "Sprite.h"

// Types

// Constants

// Prototypes
class CAnimation;

class CAnimatedSprite : public CSprite
{
    // Member Functions
public:
	         CAnimatedSprite();
	virtual ~CAnimatedSprite();

	virtual bool Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId, int _iFrameWidth);
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	void AddAnimation(CAnimation& _rAnimation);
	void PlayAnimation(const char* _kcpAnimationAlias);

	void ClearAnimations();

	// Member Inline Functions
	inline void SetFrameSpeed(float _fSpeed);

	inline float GetFrameSpeed() const;

protected:

private:

    // Member Variables
public:

protected:

private:
	std::map<int, CAnimation*> m_mapAnimation;

	int m_iAnimationName;
	int m_iAnimationNumFrames;

	int m_iCurrentFrame;

	float m_fFrameSpeed;
	float m_fTimeElapsed;

};

#include "AnimatedSprite.inl"

#endif // __IGFEB11_IG120_ANIMATEDSPRITE_H__
