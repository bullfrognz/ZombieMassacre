//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Particle.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_PARTICLE_H__
#define __IGFEB11_IG120_PARTICLE_H__

// Library Includes

// Local Includes
#include "Entity.h"

// Types

// Constants

// Prototypes

class CParticle : public CEntity
{
    // Member Functions
public:
	         CParticle();
	virtual ~CParticle();

	bool Initialise();
	void Process(float _fDeltaTick);
	void Draw();

	void ProcessFrameLifeSpan();
	void DrawParticle();

	// Member Inline Functions
	inline void SetFrameLifeSpan(int _iNumFrames);
	inline void SetAlive(bool _bAlive);

	inline int GetFrameLifeSpan() const;
	inline bool IsAlive() const;

protected:

private:

    // Member Variables
public:

protected:

private:
	int m_iFrameLifeSpan; //Client Changeable.
	int m_iFrameCount; //Client Changeable.

	bool m_bAlive; //Client Changeable.

};

#include "Particle.inl"

#endif // __IGFEB11_IG120_PARTICLE_H__
