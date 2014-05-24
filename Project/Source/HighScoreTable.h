//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   HighScoreTable.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_HEIGHSCORETABLE_H__
#define __IGFEB11_IG120_HEIGHSCORETABLE_H__

// Library Includes
#include <vector>

// Local Includes
#include "Scene.h"

// Types

// Constants

// Prototypes
class CText;
class CButton;
class CSpriteEntity;

class CHighScoreTable : public IScene
{
    // Member Functions
public:
	         CHighScoreTable();
	virtual ~CHighScoreTable();

	virtual bool Initialise();
	virtual bool Deinitialise();
	virtual void Process(float _fDeltatick);
	virtual void Draw();
	
	bool InitialiseTitle();
	bool InitialiseText();
	bool InitialiseMainMenuButton();
	bool InitialiseScores();

	bool DeinitialiseTitle();
	bool DeinitialiseText();
	bool DeinitialiseMainMenuButton();

protected:

private:

    // Member Variables
public:

protected:

private:
	int m_iMaxHighScores;

	CSpriteEntity* m_pSEntTitle;

	CText* m_pTxtPlace1;
	CText* m_pTxtPlace2;
	CText* m_pTxtPlace3;
	CText* m_pTxtPlace4;
	CText* m_pTxtPlace5;

	CButton* m_pBtnMainMenu;



};

#endif // __IGFEB11_IG120_HEIGHSCORETABLE_H__
