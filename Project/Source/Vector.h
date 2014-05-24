//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Vector.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_VECTOR_H__
#define __IGFEB11_IG120_VECTOR_H__

// Library Includes

// Local Includes

// Types

// Constants
const float g_kfPi = 3.14159265f;

// Prototypes

class CVector
{
    // Member Functions
public:
	 CVector();
	~CVector();

	void SetPositions(float _fStartPositionX, float _fStartPositionY, float _fEndPositionX, float _fEndPositionY);

	// Member Inline Functions
	inline float GetDirectionAngle();

	inline char GetQuadrant();

	inline float GetMagnitude();

	inline float GetDisplacementX();
	inline float GetDisplacementY();

	inline float GetStartPositionX();
	inline float GetStartPositionY();

	inline float GetEndPositionX();
	inline float GetEndPositionY();

	inline float GetNormalisedX();
	inline float GetNormalisedY();

protected:

private:
	void CalculateDirectionAngle();
	void CalculateMagnitude();
	void CalculateDisplacement();
	void CalculateQuadrant();
	void CalculateNormaliseDisplacement();

    // Member Variables
public:

protected:

private:
	float m_fDirectionAngle;
	
	char  m_cQuadrant;

	float m_fMagnitude;

	float m_fDisplacementX;
	float m_fDisplacementY;

	float m_fNormalisedDisplacementX;
	float m_fNormalisedDisplacementY;

	float m_fStartPositionX;
	float m_fStartPositionY;

	float m_fEndPositionX;
	float m_fEndPositionY;

};

#include "Vector.inl"

#endif // __IGFEB11_IG120_VECTOR_H__
