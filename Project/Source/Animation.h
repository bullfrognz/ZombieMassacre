//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Animation.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_ANIMATION_H__
#define __IGFEB11_IG120_ANIMATION_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes


class CAnimation
{
    // Member Functions
public:
	 CAnimation(const char* _kcpName, int _iWidth, int _iHeight, int _iNumFrames, float _fSpeed);
	~CAnimation();

	void SetName(const char* _kcpName);

	// Member Inline Functions
	inline void SetStartPositionX(int _iX);
	inline void SetStartPositionY(int _iY);
	inline void SetNumFrames(int _iCount);
	inline void SetFrameWidth(int _iWidth);
	inline void SetFrameHeight(int _iHeight);
	inline void SetFrameSpeed(float _fSpeed);

	inline int GetName() const;
	inline int GetStartPositionX() const;
	inline int GetStartPositionY() const;
	inline int GetNumFrames() const;
	inline int GetFrameWidth() const;
	inline int GetFrameHeight() const;
	inline float GetFrameSpeed() const;

protected:

private:

    // Member Variables
public:

protected:

private:
	int m_iName;

	int m_iStartX;
	int m_iStartY;

	int m_iNumFrames;

	int m_iFrameWidth;
	int m_iFrameHeight;

	float m_fFrameSpeed;

};

#include "Animation.inl"

#endif // __IGFEB11_IG120_ANIMATION_H__
