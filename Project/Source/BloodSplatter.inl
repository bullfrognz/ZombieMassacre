//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   BloodSplatter.inl
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
CBloodSplatter::SetPosition(float _fPsoitionX, float _fPositionY)
{
	m_fPositionX = _fPsoitionX;
	m_fPositionY = _fPositionY;
}

void
CBloodSplatter::SetNumParticlesToUse(int _iNumParticles)
{	
	assert(_iNumParticles >= 0);

	if (_iNumParticles > g_kiMaxParticles)
	{
		_iNumParticles = g_kiMaxParticles;
	}

	m_iNumParticlesToUse = _iNumParticles;
}

float
CBloodSplatter::GetPositionX() const
{
	return (m_fPositionX);
}

float
CBloodSplatter::GetPositionY() const
{
	return (m_fPositionY);
}

int
CBloodSplatter::GetNumParticlesToUse() const
{
	return (m_iNumParticlesToUse);
}

bool
CBloodSplatter::IsInUse()
{
	return (m_bInUse);
}