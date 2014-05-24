//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Window.inl
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

int
CWindow::GetWidth()
{
	return (m_iWidth);
}

int
CWindow::GetHeight()
{
	return (m_iHeight);
}

CBackBuffer&
CWindow::GetBackBuffer()
{
	return (*m_pBackBuffer);
}

CMessageManager&
CWindow::GetMsgManager()
{
	return (*m_pMessageManager);
}

HWND
CWindow::GetHandle()
{
	return (m_hWindow);
}

RECT
CWindow::GetBounds()
{
	return (m_rectBounds);
}

IScene&
CWindow::GetScene()
{
	return (*m_pScene);
}