//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   AnimatedSprite.inl
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>

// Local Includes

// This Include

// Static Variables

// Static Function Prototypes

// Implementation

void
CAnimatedSprite::SetFrameSpeed(float _fSpeed)
{
	assert(_fSpeed > 0.0f); //Invalid value

	m_fFrameSpeed = _fSpeed;
}

float
CAnimatedSprite::GetFrameSpeed() const
{
	return (m_fFrameSpeed);
}