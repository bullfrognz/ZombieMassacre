//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Animation.inl
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
CAnimation::SetStartPositionX(int _iX)
{
	assert(_iX >= 0); //Invalid value

	m_iStartX = _iX;
}

void
CAnimation::SetStartPositionY(int _iY)
{
	assert(_iY >= 0); //Invalid value

	m_iStartY = _iY;
}

void
CAnimation::SetNumFrames(int _iCount)
{
	assert(_iCount >= 1); //Invalid value

	m_iNumFrames = _iCount;
} 

void
CAnimation::SetFrameWidth(int _iWidth)
{
	assert(_iWidth >= 0); //Invalid value

	m_iFrameWidth = _iWidth;
}

void
CAnimation::SetFrameHeight(int _iHeight)
{
	assert(_iHeight >= 0); //Invalid value

	m_iFrameHeight = _iHeight;
}

void
CAnimation::SetFrameSpeed(float _fSpeed)
{
	assert(_fSpeed > 0.0f);

	m_fFrameSpeed = _fSpeed;
}

int
CAnimation::GetName() const
{
	return (m_iName);
}

int
CAnimation::GetStartPositionX() const
{
	return (m_iStartX);
}

int
CAnimation::GetStartPositionY() const
{
	return (m_iStartY);
}

int
CAnimation::GetNumFrames() const
{
	return (m_iNumFrames);
}

int
CAnimation::GetFrameWidth() const
{
	return (m_iFrameWidth);
}

int
CAnimation::GetFrameHeight() const
{
	return (m_iFrameHeight);
}

float
CAnimation::GetFrameSpeed() const
{
	return (m_fFrameSpeed);
}