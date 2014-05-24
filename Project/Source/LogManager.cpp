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
#include <cassert>
#include <cstring>

// Local Includes
#include "LogTarget.h"
#include "LogOutputWindow.h"

// This Include
#include "LogManager.h"

// Static Variables

// Static Function Prototypes

// Implementation
CLogManager::CLogManager()
{
	ILogTarget* pLogTarget = new CLogOutputWindow;

	AddLogTarget(pLogTarget);
}

CLogManager::~CLogManager()
{
	// Check if the object was added to the set.
	std::set<ILogTarget*>::iterator iter;

	for(iter = m_setTargetContainer.begin(); iter != m_setTargetContainer.end(); ++iter)
	{
		delete (*iter);
	}
}

bool 
CLogManager::Initialise(const char* _pcIniFile)
{
	return(true);
}

bool 
CLogManager::AddLogTarget(ILogTarget* _pLogTarget)
{
	std::set<ILogTarget*>::iterator iter;

	assert(_pLogTarget);
	m_setTargetContainer.insert(_pLogTarget);
	
	// Check if the object was added to the set.
	for(iter = m_setTargetContainer.begin(); iter != m_setTargetContainer.end(); ++iter)
	{
		if(*iter == _pLogTarget)
		{
			return(true);
		}
	}
	return(false);
}

bool 
CLogManager::RemoveLogTarget(ILogTarget* _pLogTarget)
{
	assert(_pLogTarget);
	m_setTargetContainer.erase(_pLogTarget);
	return(true);
}

void 
CLogManager::Write(const char* _pcMessage)
{
	std::set<ILogTarget*>::iterator iter;

	// Iterate through each log stream and print out message.
	for(iter = m_setTargetContainer.begin(); iter != m_setTargetContainer.end(); ++iter)
	{
		(*iter)->Write(_pcMessage);
	}
}

void 
CLogManager::WriteLine(const char* _pcMessage)
{
	std::set<ILogTarget*>::iterator iter;

	// Iterate through each log stream and print out message.
	for(iter = m_setTargetContainer.begin(); iter != m_setTargetContainer.end(); ++iter)
	{
		(*iter)->Write(_pcMessage);
		(*iter)->Write("\n");
	}
}

void
CLogManager::WriteLine(int _iValue)
{
	char* kcpmessage = new char[32];

	sprintf_s(kcpmessage, 32, "%d", _iValue);

	WriteLine(kcpmessage);

	delete kcpmessage;
	kcpmessage = 0;
}

void
CLogManager::WriteLine(float _iValue)
{
	char* kcpmessage = new char[100];

	sprintf_s(kcpmessage, 100, "%f", _iValue);

	WriteLine(kcpmessage);
}
