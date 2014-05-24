//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   LogManager.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_LOGMANAGER_H__
#define __IGFEB11_IG120_LOGMANAGER_H__

// Library Includes
#include <set>

// Local Includes
#include "LogTarget.h"

// Types

// Constants

// Prototypes


class CLogManager
{
    // Member Functions
public:
	CLogManager();
	~CLogManager();

	bool Initialise(const char* _pcIniFile);
	bool AddLogTarget(ILogTarget* _pLogTarget);
	bool RemoveLogTarget(ILogTarget* _pLogTarget);
	void Write(const char* _pcMessage);
	void WriteLine(const char* _pcMessage);
	void WriteLine(int _iValue);
	void WriteLine(float _iValue);

protected:

private:

    // Member Variables
public:

protected:

private:
	std::set<ILogTarget*> m_setTargetContainer;

};

#endif // __IGFEB11_IG120_LOGMANAGER_H__
