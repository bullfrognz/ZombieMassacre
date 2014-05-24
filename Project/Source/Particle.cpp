//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Particle.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>
#include <cmath>

// Local Includes
	//Framework
	#include "Application.h"
	#include "Window.h"
	#include "BackBuffer.h"
	#include "Utilities.h"
	//Core
	//Game

// This Include
#include "Particle.h"

// Static Variables

// Static Function Prototypes

// Implementation

CParticle::CParticle()
: m_iFrameLifeSpan(0)
, m_iFrameCount(0)
, m_bAlive(false)
{
	//Empty
}

CParticle::~CParticle()
{
	//Empty
}


bool
CParticle::Initialise()
{
	// Initial Values
	m_iFrameLifeSpan = 200;
	m_iFrameCount = 0;

	m_bAlive = false;
	// End

	CEntity::Initialise();

	return (true);
}

void
CParticle::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
	ProcessFrameLifeSpan();
}

void
CParticle::Draw()
{
	DrawParticle();
	CEntity::Draw();
}

void
CParticle::ProcessFrameLifeSpan()
{
	++ m_iFrameCount;

	if (m_iFrameCount > m_iFrameLifeSpan)
	{
		m_bAlive = false;
		m_iFrameCount = 0;
	}
}

void
CParticle::DrawParticle()
{
	CBackBuffer& rBackBuffer = CApplication::GetInstance().GetGameWindow().GetBackBuffer();

	HDC m_hDC = rBackBuffer.GetBFDC();

	int iPositionX = static_cast<int>(CEntity::GetPositionX());
	int iPositionY = static_cast<int>(CEntity::GetPositionY());

	SetPixel(m_hDC, iPositionX, iPositionY, RGB(255,0,0));
	SetPixel(m_hDC, iPositionX, 1 + iPositionY, RGB(255,0,0));
	SetPixel(m_hDC, iPositionX, 1 - iPositionY, RGB(255,0,0));
	SetPixel(m_hDC, 1 - iPositionX, iPositionY, RGB(255,0,0));
	SetPixel(m_hDC, 1 + iPositionX, iPositionY, RGB(255,0,0));
}