
#pragma once

#ifndef __IGFEB11_MODULE_MANDLEBROT_H__
#define __IGFEB11_MODULE_MANDLEBROT_H__

// Library Includes

// Local Includes
#include "Scene.h"

// Types

// Constants

// Prototypes

class CMandlebrot : public IScene
{
    // Member Functions
public:
	 CMandlebrot();
	~CMandlebrot();

	virtual bool Initialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	void DrawPixel(int _iX, int _iY, short m_sLp, short m_sLpBackup);

protected:

private:

    // Member Variables
public:

protected:

private:
	float m_fCX;
	float m_fCY;

	float m_fScale;

	short m_sLimit;

	short m_sLp;

	float m_fA1;
	float m_fB1;

	float m_fA2;
	float m_fB2;

	int m_iX;
	int m_iY;

	float m_fAX;
	float m_fAY;

	char m_cKey;

};

#endif // __IGFEB11_MODULE_MANDLEBROT_H__
