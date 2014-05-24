//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Projectile.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_PROJECTILE_H__
#define __IGFEB11_IG120_PROJECTILE_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes

class CProjectile
{
    // Member Functions
public:
	 CProjectile();
	~CProjectile();

	bool Initialise();
	void Process(float _fDeltaTick, float _fPositionX, float _fPositionY);
	void Draw();

	virtual void Kill();

	virtual void ResetVariables();

	// Member Inline Functions
	inline void SetDamage(int _iDamage);
	inline void SetNormalizedX(float _fNormalizedX);
	inline void SetNormalizedY(float _fNormalizedY);
	inline void SetMovementVelocity(float _fMovementVelocity);
	inline void SetCritical(bool _bCritical);
	inline void SetAlive(bool _bAlive);

	inline int GetDamage() const;
	inline float GetNormalizedX() const;
	inline float GetNormalisedY() const;
	inline float GetMovementVelocity() const;
	inline bool IsCritical() const;
	inline bool IsAlive() const;

	static bool TestHarness();


protected:

private:

    // Member Variables
public:

protected:
	float m_fMovementVelocity;

	float m_fNormalizedX;
	float m_fNormalizedY;

	int m_iDamage;

	bool m_bCritical;
	bool m_bAlive;

	static RECT m_rectWindowBounds;
	static int  m_iRefCount;

private:

};

#include "Projectile.inl"

#endif // __IGFEB11_IG120_PROJECTILE_H__
