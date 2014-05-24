//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   GameScene.inl
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>

// Local Includes

// This Include

// Static Variables

// Static Function Prototypes

// Implementation

void
CGameScene::SetGameLevel(int _iLevel)
{
	assert(_iLevel >= 0);

	m_iGameLevel = _iLevel;
}

void
CGameScene::SetZombieSpawnRate(float _fRate)
{
	assert(_fRate >= 0.0f);

	m_fZombieSpawnRate = _fRate;
}

int
CGameScene::GetGameLevel() const
{
	return (m_iGameLevel);
}

float
CGameScene::GetZombieSpawnRate() const
{
	return (m_fZombieSpawnRate);
}