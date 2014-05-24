//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Turret.inl
//  Description :   xxx
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
CTurret::UpgradeFireRate()
{
	m_fFireRate += m_fFireRateIncrement;
}

void
CTurret::SetPlayBounds(RECT _rectBounds)
{
	m_rectPlayBounds = _rectBounds;
}

void
CTurret::SetFireRate(float _fValue)
{
	assert(m_fFireRate >= 0.0f); //Invalid value.

	m_fFireRate = _fValue;
}

void
CTurret::UpdateFireRate(float _fValue)
{
	SetFireRate(m_fFireRate + _fValue);
}

void
CTurret::SetCurrentXp(int _iXp)
{
	assert(_iXp >= 0); //Invalid value.

	m_iCurrentXp = _iXp;
}

void
CTurret::UpdateCurrentXp(int _iXp)
{
	SetCurrentXp(m_iCurrentXp + _iXp);
}

void
CTurret::SetXpRequired(int _iXp)
{
	assert(_iXp >= 0); //Invalid value.

	m_iXpRequired = _iXp;
}

void
CTurret::SetXpRequiredIncrement(int _iIncrement)
{
	assert(_iIncrement >= 1); //Invalid value.

	m_iXpRequiredIncrement = _iIncrement;
}

void
CTurret::SetNumUpgradePoints(int _iValue)
{
	assert(_iValue >= 0); //Invalid value.

	m_iNumUpgradePoints = _iValue;
}

void
CTurret::UpdateNumUpgradePoints(int _iValue)
{
	SetNumUpgradePoints(m_iNumUpgradePoints + _iValue);
}

float
CTurret::GetFireRate() const
{
	return (m_fFireRate);
}

float
CTurret::GetFireRateIncrement() const
{
	return (m_fFireRateIncrement);
}

int
CTurret::GetCurrentXp() const
{
	return (m_iCurrentXp);
}

int
CTurret::GetXpRequired() const
{
	return (m_iXpRequired);
}

int
CTurret::GetXpRequiredIncrement() const
{
	return (m_iXpRequiredIncrement);
}

int
CTurret::GetNumUpgradePoints() const
{
	return (m_iNumUpgradePoints);
}

int
CTurret::GetMaxHealthIncrement() const
{
	return (m_iMaxHealthIncrement);
}

RECT
CTurret::GetPlayBounds() const
{
	return (m_rectPlayBounds);
}

CWeapon&
CTurret::GetWeapon() const
{
	return (*m_pWeapon);
}

bool
CTurret::HasLeveledup() const
{
	return (m_bLeveledUp);
}