//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   LogOutputWindow.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_LOGOUTPUTWINDOW_H__
#define __IGFEB11_IG120_LOGOUTPUTWINDOW_H__

// Library Includes

// Local Includes
#include "LogManager.h"

// Types

// Constants

// Prototypes


class CLogOutputWindow : public ILogTarget
{
    // Member Functions
public:
		CLogOutputWindow();
		~CLogOutputWindow();

		bool Initialise(const char* _pcIniFile);
		void Write(const char* _pcMessage);

protected:

private:

    // Member Variables
public:

protected:

private:

};

#endif // __IGFEB11_IG120_LOGOUTPUTWINDOW_H__
