//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   BloodSplatter.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cmath>

// Local Includes
	//Framework
	#include "Application.h"
	#include "LogManager.h"
	//Core
	#include "Particle.h"
	//Game

// This Include
#include "BloodSplatter.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBloodSplatter::CBloodSplatter()
: m_fMovementVelocty(0.0f)
, m_fPositionX(0.0f)
, m_fPositionY(0.0f)
, m_iNumParticlesToUse(0)
, m_iFrameLifeSpanMin(0)
, m_iFrameLifeSpanMax(0)
, m_iVelocityMin(0)
, m_iVelocityMax(0)
, m_iFrameLifeSpan(0)
, m_iFrameCount(0)
, m_bInUse(false)
{
	//Empty
}

CBloodSplatter::~CBloodSplatter()
{
	for (int i = 0; i < g_kiMaxParticles; ++i)
	{
		delete m_pParticles[i];
		m_pParticles[i] = 0;
	}
}

bool
CBloodSplatter::Initialise()
{
	// Initial Values
	m_fMovementVelocty = 30.0f;

	m_fPositionX = 0.0f;
	m_fPositionY = 0.0f;

	m_iNumParticlesToUse = 25;

	m_iFrameLifeSpanMin = 50;
	m_iFrameLifeSpanMax = 150;

	m_iVelocityMin = 1;
	m_iVelocityMax = 50;

	m_iFrameLifeSpan = 0;
	m_iFrameCount = 0;

	m_bInUse = false;
	// End

	InitialiseParticles();

	return (true);
}

void
CBloodSplatter::Process(float _fDeltaTick)
{
	ProcessFrameLifeSpan();
	ProcessParticles(_fDeltaTick);
}

void
CBloodSplatter::Draw()
{
	DrawParticles();
}

bool
CBloodSplatter::InitialiseParticles()
{
	int iLifeSpan = 0;
	int iMaxLifeSpan = 0;
	float fVelocityX = 0.0f;
	float fVelocityY = 0.0f;

	for (int i = 0; i < g_kiMaxParticles; ++i)
	{
		iLifeSpan = GenerateRandomNumber(m_iFrameLifeSpanMin, m_iFrameLifeSpanMax);

		if (iLifeSpan > m_iFrameLifeSpan)
		{
			m_iFrameLifeSpan = iLifeSpan;
		}

		fVelocityX = static_cast<float>(GenerateRandomNumber(m_iVelocityMin, m_iVelocityMax));
		fVelocityY = static_cast<float>(GenerateRandomNumber(m_iVelocityMin, m_iVelocityMax));

		float fNormalised = sqrtf( (fVelocityX * fVelocityX) + (fVelocityY * fVelocityY) );

		fVelocityX /= fNormalised;
		fVelocityY /= fNormalised;

		float fDiff = static_cast<float>(GenerateRandomNumber(50, 2500)) / 1000.0f;

		fVelocityX *= m_fMovementVelocty * fDiff;
		fVelocityY *= m_fMovementVelocty * fDiff;

		if (GenerateRandomNumber(0,2) == 1)
		{
			fVelocityX *= -1;
		}

		if (GenerateRandomNumber(0,2) == 1)
		{
			fVelocityY *= -1;
		}

		m_pParticles[i] = new CParticle;
		(*m_pParticles[i]).Initialise();
		(*m_pParticles[i]).SetFrameLifeSpan(iLifeSpan);
		(*m_pParticles[i]).SetVelocity(fVelocityX, fVelocityY);
	}

	return (true);
}

void
CBloodSplatter::ProcessFrameLifeSpan()
{
	++ m_iFrameCount;

	if (m_iFrameCount > m_iFrameLifeSpan)
	{
		m_bInUse = false;
		m_iFrameCount = 0;
	}
}

void
CBloodSplatter::ProcessParticles(float _fDeltaTick)
{
	for (int i = 0; i < m_iNumParticlesToUse; ++i)
	{
		if (m_pParticles[i]->IsAlive() == true)
		{
			(*m_pParticles[i]).Process(_fDeltaTick);
		}
	}
}

void
CBloodSplatter::DrawParticles()
{
	for (int i = 0; i < m_iNumParticlesToUse; ++i)
	{
		if (m_pParticles[i]->IsAlive() == true)
		{
			(*m_pParticles[i]).Draw();
		}
	}
}

void
CBloodSplatter::ReleaseParticles()
{
	for (int i = 0; i < m_iNumParticlesToUse; ++i)
	{
		(*m_pParticles[i]).SetPosition(m_fPositionX, m_fPositionY);
		(*m_pParticles[i]).SetAlive(true);
	}

	m_bInUse = true;
}