//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Projectile.inl
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
CProjectile::SetDamage(int _iDamage)
{
	assert(_iDamage >= 0);

	m_iDamage = _iDamage;
}

void
CProjectile::SetNormalizedX(float _fNormalizedX)
{
	m_fNormalizedX = _fNormalizedX;
}

void
CProjectile::SetNormalizedY(float _fNormalizedY)
{
	m_fNormalizedY = _fNormalizedY;
}

void
CProjectile::SetMovementVelocity(float _fMovementVelocity)
{
	assert(_fMovementVelocity >= 0);//Movement velocity value is not valid

	m_fMovementVelocity = _fMovementVelocity;
}

void
CProjectile::SetCritical(bool _bCritical)
{
	m_bCritical = _bCritical;
}

void
CProjectile::SetAlive(bool _bAlive)
{
	m_bAlive = _bAlive;
}

int
CProjectile::GetDamage() const
{
	return (m_iDamage);
}

float
CProjectile::GetNormalizedX() const
{
	return (m_fNormalizedX);
}

float
CProjectile::GetNormalisedY() const
{
	return (m_fNormalizedY);
}

float
CProjectile::GetMovementVelocity() const
{
	return (m_fMovementVelocity);
}

bool
CProjectile::IsCritical() const
{
	return (m_bCritical);
}

bool
CProjectile::IsAlive() const
{
	return (m_bAlive);
}