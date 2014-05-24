//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Bullet.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
	#include "resource.h"
	//Framework
	#include "Utilities.h"
	//Core
	#include "RotationSprite.h"
	//Game

// This Include
#include "Bullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBullet::CBullet()
{
	//Empty
}

CBullet::~CBullet()
{
	//Empty
}

bool
CBullet::Initialise()
{
	CProjectile::Initialise();

	CRotationEntity::Initialise(IDB_BULLET, IDB_BULLETMASK, 48, 90, 4);
	CRotationEntity::SetRadius(12);

	CProjectile::SetMovementVelocity(1000);

	ResetVariables();
	
	return (true);
}

void
CBullet::Process(float _fDeltaTick)
{
	CRotationEntity::SetVelocityX(CProjectile::m_fNormalizedX * CProjectile::m_fMovementVelocity);
	CRotationEntity::SetVelocityY(CProjectile::m_fNormalizedY * CProjectile::m_fMovementVelocity);

	CProjectile::Process(_fDeltaTick, CEntity::GetPositionX(), CEntity::GetPositionY());
	CRotationEntity::Process(_fDeltaTick);
}

void 
CBullet::Draw()
{
	CRotationEntity::Draw();
}

void
CBullet::Kill()
{
	ResetVariables();
	CProjectile::Kill();
}

void
CBullet::ResetVariables()
{
	CProjectile::ResetVariables();
}