//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Turret.h
//  Description :   xxx
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_TURRET_H__
#define __IGFEB11_IG120_TURRET_H__

// Library Includes

// Local Includes
#include "MessageTarget.h"
#include "Character.h"

// Types

// Constants

// Prototypes
class CWeapon;

class CTurret : public CCharacter, public IMessageTarget
{
    // Member Functions
public:
	         CTurret();
	virtual ~CTurret();

	virtual bool Initialise();
	virtual bool Deinitialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	bool InitialiseMessageTarget();
	bool InitialiseWeapon();
	bool InitialiseVariables();

	bool DeinitialiseMessageTarget();
	bool DeinitialiseWeapon();

	void ProcessExperience();
	void ProcessThrowGrenade();
	void ProcessFireWeapon(float _fDeltaTick);
	virtual void ProcessMove(float _fDeltaTick);
	virtual void ProcessRotation();
	virtual void ProcesUpgradeed();

	virtual void HandleMessage(EMESSAGECODE _eMessageCode, WPARAM _wParam, LPARAM _lParam);

	// Member Inline Functions
	inline void UpgradeFireRate();

	inline void SetPlayBounds(RECT _rectBounds);
	inline void SetFireRate(float _fValue);
	inline void UpdateFireRate(float _fValue);
	inline void SetCurrentXp(int _iXp);
	inline void UpdateCurrentXp(int _iXp);
	inline void SetXpRequired(int _iXp);
	inline void SetXpRequiredIncrement(int _iIncrement);
	inline void SetNumUpgradePoints(int _iValue);
	inline void UpdateNumUpgradePoints(int _iValue);

	inline float GetFireRate() const;
	inline float GetFireRateIncrement() const;
	inline int GetCurrentXp() const;
	inline int GetXpRequired() const;
	inline int GetXpRequiredIncrement() const;
	inline int GetNumUpgradePoints() const;
	inline int GetMaxHealthIncrement() const;

	inline RECT GetPlayBounds() const;
	inline CWeapon& GetWeapon() const;

	inline bool HasLeveledup() const;


protected:

private:

    // Member Variables
public:

protected:

private:
	RECT m_rectPlayBounds;

	CWeapon* m_pWeapon;

	int m_iCurrentXp;
	int m_iXpRequired;
	int m_iXpRequiredIncrement;

	int m_iNumUpgradePoints;

	float m_fFireRate;
	float m_fFiringTimer;
	float m_fFireRateIncrement;

	int m_iMaxHealthIncrement;

	COORD m_crdMousePosition;

	bool m_bLeveledUp;

	bool m_bMoveNorth;
	bool m_bMoveEast;
	bool m_bMoveSouth;
	bool m_bMoveWest;

	bool m_bFireButtonDown;
	bool m_bThrowGreade;

};

#include "Turret.inl"

#endif // __IGFEB11_IG120_TURRET_H__
