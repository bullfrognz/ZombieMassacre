#include <cmath>
#include <windows.h>

// Local Includes
#include "Application.h"
#include "Window.h"
#include "BackBuffer.h"
#include "Utilities.h"

// This Include
#include "Mandelbrot.h"

// Implementation
CMandlebrot::CMandlebrot()
: m_fCX(0.0f)
, m_fCY(0.0f)
, m_fScale(0.0f)
, m_sLimit(0)
, m_sLp(0)
, m_fA1(0.0f)
, m_fB1(0.0f)
, m_fA2(0.0f)
, m_fB2(0.0f)
, m_iX(0)
, m_iY(0)
, m_fAX(0.0f)
, m_fAY(0.0f)
, m_cKey(0)
{
	//Empty
}

CMandlebrot::~CMandlebrot()
{
	//Emtpy
}

bool
CMandlebrot::Initialise()
{
	short m_sLpBackup = 0;

	m_fCX = 0.00;
	m_fCY = 0.00;

	m_fScale = 0.00399f;

	m_sLimit = 2;

	for (int x = -420; x < 300; ++x)
	{
		for (int y = -260; y <= 260; ++y)
		{
			m_fAX = m_fCX + (x * m_fScale);
			m_fAY = m_fCY + (y * m_fScale);

			m_fA1 = m_fAX;
			m_fB1 = m_fAY;

			m_sLp = 0;

			while (true)
			{
				++ m_sLp;

				m_fA2 = (m_fA1 * m_fA1) - (m_fB1 * m_fB1) + (m_fAX);
				m_fB2 = 2 * (m_fA1 * m_fB1) + (m_fAY);

				m_fA1 = m_fA2;
				m_fB1 = m_fB2;

				if (m_sLp > 255)
				{
					break;
				}

				if ((m_fA1 * m_fA1) + (m_fB1 * m_fB1) > m_sLimit)
				{
					break;
				}

			}

			if (m_sLp > 255)
			{
				m_sLpBackup = m_sLp;
				m_sLp = 0;
			}

			DrawPixel(x + 470, y + 290, m_sLp, y);
		}
	}

	Sleep(1000000);

	return true;
}

void
CMandlebrot::Process(float _fDeltaTick)
{

}

void
CMandlebrot::Draw()
{
}

void
CMandlebrot::DrawPixel(int _iX, int _iY, short m_sLp, short m_sLpBackup)
{
	//short a = 100;
	//short b = 100;
	//bool  c = false;

	//short v = a + b*320;

	HDC WindowDC = GetDC(CApplication::GetInstance().GetGameWindow().GetHandle());

	if (m_sLp == 0)
	{
		SetPixel(WindowDC, _iX, _iY, RGB(m_sLpBackup * 1 % 254, m_sLpBackup % 254, m_sLpBackup * 1 % 254));
	}
	else
	{
		SetPixel(WindowDC, _iX, _iY, RGB(m_sLp, m_sLp, m_sLp));
	}

	ReleaseDC(CApplication::GetInstance().GetGameWindow().GetHandle(), WindowDC);
}