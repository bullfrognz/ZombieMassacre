//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Character.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_CHARACTER_H__
#define __IGFEB11_IG120_CHARACTER_H__

// Library Includes

// Local Includes
#include "RotationEntity.h"

// Types

// Constants

// Prototypes
class CVector;

class CCharacter : public CRotationEntity
{
    // Member Functions
public:
	         CCharacter();
	virtual ~CCharacter();

	virtual bool Initialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	virtual void ProcessMove(float _fDeltaTick) = 0;
	virtual void ProcessRotation() = 0;
	virtual void ProcesUpgradeed() = 0;


	// Member Inline Functions
	inline void ReplenishCurrentHealth();

	inline void SetMaxHealth(int _iValue);
	inline void UpdateMaxHealth(int _iValue);
	inline void SetCurrentHealth(int _iValue);
	inline void UpdateCurrentHealth(int _iValue);
	inline void SetMovementVelocityX(float _fValue);
	inline void SetMovementVelocityY(float _fValue);
	inline void SetMovementVelocity(float _fVelocityX, float _fVelocityY);
	inline void SetAlive(bool _bValue);

	inline int GetMaxHealth() const;
	inline int GetCurrentHealth() const;
	inline float GetMovementVelocityX() const;
	inline float GetMovementVelocityY() const;

	inline bool IsAlive() const;

protected:

private:

    // Member Variables
public:

protected:
	CVector* m_pVector;

	int m_iMaxHealth;
	int m_iCurrentHealth;

	float m_fMovementVelocityX;
	float m_fMovementVelocityY;

	bool m_bAlive;

private:

};

#include "Character.inl"

#endif // __IGFEB11_IG120_CHARACTER_H__
