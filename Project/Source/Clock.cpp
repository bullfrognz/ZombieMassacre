//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Clock.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <iostream>

// Local Includes
#include "Text.h"
#include "Application.h"
#include "Window.h"

// This Include
#include "clock.h"

// Static Variables

// Static Function Prototypes

// Implementation

CClock::CClock()
: m_fTimeElapsed(0)
, m_fDeltaTime(0)
, m_fCurrentTime(0)
, m_fLastTime(0)
, m_iFrameCount(0)
, m_cFpsMessage(0)
{
	// Default Constructor.
}

CClock::CClock(const CClock& _kr)
: m_iFrameCount(0)
{
	//Emtpy
}

CClock::~CClock()
{
	delete m_pFpsText;
	m_pFpsText = 0;

	delete m_cFpsMessage;
	m_cFpsMessage = 0;
}

bool 
CClock::Initialise()
{
	int iWidth  = CApplication::GetInstance().GetGameWindow().GetWidth();
	int iHeight = CApplication::GetInstance().GetGameWindow().GetHeight();

	m_pFpsText = new CText;
	m_pFpsText->Initialise();
	m_pFpsText->SetText("Setup");
	m_pFpsText->SetDisplay(true);
	m_pFpsText->SetPosition(iWidth - 80.0f, iHeight - 80.0f);

	m_cFpsMessage = new char[32];

	return(true);
}

bool 
CClock::Deinitialise()
{
	return (true);
}

void 
CClock::Process()
{

	m_fLastTime = m_fCurrentTime;
		
	m_fCurrentTime = static_cast<float>(timeGetTime());
	if(m_fLastTime == 0.0f)
	{
		m_fLastTime = m_fCurrentTime;
	}
	m_fDeltaTime = (m_fCurrentTime - m_fLastTime) / 1000;

	m_fTimeElapsed += m_fDeltaTime;

	ProcessFPS();
}

void
CClock::Draw()
{
	m_pFpsText->Draw();
}

void
CClock::ProcessFPS()
{
	float fMaxFrames = 120.0f;
	float fLockedDeltaTime = 1000.0f / fMaxFrames;

	float fCurrentDeltaTime = m_fDeltaTime * 1000;

	if (fLockedDeltaTime > fCurrentDeltaTime)
	{
		float fSleep = fLockedDeltaTime - m_fDeltaTime;

		Sleep(static_cast<int>(fSleep));
	}


	++ m_iFrameCount;

	if (m_fTimeElapsed > 1.0f)
	{
		sprintf_s(m_cFpsMessage, 32, "FPS: %d", m_iFrameCount);
		m_pFpsText->SetText(m_cFpsMessage);

		m_iFrameCount = 0;
		m_fTimeElapsed = 0.0f;
	}
}

float 
CClock::GetDeltaTick()
{
	float fMinFrames = 60.0f;

	float fMaxDeltaTime = 1.0f / fMinFrames;

	if (fMaxDeltaTime < m_fDeltaTime)
	{
		return (fMaxDeltaTime);
	}

	return(m_fDeltaTime);
}
