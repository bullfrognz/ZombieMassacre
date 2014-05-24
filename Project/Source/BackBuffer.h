//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   BackBuffer.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_BACKBUFFER_H__
#define __IGFEB11_IG120_BACKBUFFER_H__

// Library Includes
#include <windows.h>

// Local Includes

// Types

// Constants

// Prototypes


class CBackBuffer
{
    // Member Functions
public:
	 CBackBuffer();
	~CBackBuffer();

	bool Initialise(HWND _hWindow, int _iWidth, int _iHeight);
	void Present();
	void Clear();

	// Member Inline Functions
	inline HDC GetBFDC() const;
	inline int GetWidth() const;
	inline int GetHeight() const;

protected:

private:

    // Member Variables
public:

protected:

private:
	HWND	m_hWindow;
	HDC		m_hDC;

	HBITMAP m_hSurface;
	HBITMAP m_hOldObject;

	int		m_iWidth;
	int		m_iHeight;

};

#include "BackBuffer.inl"

#endif // __IGFEB11_IG120_BACKBUFFER_H__
