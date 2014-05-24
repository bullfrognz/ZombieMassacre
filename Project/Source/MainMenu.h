//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MainMenu.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_MAINMENU_H__
#define __IGFEB11_IG120_MAINMENU_H__

// Library Includes

// Local Includes
#include "Scene.h"

// Types

// Constants

// Prototypes
class CSpriteEntity;
class CButton;

class CMainMenu : public IScene
{
    // Member Functions
public:
	 CMainMenu();
	~CMainMenu();

	virtual bool Initialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

protected:

private:

    // Member Variables
public:

protected:

private:
	CSpriteEntity* m_pGameTitle;

	CButton* m_pButtonPlayGame;
	CButton* m_pButtonViewHighScores;
	CButton* m_pButtonQuitGame;

};

#endif // __IGFEB11_IG120_MAINMENU_H__
