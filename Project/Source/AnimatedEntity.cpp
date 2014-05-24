//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   AnimatedEntity.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "AnimatedSprite.h"

// This Include
#include "AnimatedEntity.h"

// Static Variables

// Static Function Prototypes

// Implementation
CAnimatedEntity::CAnimatedEntity()
: m_pAnimatedSprite(0)
{
	m_pAnimatedSprite = new CAnimatedSprite;
}

CAnimatedEntity::~CAnimatedEntity()
{
	if (m_pAnimatedSprite != 0)
	{
		delete m_pAnimatedSprite;
		m_pAnimatedSprite = 0;
	}
}

bool
CAnimatedEntity::Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId, int _iFrameWidth)
{
	m_pAnimatedSprite->Initialise(_kiSpriteResourceId, _kiMaskResourceId, _iFrameWidth);

	return (true);
}

void
CAnimatedEntity::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);

	m_pAnimatedSprite->Process(_fDeltaTick);
}

void
CAnimatedEntity::Draw()
{
	CEntity::Draw();

	m_pAnimatedSprite->SetPosition(CEntity::m_fPositionX, CEntity::m_fPositionY);

	m_pAnimatedSprite->Draw();
}