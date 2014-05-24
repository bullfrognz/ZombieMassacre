//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Clock.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_CLOCK_H__
#define __IGFEB11_IG120_CLOCK_H__

// Library Includes
#include <windows.h>
#include <windowsx.h>

// Local Includes

// Types

// Constants

// Prototypes
class CText;

class CClock
{
	// Member Functions
public:
	CClock();
	virtual ~CClock();

	virtual bool Initialise();
	virtual bool Deinitialise();
	virtual void Process();
	virtual void Draw();

	void ProcessFPS();

	float GetDeltaTick();

protected:

private:
	CClock(const CClock& _kr);
	CClock& operator=(const CClock& _kr);

	// Member Variables
public:

protected:
	CText* m_pFpsText;

	float m_fDeltaTime;

	float m_fTimeElapsed;
	float m_fLastTime;
	float m_fCurrentTime;

	int m_iFrameCount;

	char* m_cFpsMessage;

private:

};

#endif // __IGFEB11_IG120_CLOCK_H__

