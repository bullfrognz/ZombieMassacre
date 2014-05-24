//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Application.inl
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Include

// Static Variables

// Static Function Prototypes

// Implementation
HINSTANCE
CApplication::GetAppInstance()
{
	return m_hInstance;
}
	
CWindow&
CApplication::GetGameWindow()
{
	return (*m_pGameWindow);
}

CLogManager&
CApplication::GetLogManager()
{
	return (*m_pLogManager);
}

CIniParser&
CApplication::GetIniParser()
{
	return (*m_pIniParser);
}

void
CApplication::Quit()
{
	PostQuitMessage(0);
}