//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Scene.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_SCENE_H__
#define __IGFEB11_IG120_SCENE_H__

// Library Includes

// Local Includes

// Types
enum EWINDOWSCENE
{
	SCENE_INVALID,
	SCENE_MAINMENU,
	SCENE_HIGHSCORETABLE,
	SCENE_GAME,
	SCENE_SUBMITSCORE,
	SCENE_MAX
};

// Constants

// Prototypes


class IScene
{
    // Member Functions
public:
	IScene() {};
	virtual ~IScene() {};

	virtual bool Initialise() = 0;
	virtual void Draw() = 0;
	virtual void Process(float _fDeltatick) = 0;

protected:

private:

    // Member Variables
public:

protected:

private:

};

#endif // __IGFEB11_IG120_SCENE_H__
