//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Vector.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cmath>

// Local Includes

// This Include
#include "Vector.h"

// Static Variables

// Static Function Prototypes

// Implementation

CVector::CVector()
: m_fDirectionAngle(0.0f)
, m_cQuadrant(0)
, m_fMagnitude(0.0f)
, m_fDisplacementX(0.0f)
, m_fDisplacementY(0.0f)
, m_fNormalisedDisplacementX(0.0f)
, m_fNormalisedDisplacementY(0.0f)
, m_fStartPositionX(0.0f)
, m_fStartPositionY(0.0f)
, m_fEndPositionX(0.0f)
, m_fEndPositionY(0.0f)
{
	//Empty
}

CVector::~CVector()
{
	//Empty
}

void
CVector::SetPositions(float _fStartPositionX, float _fStartPositionY, float _fEndPositionX, float _fEndPositionY)
{
	m_fStartPositionX = _fStartPositionX;
	m_fStartPositionY = _fStartPositionY;

	m_fEndPositionX = _fEndPositionX;
	m_fEndPositionY = _fEndPositionY;

	m_fDirectionAngle = 0.0f;
	m_cQuadrant = 0;
	m_fMagnitude = 0.0f;
	m_fDisplacementX = 0.0f;
	m_fDisplacementY = 0.0f;
	m_fNormalisedDisplacementX = 0.0f;
	m_fNormalisedDisplacementY = 0.0f;
}

void
CVector::CalculateDirectionAngle()
{
	if (m_fDisplacementX == 0.0f && m_fDisplacementY == 0.0f)
	{
		CalculateDisplacement();
	}

	m_fDirectionAngle  = atanf(m_fDisplacementY / m_fDisplacementX); //Get angle in radians
	m_fDirectionAngle *= (180.0f / g_kfPi); //Convert to degrees
	m_fDirectionAngle  = abs(m_fDirectionAngle);

	if (m_cQuadrant == 0)
	{
		CalculateQuadrant();
	}

	if (m_cQuadrant == 2)//Quadrant 2
	{
		m_fDirectionAngle = 90.0f + 90.0f - m_fDirectionAngle;
	}
	else if (m_cQuadrant == 3)//Quadrant 3
	{
		m_fDirectionAngle = 180.0f + m_fDirectionAngle;
	}
	else if (m_cQuadrant == 4)//Quadrant 4
	{
		m_fDirectionAngle = 270.0f + 90.0f - m_fDirectionAngle;
	}
	else //Quadrant 1
	{
		//Empty
	}
}

void
CVector::CalculateMagnitude()
{
	float fDisplacementSquaredY = pow(m_fDisplacementX, 2);
	float fDisplacementSquaredX = pow(m_fDisplacementY, 2);

	m_fMagnitude = sqrt( fDisplacementSquaredY + fDisplacementSquaredX );
}

void
CVector::CalculateDisplacement()
{
	m_fDisplacementX = m_fEndPositionX - m_fStartPositionX;
	m_fDisplacementY = m_fStartPositionY - m_fEndPositionY;

	if (m_fDisplacementX == 0.0f)
	{
		m_fDisplacementX = 0.0001f;
	}
	if (m_fDisplacementY == 0.0f)
	{
		m_fDisplacementY = 0.0001f;
	}
}

void
CVector::CalculateQuadrant()
{
	if (m_fDisplacementX <= 0 && m_fDisplacementY >= 0)//Quadrant 2
	{
		m_cQuadrant = 2;
	}
	else if (m_fDisplacementX <= 0 && m_fDisplacementY <= 0)//Quadrant 3
	{
		m_cQuadrant = 3;
	}
	else if (m_fDisplacementX >= 0 && m_fDisplacementY <= 0)//Quadrant 4
	{
		m_cQuadrant = 4;
	}
	else //Quadrant 1
	{
		m_cQuadrant = 1;
	}
}

void
CVector::CalculateNormaliseDisplacement()
{
	if (m_fMagnitude == 0.0f)
	{
		CalculateMagnitude();
	}

	if (m_fMagnitude == 0.0f)
	{
		return ;
	}

	if (m_fDisplacementX == 0.0f && m_fDisplacementY == 0.0f)
	{
		CalculateDisplacement();
	}

	m_fNormalisedDisplacementX = m_fDisplacementX / m_fMagnitude;
	m_fNormalisedDisplacementY = m_fDisplacementY / m_fMagnitude;
}