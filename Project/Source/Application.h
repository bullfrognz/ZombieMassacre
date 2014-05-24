//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Application.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_APPLICATION_H__
#define __IGFEB11_IG120_APPLICATION_H__

// Library Includes
#include <windows.h>

// Local Includes

// Types

// Constants

// Prototypes
class CWindow;
class CLogManager;
class CIniParser;

class CApplication
{
    // Member Functions
public:
	~CApplication();

	static CApplication& GetInstance();
	static void DestroyInstance();

	void Initialise(HINSTANCE _hInstance);

	// Member Inline Funtions
	inline HINSTANCE GetAppInstance();
	inline CWindow& GetGameWindow();
	inline CLogManager& GetLogManager();
	inline CIniParser& GetIniParser();

	inline void Quit();

protected:
	
private:
	CApplication();
	CApplication(const CApplication& _kr);
	CApplication& operator= (const CApplication& _kr);

    // Member Variables
public:

protected:

private:
	HINSTANCE m_hInstance;
	CWindow*  m_pGameWindow;

	CLogManager* m_pLogManager;
	CIniParser* m_pIniParser;

	static CApplication* s_pApplication;

};

#include "Application.inl"

#endif // __IGFEB11_IG120_APPLICATION_H__
