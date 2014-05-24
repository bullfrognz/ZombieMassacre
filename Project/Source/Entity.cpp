//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Entity.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Include
#include "Entity.h"

// Static Variables

// Static Function Prototypes

// Implementation
CEntity::CEntity()
: m_fPositionX(0.0f)
, m_fPositionY(0.0f)
, m_fVelocityX(0.0f)
, m_fVelocityY(0.0f)
, m_fRadius(0.0f)
{
	//Empty
}

CEntity::~CEntity()
{
	//Empty
}

bool
CEntity::Initialise()
{
	//Empty

	return (true);
}

void
CEntity::Process(float _fDeltaTick)
{
	if (m_fVelocityX != 0.0f)
	{
		float fDisplacementX = m_fVelocityX * _fDeltaTick;
		TranslatePositionX(fDisplacementX);
	}

	if (m_fVelocityY != 0.0f)
	{
		float fDisplacementY = m_fVelocityY * _fDeltaTick;
		
		fDisplacementY *= -1; //Invert Y axis

		TranslatePositionY(fDisplacementY);
	}
}

void
CEntity::Draw()
{
	//Emtpy
}