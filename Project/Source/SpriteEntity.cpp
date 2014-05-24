//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   SpriteEntity.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "Sprite.h"

// This Include
#include "SpriteEntity.h"

// Static Variables

// Static Function Prototypes

// Implementation
CSpriteEntity::CSpriteEntity()
: m_pSprite(0)
{
	m_pSprite = new CSprite;
}

CSpriteEntity::~CSpriteEntity()
{
	if (m_pSprite != 0)
	{
		delete m_pSprite;
		m_pSprite = 0;
	}
}

bool
CSpriteEntity::Initialise(const int _kiSpriteId, const int _kiMaskId)
{
	m_pSprite->Initialise(_kiSpriteId, _kiMaskId);

	return (true);
}

void
CSpriteEntity::Process(float _fDeltaTick)
{
	//Empty
}

void
CSpriteEntity::Draw()
{
	m_pSprite->SetPosition(CEntity::m_fPositionX, CEntity::m_fPositionY);

	m_pSprite->Draw();
}