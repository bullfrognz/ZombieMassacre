//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Animation.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>
#include <iostream>

// Local Includes
	//Framework
	#include "Utilities.h"
	//Core
	//Game

// This Include
#include "Animation.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAnimation::CAnimation(const char* _kcpName, int _iWidth, int _iHeight, int _iNumFrames, float _fSpeed)
: m_iName(0)
, m_iStartX(0)
, m_iStartY(0)
, m_iNumFrames(_iNumFrames)
, m_iFrameWidth(_iWidth)
, m_iFrameHeight(_iHeight)
, m_fFrameSpeed(_fSpeed)
{
	SetName(_kcpName);
	SetFrameSpeed(_fSpeed);
}

CAnimation::~CAnimation()
{
	//Empty
}

void
CAnimation::SetName(const char* _kcpName)
{
	assert(strlen(_kcpName) > 0); //Invalid string.

	m_iName = ConvertCharIntSum(_kcpName);
}