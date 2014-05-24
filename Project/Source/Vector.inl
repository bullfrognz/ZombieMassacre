//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Vector.inl
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

float
CVector::GetDirectionAngle()
{
	if (m_fDirectionAngle == 0.00f)
	{
		CalculateDirectionAngle();
	}

	return (m_fDirectionAngle);
}

char
CVector::GetQuadrant()
{
	if (m_cQuadrant == 0)
	{
		CalculateQuadrant();
	}

	return (m_cQuadrant);
}

float
CVector::GetMagnitude()
{
	if (m_fMagnitude == 0.0f)
	{
		CalculateMagnitude();
	}

	return (m_fMagnitude);
}

float
CVector::GetDisplacementX()
{
	if (m_fDisplacementX == 0.0f && m_fDisplacementY == 0.0f)
	{
		CalculateDisplacement();
	}

	return (m_fDisplacementX);
}

float
CVector::GetDisplacementY()
{
	if (m_fDisplacementX == 0.0f && m_fDisplacementY == 0.0f)
	{
		CalculateDisplacement();
	}

	return (m_fDisplacementY);
}

float
CVector::GetStartPositionX()
{
	return (m_fStartPositionX);
}

float
CVector::GetStartPositionY()
{
	return (m_fStartPositionY);
}

float
CVector::GetEndPositionX()
{
	return (m_fEndPositionX);
}

float
CVector::GetEndPositionY()
{
	return (m_fEndPositionY);
}

float
CVector::GetNormalisedX()
{
	if (m_fNormalisedDisplacementX == 0.0f && m_fNormalisedDisplacementY == 0.0f)
	{
		CalculateNormaliseDisplacement();
	}
	
	return (m_fNormalisedDisplacementX);
}

float
CVector::GetNormalisedY()
{
	if (m_fNormalisedDisplacementX == 0.0f && m_fNormalisedDisplacementY == 0.0f)
	{
		CalculateNormaliseDisplacement();
	}
	
	return (m_fNormalisedDisplacementY);
}