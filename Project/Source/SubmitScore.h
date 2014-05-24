//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   SubmitScore.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_SUBMITSCORE_H__
#define __IGFEB11_IG120_SUBMITSCORE_H__

// Library Includes

// Local Includes
#include "Scene.h"
#include "MessageTarget.h"

// Types

// Constants

// Prototypes
class CText;
class CButton;
class CSpriteEntity;

class CSubmitScore : public IScene, public IMessageTarget
{
    // Member Functions
public:
	         CSubmitScore();
	virtual ~CSubmitScore();

	virtual bool Initialise();
	virtual bool Deinitialise();
	virtual void Process(float _fDeltatick);
	virtual void Draw();

	bool InitialiseScores();

	virtual void HandleMessage(EMESSAGECODE _eMessageCode, WPARAM _wParam, LPARAM _lParam);

	void AddLetter(char _cLetter);
	void Backspace();
	void AcceptName();

protected:

private:

    // Member Variables
public:

protected:

private:
	int m_iPlace1Score;
	int m_iPlace2Score;
	int m_iPlace3Score;
	int m_iPlace4Score;
	int m_iPlace5Score;

	CText* m_pScore;
	CText* m_pPlayerName;
	CText* m_pMessage;

	char* m_kcpPlayerName;
};

#endif // __IGFEB11_IG120_SUBMITSCORE_H__
