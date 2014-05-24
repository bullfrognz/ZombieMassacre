//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Character.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
	//Framework
	#include "Vector.h"
	//Core
	#include "RotationSprite.h"
	//Game

// This Include
#include "Character.h"

// Static Variables

// Static Function Prototypes

// Implementation
CCharacter::CCharacter()
: m_pVector(0)
, m_iMaxHealth(0)
, m_iCurrentHealth(0)
, m_fMovementVelocityX(0)
, m_fMovementVelocityY(0)
, m_bAlive(false)
{
	//Emtpy
}

CCharacter::~CCharacter()
{
	delete m_pVector;
	m_pVector = 0;
}

bool
CCharacter::Initialise()
{
	m_pVector = new CVector;
	m_bAlive = false;

	return (true);
}

void
CCharacter::Process(float _fDeltaTick)
{
	CRotationEntity::Process(_fDeltaTick);
}

void
CCharacter::Draw()
{	
	CRotationEntity::Draw();
}