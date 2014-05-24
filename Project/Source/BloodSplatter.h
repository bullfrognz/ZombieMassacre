//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   BloodSplatter
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_BLOODSPLATTER_H__
#define __IGFEB11_IG120_BLOODSPLATTER_H__

// Library Includes

// Local Includes

// Types

// Constants
const int g_kiMaxParticles = 250;

// Prototypes
class CParticle;

class CBloodSplatter
{
    // Member Functions
public:
	 CBloodSplatter();
	~CBloodSplatter();

	bool Initialise();
	void Process(float _fDeltaTick);
	void Draw();
	
	bool InitialiseParticles();
	void ProcessFrameLifeSpan();
	void ProcessParticles(float _fDeltaTick);
	void DrawParticles();

	void ReleaseParticles();

	// Member Inline Functions
	inline void SetPosition(float _fPsoitionX, float _fPositionY);
	inline void SetNumParticlesToUse(int _iNumParticles);

	inline float GetPositionX() const;
	inline float GetPositionY() const;
	inline int GetNumParticlesToUse() const;

	inline bool IsInUse();

protected:

private:

    // Member Variables
public:

protected:

private:
	CParticle* m_pParticles[g_kiMaxParticles]; //Self Access Only.

	float m_fMovementVelocty;

	float m_fPositionX; //Client Changeable.
	float m_fPositionY; //Client Changeable.

	int m_iNumParticlesToUse; //Client Changeable.

	int m_iFrameLifeSpanMin; //Initialise Locked.
	int m_iFrameLifeSpanMax; //Initialise Locked.
	int m_iVelocityMin; //Initialise Locked.
	int m_iVelocityMax; //Initialise Locked.

	int m_iFrameLifeSpan; //Self Access Only.
	int m_iFrameCount; //Self Access Only.

	bool m_bInUse; //Client Viewable.

};

#include "BloodSplatter.inl"

#endif // __IGFEB11_IG120_BLOODSPLATTER_H__
