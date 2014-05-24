//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Zombie.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
	#include "resource.h"
	//Framework
	#include "Application.h"
	#include "Window.h"
	#include "Utilities.h"
	#include "Vector.h"
	//Core
	#include "RotationSprite.h"
	//Game

// This Include
#include "Zombie.h"

// Static Variables

// Static Function Prototypes
int CZombie::s_iRefCount = 0;

// Implementation

CZombie::CZombie()
: m_fTargetPositionX(0.0f)
, m_fTargetPositionY(0.0f)
, m_iDamage(0)
{
	++ s_iRefCount;
}

CZombie::~CZombie()
{
	-- s_iRefCount;
}

int g_iStartPosY = 0;

bool
CZombie::Initialise(EZombieType _eZombieType)
{
	switch (_eZombieType)
	{
	case ZOMBIE_GREEN:
		CRotationEntity::Initialise(IDB_ZOMBIE_GREEN, IDB_ZOMBIE_MASK, 64, 74, 5);
		CCharacter::SetMovementVelocity(70, 70);
		m_iDamage = 5;
		break;

	case ZOMBIE_ORANGE:
		CRotationEntity::Initialise(IDB_ZOMBIE_ORANGE, IDB_ZOMBIE_MASK, 64, 74, 5);
		CCharacter::SetMovementVelocity(45, 45);
		m_iDamage = 15;
		break;

	case ZOMBIE_RED:
		CRotationEntity::Initialise(IDB_ZOMBIE_RED, IDB_ZOMBIE_MASK, 64, 74, 5);
		CCharacter::SetMovementVelocity(30, 30);
		m_iDamage = 20;
		break;

	default:
		assert(false); //Invalid zombie.
	}

	m_eType = _eZombieType;

	CRotationEntity::SetRadius(38);
	CCharacter::Initialise();
	CCharacter::SetMaxHealth(100);
	CCharacter::ReplenishCurrentHealth();

	return (true);
}

void
CZombie::Process(float _fDeltaTick)
{
	ProcessRotation();
	ProcessMove(_fDeltaTick);
	ProcesUpgradeed();

	CCharacter::Process(_fDeltaTick);
}

void
CZombie::Draw()
{
	CCharacter::Draw();
}

void
CZombie::ProcessMove(float _fDeltaTick)
{
	float fVelocityX = CCharacter::m_fMovementVelocityX;
	float fVelocityY = CCharacter::m_fMovementVelocityY;

	CRotationEntity::m_fVelocityX = m_pVector->GetNormalisedX() * fVelocityX;
	CRotationEntity::m_fVelocityY = m_pVector->GetNormalisedY() * fVelocityY;
}

void
CZombie::ProcessRotation()
{
	float fZombieX = CRotationEntity::GetPositionX();
	float fZombieY = CRotationEntity::GetPositionY();

	m_pVector->SetPositions(fZombieX, fZombieY, m_fTargetPositionX, m_fTargetPositionY);

	CRotationEntity::m_fFacingAngle = m_pVector->GetDirectionAngle();
}

void
CZombie::ProcesUpgradeed()
{
	if (CCharacter::m_iCurrentHealth <= 0)
	{
		CCharacter::m_bAlive = false;
	}
}