//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   HolyGrenade.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes=

// Local Includes
	#include "resource.h"
	//Framework
	#include "Utilities.h"
	//Core
	#include "AnimatedSprite.h"
	#include "Animation.h"
	//Game

// This Include
#include "HolyGrenade.h"

// Static Variables

// Static Function Prototypes

// Implementation

CHolyGrenade::CHolyGrenade()
: m_bDeadAnimationPlaying(false)
, m_iDeadAnimationFrameWait(0)
, m_iFrameCount(0)
, m_fBlastRadius(0)
{
	//Emtpy
}

CHolyGrenade::~CHolyGrenade()
{
	//Emtpy
}

bool
CHolyGrenade::Initialise()
{
	CProjectile::Initialise();

	CAnimatedEntity::Initialise(IDB_HOLYGRENADE, IDB_HOLYGRENADEMASK, 48);

	CAnimation* pAnimationMove = new CAnimation("Move", 48, 48, 45, 0.01f);
	CAnimatedEntity::GetAnimatedSprite().AddAnimation((*pAnimationMove));

	CAnimation* pAnimationExplode = new CAnimation("Explode", 176, 176, 4, 0.1f);
	pAnimationExplode->SetStartPositionY(48);
	CAnimatedEntity::GetAnimatedSprite().AddAnimation((*pAnimationExplode));

	ResetVariables();

	return (true);
}

void
CHolyGrenade::Process(float _fDeltaTick)
{
	if (m_bDeadAnimationPlaying == true)
	{
		++ m_iFrameCount;

		if (m_iFrameCount >= m_iDeadAnimationFrameWait)
		{
			ResetVariables();
			CProjectile::Kill();
		}
	}

	CAnimatedEntity::SetVelocityX(CProjectile::m_fNormalizedX * CProjectile::m_fMovementVelocity);
	CAnimatedEntity::SetVelocityY(CProjectile::m_fNormalizedY * CProjectile::m_fMovementVelocity);

	CProjectile::Process(_fDeltaTick, CEntity::GetPositionX(), CEntity::GetPositionY());
	CAnimatedEntity::Process(_fDeltaTick);
}

void 
CHolyGrenade::Draw()
{
	CProjectile::Draw();
	CAnimatedEntity::Draw();
}

void
CHolyGrenade::Kill()
{
	CAnimatedEntity::SetRadius(0.0f);
	CAnimatedEntity::GetAnimatedSprite().PlayAnimation("Explode");
	m_bDeadAnimationPlaying = true;

	CProjectile::m_fMovementVelocity = 0;
}

void
CHolyGrenade::ResetVariables()
{
	CAnimatedEntity::SetRadius(30.0f);
	CAnimatedEntity::GetAnimatedSprite().PlayAnimation("Move");

	m_bDeadAnimationPlaying = false;
	m_iFrameCount = 0;
	m_iDeadAnimationFrameWait = 100;

	CProjectile::SetMovementVelocity(250);

	m_fBlastRadius = 100;

	CProjectile::ResetVariables();
}