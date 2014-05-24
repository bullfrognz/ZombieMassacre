//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Projectile.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
//Framework
#include "Application.h"
#include "Window.h"
//Core
//Game

// This Include
#include "Projectile.h"

// Static Variables
int  CProjectile::m_iRefCount = 0;
RECT CProjectile::m_rectWindowBounds;

// Static Function Prototypes

// Implementation

CProjectile::CProjectile()
: m_fMovementVelocity(0.0f)
, m_fNormalizedX(0.0f)
, m_fNormalizedY(0.0f)
, m_iDamage(0)
, m_bCritical(true)
, m_bAlive(false)
{
	if (m_iRefCount == 0)
	{
		m_rectWindowBounds.top = 0;
		m_rectWindowBounds.bottom = CApplication::GetInstance().GetGameWindow().GetHeight();
		m_rectWindowBounds.left = 0;
		m_rectWindowBounds.right = CApplication::GetInstance().GetGameWindow().GetWidth();
	}

	++ m_iRefCount;
}

CProjectile::~CProjectile()
{
	-- m_iRefCount;
}

bool
CProjectile::Initialise()
{
	return (true);
}

void
CProjectile::Process(float _fDeltaTick, float _fPositionX, float _fPositionY)
{
	if (m_rectWindowBounds.top    > static_cast<int>(_fPositionY) ||
		m_rectWindowBounds.bottom < static_cast<int>(_fPositionY) ||
		m_rectWindowBounds.left   > static_cast<int>(_fPositionX) ||
		m_rectWindowBounds.right  < static_cast<int>(_fPositionX))
	{
		m_bAlive = false;
		return ;
	}

	//Empty
}

void
CProjectile::Draw()
{
	//Empty
}

void
CProjectile::Kill()
{
	SetAlive(false);
}

void
CProjectile::ResetVariables()
{
	//Emtpy
}