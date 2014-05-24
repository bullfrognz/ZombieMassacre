//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   BackBuffer.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Include
#include "BackBuffer.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBackBuffer::CBackBuffer()
: m_hWindow(0)
, m_hDC(0)
, m_hSurface(0)
, m_hOldObject(0)
, m_iWidth(0)
, m_iHeight(0)
{
}

CBackBuffer::~CBackBuffer()
{
	SelectObject(m_hDC, m_hOldObject);

	DeleteObject(m_hSurface);
	DeleteObject(m_hDC);
}

bool
CBackBuffer::Initialise(HWND _hWindow, int _iWidth, int _iHeight)
{
	m_hWindow = _hWindow;
	m_iWidth  = _iWidth;
	m_iHeight = _iHeight;

	HDC hWindowDC = GetDC(m_hWindow);

	m_hDC = CreateCompatibleDC(hWindowDC);

	m_hSurface = CreateCompatibleBitmap(hWindowDC, m_iWidth, m_iHeight);

	SetBkMode(m_hDC, TRANSPARENT);

	ReleaseDC(m_hWindow, hWindowDC);

	m_hOldObject = static_cast<HBITMAP>(SelectObject(m_hDC, m_hSurface));

	HBRUSH brushWhite = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

	

	Clear();

	return (true);
}

void
CBackBuffer::Present()
{
	HDC hWindowDC = GetDC(m_hWindow);

	BitBlt(hWindowDC, 0, 0, m_iWidth, m_iHeight, m_hDC, 0, 0, SRCCOPY);

	ReleaseDC(m_hWindow, hWindowDC);
}

void
CBackBuffer::Clear()
{
	HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(GetBFDC(), GetStockObject(WHITE_BRUSH)));

	Rectangle(GetBFDC(), 0, 0, GetWidth(), GetHeight());

	SelectObject(GetBFDC(), hOldBrush);
}