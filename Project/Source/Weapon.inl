//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Weapon.inl
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
CWeapon::UpgradeBulletdamage()
{
	SetBulletDamageMax(m_iBulletDamageMax + m_iBulletDamageIncrement); //Max damage has to be set first
	SetBulletDamageMin(m_iBulletDamageMin + (m_iBulletDamageIncrement / 2));
}

void
CWeapon::UpgradeCriticalRating()
{
	SetCriticalRating(m_iCriticalRating + m_iCriticalRatingIncrement);

	if (m_iCriticalRating > 100)
	{
		m_iCriticalRating = 100;
	}
}

void
CWeapon::SetBulletDamageMin(int _iDamage)
{
	assert(m_iBulletDamageMax > _iDamage); //Invalid value. Min damage can not be higher then max damage.

	m_iBulletDamageMin = _iDamage;
}

void
CWeapon::SetBulletDamageMax(int _iDamage)
{
	assert(m_iBulletDamageMin < _iDamage); //Invalid value. Min damage can not be higher then max damage.

	m_iBulletDamageMax = _iDamage;
}

void
CWeapon::UpdateBulletDamage(int _iDamage)
{
	SetBulletDamageMax(m_iBulletDamageMax + _iDamage);
	SetBulletDamageMin(m_iBulletDamageMin + _iDamage);
}	

void
CWeapon::UpdateHolyGrenadeAmmo(int _iAmount)
{
	m_iHolyGrenadeAmmo += _iAmount;

	if (m_iHolyGrenadeAmmo < 0)
	{
		m_iHolyGrenadeAmmo = 0;
	}
}

void
CWeapon::SetHolyGrenadeAmmo(int _iAmmo)
{
	assert(_iAmmo >= 0); //Invalid value.

	m_iHolyGrenadeAmmo = _iAmmo;
}

void
CWeapon::SetCriticalRating(int _iCriticalRating)
{
	assert(_iCriticalRating >= 0);//Invalid level value

	m_iCriticalRating = _iCriticalRating;
}

void
CWeapon::UpdateCriticalRating(int _iCriticalRating)
{
	m_iCriticalRating += _iCriticalRating;
}

int
CWeapon::GetBulletDamageMin() const
{
	return (m_iBulletDamageMin);
}

int
CWeapon::GetBulletDamageMax() const
{
	return (m_iBulletDamageMax);
}

int
CWeapon::GetBulletDamageIncrement() const
{
	return (m_iBulletDamageIncrement);
}

int
CWeapon::GetCriticalRating() const
{
	return (m_iCriticalRating);
}

int
CWeapon::GetCriticalRatingIncrement() const
{
	return (m_iCriticalRatingIncrement);
}

int
CWeapon::GetHolyGrenadeAmmo() const
{
	return (m_iHolyGrenadeAmmo);
}

CBullet&
CWeapon::GetBullet(int _iIndex) const
{
	return (*m_pBullets[_iIndex]);
}

CHolyGrenade&
CWeapon::GetHolyGrenade(int _iIndex) const
{
	return (*m_pHolyGrenades[_iIndex]);
}