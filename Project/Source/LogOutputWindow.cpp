//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   "-----"
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes

// This Include
#include "LogOutputWindow.h"

// Static Variables

// Static Function Prototypes

// Implementation

CLogOutputWindow::CLogOutputWindow()
{
	// Default Constructor.
}

CLogOutputWindow::~CLogOutputWindow()
{
	// Default Destructor.
}

bool 
CLogOutputWindow::Initialise(const char* _pcIniFile)
{
	return(true);
}

void 
CLogOutputWindow::Write(const char* _pcMessage)
{
	int iMsgLen = lstrlenA(_pcMessage);
	int iWMsgLen;
	BSTR unicodeMsg;

	iWMsgLen = ::MultiByteToWideChar(CP_ACP, 0, _pcMessage, iMsgLen, 0, 0);
	if (iWMsgLen > 0)
	{
	  // Check whether conversion was successful
	  unicodeMsg = ::SysAllocStringLen(0, iWMsgLen);
	  ::MultiByteToWideChar(CP_ACP, 0, _pcMessage, iMsgLen, unicodeMsg, iWMsgLen);
	}

	// Free the BSTR
	::SysFreeString(unicodeMsg);

	OutputDebugString(unicodeMsg);
}