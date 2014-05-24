//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   IniParser.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <iostream>

// Local Includes

// This Include
#include "IniParser.h"

// Static Variables

// Static Function Prototypes

// Implementation

CIniParser::CIniParser()
{
	//Empty
}

CIniParser::~CIniParser()
{
	//m_FileStream.close();
}

void Trim(std::string& _string)
{
	while(true)
	{
		size_t WhiteSpacePos = _string.find(' ');
		
		if (WhiteSpacePos == std::string::npos)
		{
			WhiteSpacePos = _string.find('\t');
		}

		if (WhiteSpacePos != std::string::npos)
		{
			_string.erase( WhiteSpacePos , 1 );
			continue;
		}
		
		break;
	}
}

void ConvertLowerCase(std::string& _string)
{
	size_t stringLength = _string.length();

	for (size_t i = 0; i < stringLength; ++i)
	{
		if (_string[i] >= 'A' && _string[i] <= 'Z')
		{
			_string[i] = _string[i] + 32;
		}
	}
}


bool
CIniParser::LoadIniFile(const char* _pcFileName)
{
	m_StrFileName = _pcFileName;

	m_FileStream.open( m_StrFileName );

	if (m_FileStream.is_open())
	{
		std::string StrLine    = "\0";
		std::string StrSection = "\0";

		std::queue<std::string> CommentsQueue;
		std::queue<std::string> EmptyQueue;
		while (!m_FileStream.eof())
		{	
			getline( m_FileStream , StrLine );

			size_t BracketStartPos = StrLine.find( "[" );
			size_t BracketEndPos   = StrLine.find( "]" );
			size_t EqualPos = StrLine.find('=');

			if (BracketStartPos != std::string::npos && BracketEndPos != std::string::npos) //Is Section
			{
				StrSection = StrLine.substr( BracketStartPos + 1 , BracketEndPos -1 );
				Trim(StrSection);
				
				m_IniComments[StrSection] = CommentsQueue;
				CommentsQueue = EmptyQueue;
			}
			else if (EqualPos != std::string::npos) //Is Data Field
			{
				if (StrSection == "\0")
				{
					//cout << "[Ini Read Error] Section has no name" << endl;
				}

				std::string Key	 = StrLine.substr( 0 , EqualPos );
				std::string Value = StrLine.substr( EqualPos + 1 , StrLine.length() );
				
				Trim(Key);
				Trim(Value);

				m_IniData[StrSection][Key] = Value;

				m_IniComments[Key] = CommentsQueue;
				CommentsQueue = EmptyQueue;
			}
			else
			{
				CommentsQueue.push(StrLine);
			}
		}
	
		return true;
	}

	//cout << "Ini file not found!" << endl;

	return false;
}


bool
CIniParser::AddValue(const char* _pcSection, const char* _pcKey, const char* _pcValue)
{
	std::string pcSection = _pcSection;
	std::string pcKey     = _pcKey;
	std::string pcValue   = _pcValue;

	Trim(pcSection);
	Trim(pcKey);
	Trim(pcValue);

	m_IniData[_pcSection][_pcKey] = _pcValue;

	return true;
}

bool
CIniParser::CloseFile(bool _bSave)
{
	if (_bSave == true)
	{
		m_FileStream.clear();
		m_FileStream.close();
		m_FileStream.open(m_StrFileName, std::ios::out);
		m_FileStream.seekp(0);

		std::map< std::string , std::map<std::string,std::string> >::iterator Section_Iter;
		std::map<std::string,std::string>::iterator Data_Iter;
		std::map< std::string , std::queue<std::string> >::iterator Comments_Iter;

		for (Section_Iter = m_IniData.begin(); Section_Iter != m_IniData.end(); ++ Section_Iter)
		{
			Comments_Iter = m_IniComments.find(Section_Iter->first);
			if (Comments_Iter != m_IniComments.end())
			{
				while (!Comments_Iter->second.empty())
				{
					m_FileStream << Comments_Iter->second.front() << std::endl;
					Comments_Iter->second.pop();
				}
			}

			m_FileStream << "[" << Section_Iter->first << "]" << std::endl;

			for (Data_Iter = Section_Iter->second.begin(); Data_Iter != Section_Iter->second.end(); ++ Data_Iter)
			{
				Comments_Iter = m_IniComments.find(Data_Iter->first);
				if (Comments_Iter != m_IniComments.end())
				{
					while (!Comments_Iter->second.empty())
					{
						m_FileStream << Comments_Iter->second.front() << std::endl;
						Comments_Iter->second.pop();
					}
				}

				m_FileStream << Data_Iter->first << "\t= " << Data_Iter->second << std::endl;
			}
		}
		
	}

	m_FileStream.close();
	return true;
}


bool
CIniParser::GetValue(const char* _pcSelection, const char* _pcKey, std::string& _rstringValue)
{
	if (DoesDataExist(_pcSelection,_pcKey) == false)
	{
		return false;
	}

	_rstringValue = m_IniData[_pcSelection][_pcKey];

	return true;
}


bool
CIniParser::GetValue(const char* _pcSelection, const char* _pcKey, int& _riValue)
{
	if (DoesDataExist(_pcSelection,_pcKey) == false)
	{
		return false;
	}

	_riValue = atoi(m_IniData[_pcSelection][_pcKey].c_str());

	return true;
}


bool
CIniParser::GetValue(const char* _pcSelection, const char* _pcKey, float& _rfValue)
{
	if (DoesDataExist(_pcSelection,_pcKey) == false)
	{
		return false;
	}

	_rfValue = static_cast<float>(atof(m_IniData[_pcSelection][_pcKey].c_str()));

	return true;
}


bool
CIniParser::GetValue(const char* _pcSelection, const char* _pcKey, bool& _rbValue)
{
	if (DoesDataExist(_pcSelection,_pcKey) == false)
	{
		return false;
	}

	std::string strData = m_IniData[_pcSelection][_pcKey];

	ConvertLowerCase(strData);

	if (strData == "true" || strData == "on" || strData == "yes" || strData == "1" )
	{
		_rbValue = true;
		return true;
	}

	_rbValue = false;
	return false;
}

bool
CIniParser::DoesDataExist(const char* _kcSectionName, const char* _kcFieldName)
{
	std::map<std::string, std::map<std::string,std::string> >::iterator Iter;

	Iter = m_IniData.find(_kcSectionName);

	if (Iter != m_IniData.end())
	{
		std::map<std::string,std::string>::iterator Iter2;

		Iter2 = (Iter->second).find(_kcFieldName);

		if (Iter2 != Iter->second.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}