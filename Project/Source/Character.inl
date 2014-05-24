//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   "-----"
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
CCharacter::ReplenishCurrentHealth()
{
	SetCurrentHealth(m_iMaxHealth);
}

void
CCharacter::SetMaxHealth(int _iValue)
{
	assert(_iValue > 0); //Invalid value.

	m_iMaxHealth = _iValue;
}

void
CCharacter::UpdateMaxHealth(int _iValue)
{
	SetMaxHealth(m_iMaxHealth + _iValue);
}

void
CCharacter::SetCurrentHealth(int _iValue)
{
	m_iCurrentHealth = _iValue;

	if (m_iCurrentHealth <= 0)
	{
		m_iCurrentHealth = 0;
		SetAlive(false);
	}
}

void
CCharacter::UpdateCurrentHealth(int _iValue)
{
	SetCurrentHealth(m_iCurrentHealth + _iValue);
}

void
CCharacter::SetMovementVelocityX(float _fValue)
{
	m_fMovementVelocityX += _fValue;
}

void
CCharacter::SetMovementVelocityY(float _fValue)
{
	m_fMovementVelocityY += _fValue;
}

void
CCharacter::SetMovementVelocity(float _fVelocityX, float _fVelocityY)
{
	SetMovementVelocityX(_fVelocityX);
	SetMovementVelocityY(_fVelocityY);
}

void
CCharacter::SetAlive(bool _bValue)
{
	m_bAlive = _bValue;
}

int
CCharacter::GetMaxHealth() const
{
	return (m_iMaxHealth);
}

int
CCharacter::GetCurrentHealth() const
{
	return (m_iCurrentHealth);
}

float
CCharacter::GetMovementVelocityX() const
{
	return (m_fMovementVelocityX);
}

float
CCharacter::GetMovementVelocityY() const
{
	return (m_fMovementVelocityY);
}

bool
CCharacter::IsAlive() const
{
	return (m_bAlive);
}