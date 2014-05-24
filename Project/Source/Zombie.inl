//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Zombie.inl
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
CZombie::SetDamage(int _iDamage)
{
	m_iDamage = _iDamage;
}

void
CZombie::SetTargetPosition(float _fPositionX, float _fPositionY)
{
	m_fTargetPositionX = _fPositionX;
	m_fTargetPositionY = _fPositionY;
}

int
CZombie::GetDamage() const
{
	return (m_iDamage);
}

float
CZombie::GetTargetPositionX() const
{
	return (m_fTargetPositionX);
}

float
CZombie::GetTargetPositionY() const
{
	return (m_fTargetPositionY);
}

EZombieType
CZombie::GetType() const
{
	return (m_eType);
}