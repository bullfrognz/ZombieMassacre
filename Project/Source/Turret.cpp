//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Turret.cpp
//  Description :   xxx
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"

// Framework
#include "Application.h"
#include "MessageManager.h"
#include "LogManager.h"
#include "Window.h"
#include "Vector.h"
#include "Utilities.h"
#include "IniParser.h"

// Core
#include "RotationSprite.h"

// Game
#include "Weapon.h"

// This Include
#include "Turret.h"

// Static Variables

// Static Function Prototypes

// Implementation

CTurret::CTurret()
: m_pWeapon(0)
, m_iCurrentXp(0)
, m_iXpRequired(0)
, m_iXpRequiredIncrement(0)
, m_iNumUpgradePoints(0)
, m_fFireRate(0.0f)
, m_fFiringTimer(0.0f)
, m_fFireRateIncrement(0.0f)
, m_iMaxHealthIncrement(0)
, m_bLeveledUp(false)
, m_bMoveNorth(false)
, m_bMoveEast(false)
, m_bMoveSouth(false)
, m_bMoveWest(false)
, m_bFireButtonDown(false)
, m_bThrowGreade(false)
{
	ZeroMemory(&m_rectPlayBounds, sizeof(RECT));
	ZeroMemory(&m_crdMousePosition, sizeof(COORD));
}

CTurret::~CTurret()
{
	Deinitialise();
}

bool 
CTurret::Initialise()
{
	CRotationEntity::Initialise(IDB_CHARACTER_TURRET, IDB_CHARACTER_TURRETMASK, 48, 90, 4);

	CCharacter::Initialise();
	InitialiseVariables();
	InitialiseMessageTarget();
	InitialiseWeapon();
	
	return true;
}

bool
CTurret::Deinitialise()
{
	DeinitialiseMessageTarget();
	DeinitialiseWeapon();

	return (true);
}

void
CTurret::Process(float _fDeltaTick)
{
	ProcessExperience();
	ProcessRotation();
	ProcessMove(_fDeltaTick);
	ProcessThrowGrenade();
	ProcessFireWeapon(_fDeltaTick);
	m_pWeapon->Process(_fDeltaTick);
	ProcesUpgradeed();

	CCharacter::Process(_fDeltaTick);
}

void
CTurret::Draw()
{
	m_pWeapon->Draw();
	CCharacter::Draw();
}

bool
CTurret::InitialiseVariables()
{
	float fRadius = 32.0f;
	float fFireRate = 0.45f;
	float fFireRateIncrement = -0.01f;
	float fMovementVelocityX = 200.0f;
	float fMovementVelocityY = 200.0f;
	int iXpIncrement = 5;
	int iNumUpgradePoints = 0;
	int iMaxHealth = 100;

	char cTurretInitialise[] = "TurretInitialise";

	CIniParser& rIniParser = CApplication::GetInstance().GetIniParser();

	rIniParser.GetValue(cTurretInitialise, "Radius", fRadius);
	rIniParser.GetValue(cTurretInitialise, "FireRate", fFireRate);
	rIniParser.GetValue("TurretUpgrade", "FireRate", fFireRateIncrement);
	rIniParser.GetValue(cTurretInitialise, "MoveVelocityX", fMovementVelocityX);
	rIniParser.GetValue(cTurretInitialise, "MoveVelocityY", fMovementVelocityY);
	rIniParser.GetValue(cTurretInitialise, "XpIncrement", iXpIncrement);
	rIniParser.GetValue(cTurretInitialise, "UpgradePoints", iNumUpgradePoints);
	rIniParser.GetValue(cTurretInitialise, "MaxHealth", iMaxHealth);

	CRotationEntity::SetRadius(fRadius);

	m_fFireRate = fFireRate;
	m_fFireRateIncrement = fFireRateIncrement;
	CCharacter::m_fMovementVelocityX = fMovementVelocityX;
	CCharacter::m_fMovementVelocityY = fMovementVelocityY;
	m_iXpRequiredIncrement = iXpIncrement;
	m_iNumUpgradePoints = iNumUpgradePoints;
	CCharacter::m_iMaxHealth = iMaxHealth;

	CCharacter::ReplenishCurrentHealth();

	m_iCurrentXp = 0;
	m_iXpRequired = iXpIncrement;

	return (true);
}

bool
CTurret::InitialiseMessageTarget()
{
	CMessageManager& rMessageManager = CApplication::GetInstance().GetGameWindow().GetMsgManager();

	rMessageManager.AddMsgTarget(MSG_MOUSE_MOVE, this);
	rMessageManager.AddMsgTarget(MSG_MOUSE_LBUTTONUP, this);
	rMessageManager.AddMsgTarget(MSG_MOUSE_LBUTTONDWN, this);
	rMessageManager.AddMsgTarget(MSG_MOUSE_RBUTTONDWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_W_UP, this);
	rMessageManager.AddMsgTarget(MSG_KEY_W_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_S_UP, this);
	rMessageManager.AddMsgTarget(MSG_KEY_S_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_A_UP, this);
	rMessageManager.AddMsgTarget(MSG_KEY_A_DWN, this);
	rMessageManager.AddMsgTarget(MSG_KEY_D_UP, this);
	rMessageManager.AddMsgTarget(MSG_KEY_D_DWN, this);

	return (true);
}
bool
CTurret::InitialiseWeapon()
{
	m_pWeapon = new CWeapon;
	m_pWeapon->Initialise();

	assert(m_pWeapon);

	return (true);
}

bool
CTurret::DeinitialiseMessageTarget()
{
	CApplication::GetInstance().GetGameWindow().GetMsgManager().RemoveMsgTarget(this);

	return (true);
}

bool
CTurret::DeinitialiseWeapon()
{
	delete m_pWeapon;
	m_pWeapon = 0;

	return (true);
}

void
CTurret::ProcessExperience()
{
	m_bLeveledUp = false;

	if (m_iCurrentXp > m_iXpRequired)
	{
		m_iXpRequired += m_iXpRequiredIncrement;
		++ m_iNumUpgradePoints;

		m_bLeveledUp = true;
	}
}

void
CTurret::ProcessThrowGrenade()
{
	if (m_bThrowGreade == true)
	{
		m_pWeapon->ThrowGrenade(m_fPositionX, m_fPositionY, m_pVector->GetNormalisedX(), m_pVector->GetNormalisedY());

		m_bThrowGreade = false;
	}
}

void
CTurret::ProcessFireWeapon(float _fDeltaTick)
{
	m_fFiringTimer += _fDeltaTick;

	if (IsWithinBounds(m_rectPlayBounds, m_crdMousePosition.X, m_crdMousePosition.Y) == true)
	{
		if (m_bFireButtonDown == true && m_fFiringTimer > m_fFireRate)
		{
			m_pWeapon->FireBullet(m_fPositionX, m_fPositionY, m_fFacingAngle, m_pVector->GetNormalisedX(), m_pVector->GetNormalisedY());

			m_fFiringTimer = 0.0f;
		}
	}
}

void
CTurret::ProcessMove(float _fDeltaTick)
{
	CRotationEntity::SetVelocityY(0.0f);
	CRotationEntity::SetVelocityX(0.0f);

	float fVelocityX = CCharacter::m_fMovementVelocityX;
	float fVelocityY = CCharacter::m_fMovementVelocityY;

	const int iBoundsPadding = 25;

	if (m_bMoveNorth == true && m_bMoveSouth != true)
	{	
		if (CCharacter::m_fPositionY > (m_rectPlayBounds.top + iBoundsPadding))
		{
			CRotationEntity::m_fVelocityY = fVelocityY;
		}
	}
	else if (m_bMoveNorth != true && m_bMoveSouth == true)
	{
		if (CCharacter::m_fPositionY < (m_rectPlayBounds.bottom - iBoundsPadding * 3))
		{
			CRotationEntity::m_fVelocityY = fVelocityY * -1.0f;
		}
	}

	if (m_bMoveEast == true && m_bMoveWest != true)
	{
		if (CCharacter::m_fPositionX < (m_rectPlayBounds.right - iBoundsPadding))
		{
			CRotationEntity::m_fVelocityX = fVelocityX;
		}
	}
	else if (m_bMoveEast != true && m_bMoveWest == true)
	{
		if (CCharacter::m_fPositionX > (m_rectPlayBounds.left + iBoundsPadding))
		{
			CRotationEntity::m_fVelocityX = fVelocityX * -1.0f;
		}
	}
}

void
CTurret::ProcessRotation()
{
	float fTurretX = CRotationEntity::GetPositionX();
	float fTurretY = CRotationEntity::GetPositionY();

	float fMouseX = static_cast<float>(m_crdMousePosition.X);
	float fMouseY = static_cast<float>(m_crdMousePosition.Y);

	m_pVector->SetPositions(fTurretX, fTurretY, fMouseX, fMouseY);

	CRotationEntity::m_fFacingAngle = m_pVector->GetDirectionAngle();
}

void
CTurret::ProcesUpgradeed()
{
	if (CCharacter::m_iCurrentHealth <= 0)
	{
		CCharacter::m_bAlive = false;
	}
}

void
CTurret::HandleMessage(EMESSAGECODE _eMessageCode, WPARAM _wParam, LPARAM _lParam)
{
	switch (_eMessageCode)
	{		
		case MSG_MOUSE_MOVE:
		{
			m_crdMousePosition.X = static_cast<int>(LOWORD(_lParam));
			m_crdMousePosition.Y = static_cast<int>(HIWORD(_lParam));
			break;
		}

		case MSG_MOUSE_LBUTTONDWN:
		{
			m_bFireButtonDown = true;
			break;
		}

		case MSG_MOUSE_LBUTTONUP:
		{
			m_bFireButtonDown = false;
			break;
		}

		case MSG_MOUSE_RBUTTONDWN:
		{
			m_bThrowGreade = true;
			break;
		}

		case MSG_KEY_W_UP:
		{
			m_bMoveNorth = false;
			break;
		}

		case MSG_KEY_W_DWN:
		{
			m_bMoveNorth = true;
			break;
		}

		case MSG_KEY_S_UP:
		{
			m_bMoveSouth = false;
			break;
		}

		case MSG_KEY_S_DWN:
		{
			m_bMoveSouth = true;
			break;
		}

		case MSG_KEY_A_UP:
		{
			m_bMoveWest = false;
			break;
		}

		case MSG_KEY_A_DWN:
		{
			m_bMoveWest = true;
			break;
		}

		case MSG_KEY_D_UP:
		{
			m_bMoveEast = false;
			break;
		}

		case MSG_KEY_D_DWN:
		{
			m_bMoveEast = true;
			break;
		}

		default:
		{
			assert(false); //Recieved unknown message.
			break;
		}
	}
}
