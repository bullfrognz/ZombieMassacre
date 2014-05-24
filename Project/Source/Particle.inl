//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Particle.inl
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>

// Local Includes
	//Framework
	#include "Utilities.h"
	//Core
	//Game

// This Include

// Static Variables

// Static Function Prototypes

// Implementation
void
CParticle::SetFrameLifeSpan(int _iNumFrames)
{
	assert(_iNumFrames >= 0); //Invalid value.

	m_iFrameLifeSpan = _iNumFrames;
}

int
CParticle::GetFrameLifeSpan() const
{
	return (m_iFrameLifeSpan);
}

void
CParticle::SetAlive(bool _bAlive)
{
	m_bAlive = _bAlive;
}

bool
CParticle::IsAlive() const
{
	return (m_bAlive);
}