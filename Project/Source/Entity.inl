//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Entity.inl
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
CEntity::SetPositionX(float _fPositionX)
{
	m_fPositionX = _fPositionX;
}

void
CEntity::SetPositionY(float _fPositionY)
{
	m_fPositionY = _fPositionY;
}

void
CEntity::SetPosition(float _fPositionX, float _fPositionY)
{
	SetPositionX(_fPositionX);
	SetPositionY(_fPositionY);
}

void
CEntity::SetPositionX(int _iPositionX)
{
	SetPositionX(static_cast<float>(_iPositionX));
}

void
CEntity::SetPositionY(int _iPositionY)
{
	SetPositionY(static_cast<float>(_iPositionY));
}

void
CEntity::SetPosition(int _iPositionX, int _iPositionY)
{
	SetPositionX(static_cast<float>(_iPositionX));
	SetPositionY(static_cast<float>(_iPositionY));
}

void
CEntity::SetVelocityX(float _fVelocityX)
{
	m_fVelocityX = _fVelocityX;
}

void
CEntity::SetVelocityY(float _fVelocityY)
{
	m_fVelocityY = _fVelocityY;
}

void
CEntity::SetVelocity(float _fVelocityX, float _fVelocityY)
{
	SetVelocityX(_fVelocityX);
	SetVelocityY(_fVelocityY);
}

void
CEntity::SetVelocityX(int _iVelocityX)
{
	SetVelocityX(static_cast<float>(_iVelocityX));
}

void
CEntity::SetVelocityY(int _iVelocityY)
{
	SetVelocityY(static_cast<float>(_iVelocityY));
}

void
CEntity::SetVelocity(int _iVelocityX, int _iVelocityY)
{
	SetVelocityX(static_cast<float>(_iVelocityX));
	SetVelocityY(static_cast<float>(_iVelocityY));
}

void
CEntity::SetRadius(float _fRadius)
{
	assert(_fRadius >= 0.0f);//Radius value is not valid

	m_fRadius = _fRadius;
}

void
CEntity::TranslatePositionX(float _fX)
{
	SetPositionX(m_fPositionX + _fX);
}

void
CEntity::TranslatePositionY(float _fY)
{
	SetPositionY(m_fPositionY + _fY);
}

void
CEntity::TranslatePosition(float _fX, float _fY)
{
	SetPosition(m_fPositionX + _fX, m_fPositionY + _fY);
}

void
CEntity::TranslatePositionX(int _iX)
{
	SetPositionX(m_fPositionX + static_cast<float>(_iX));
}

void
CEntity::TranslatePositionY(int _iY)
{
	SetPositionY(m_fPositionY + static_cast<float>(_iY));
}

void
CEntity::TranslatePosition(int _iX, int _iY)
{
	SetPositionX(m_fPositionX + static_cast<float>(_iX));
	SetPositionY(m_fPositionY + static_cast<float>(_iY));
}

float
CEntity::GetPositionX() const
{
	return (m_fPositionX);
}

float
CEntity::GetPositionY() const
{
	return (m_fPositionY);
}

float
CEntity::GetVelocityX() const
{
	return (m_fVelocityX);
}

float
CEntity::GetVelocityY() const
{
	return (m_fVelocityY);
}

float
CEntity::GetRadius()
{
	return (m_fRadius);
}