//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   PerformanceClock.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
	//Framework
	//Core
	//Game


// This Include
#include "PerformanceClock.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPerformanceClock::CPerformanceClock(__int64 _i64CountsPerSecond)
: m_i64CurrentTime(0) 
, m_i64LastTime(0)
, m_i64CountsPerSecond(_i64CountsPerSecond)
, m_dPerfCounterTimeScale(0.0)
{
	//Empty
}

CPerformanceClock::~CPerformanceClock()
{
	//Empty
}


bool
CPerformanceClock::Initialise()
{
	m_dPerfCounterTimeScale = 1.0 / (double)(m_i64CountsPerSecond);

	CClock::Initialise();

	return (true);
}

bool
CPerformanceClock::Deintiialise()
{
	return (true);
}

void
CPerformanceClock::Process()
{
	m_i64LastTime = m_i64CurrentTime;
		
	QueryPerformanceCounter((LARGE_INTEGER*)&m_i64CurrentTime);
	if(m_i64LastTime == 0)
	{
		m_i64LastTime = m_i64CurrentTime;
	}
	m_fDeltaTime = (m_i64CurrentTime - m_i64LastTime) * static_cast<float>(m_dPerfCounterTimeScale);

	m_fTimeElapsed += m_fDeltaTime;

	CClock::ProcessFPS();
}

void
CPerformanceClock::Draw()
{
	CClock::Draw();
}

