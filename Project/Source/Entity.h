//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Entity.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_ENTITY_H__
#define __IGFEB11_IG120_ENTITY_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes

class CEntity
{
    // Member Functions
public:
	CEntity();
	virtual ~CEntity();

	virtual bool Initialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	// Member Inline Functions
	inline void SetPositionX(float _fPositionX);
	inline void SetPositionY(float _fPositionY);
	inline void SetPosition(float _fPositionX, float _fPositionY);
	inline void SetPositionX(int _iPositionX);
	inline void SetPositionY(int _iPositionY);
	inline void SetPosition(int _iPositionX, int _iPositionY);

	inline void SetVelocityX(float _fVelocityX);
	inline void SetVelocityY(float _fVelocityY);
	inline void SetVelocity(float _fVelocityX, float _fVelocityY);
	inline void SetVelocityX(int _iVelocityX);
	inline void SetVelocityY(int _iVelocityY);
	inline void SetVelocity(int _iVelocityX, int _iVelocityY);

	inline void SetRadius(float _fRadius);

	inline void TranslatePositionX(int _iPositionX);
	inline void TranslatePositionY(int _iPositionY);
	inline void TranslatePosition(int _iPositionX, int _iPositionY);
	inline void TranslatePositionX(float _fPositionX);
	inline void TranslatePositionY(float _fPositionY);
	inline void TranslatePosition(float _fPositionX, float _fPositionY);

	inline float GetPositionX() const;
	inline float GetPositionY() const;

	inline float GetVelocityX() const;
	inline float GetVelocityY() const;

	inline float GetRadius();

protected:

private:

    // Member Variables
public:

protected:
	float m_fPositionX;
	float m_fPositionY;

	float m_fVelocityX;
	float m_fVelocityY;

	float m_fRadius;

private:

};

#include "Entity.inl"

#endif // __IGFEB11_IG120_ENTITY_H__
