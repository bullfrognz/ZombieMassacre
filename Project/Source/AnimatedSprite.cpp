//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   AnimatedSprite.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>

// Local Includes
	//Framework
	#include "Application.h"
	#include "Window.h"
	#include "BackBuffer.h"
	#include "Utilities.h"
	//Core
	#include "Animation.h"
	//Game

// This Include
#include "AnimatedSprite.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAnimatedSprite::CAnimatedSprite()
: m_iAnimationName(0)
, m_iAnimationNumFrames(0)
, m_iCurrentFrame(0)
, m_fFrameSpeed(0.0f)
, m_fTimeElapsed(0.0f)
{
	//Empty
}

CAnimatedSprite::~CAnimatedSprite()
{
	ClearAnimations();
}

bool
CAnimatedSprite::Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId, int _iFrameWidth)
{
	CSprite::Initialise(_kiSpriteResourceId, _kiMaskResourceId);
	CSprite::SetFrameWidth(_iFrameWidth);

	return (true);
}

void
CAnimatedSprite::Process(float _fDeltaTick)
{
	CSprite::Process(_fDeltaTick);

	m_fTimeElapsed += _fDeltaTick;

	if (m_fTimeElapsed >= m_fFrameSpeed && m_fFrameSpeed != 0.0f)
	{
		++ m_iCurrentFrame;

		if (m_iCurrentFrame >= m_iAnimationNumFrames)
		{
			m_iCurrentFrame = 0;
		}

		m_fTimeElapsed = 0.0f;
	}
}

void
CAnimatedSprite::Draw()
{
	int iFrameWidth = CSprite::GetFrameWidth();

	CSprite::SetFrameStartX(iFrameWidth * m_iCurrentFrame);

	CSprite::Draw();
}

void
CAnimatedSprite::AddAnimation(CAnimation& _rAnimation)
{
	int iAnimationAlias = _rAnimation.GetName();

	std::map<int, CAnimation*>::iterator Iter;
	Iter = m_mapAnimation.find(iAnimationAlias);
	assert(Iter == m_mapAnimation.end()); //Animation already exists.

	m_mapAnimation.insert(std::pair<int, CAnimation*>(iAnimationAlias , &_rAnimation));
}

void
CAnimatedSprite::PlayAnimation(const char* _kcpAnimationAlias)
{
	int iAnimationAlias = ConvertCharIntSum(_kcpAnimationAlias);

	std::map<int, CAnimation*>::iterator Iter;

	Iter = m_mapAnimation.find(iAnimationAlias);
	assert(Iter != m_mapAnimation.end()); //Animation does not exists.

	CAnimation& rAnimation = (*(*Iter).second);

	m_iAnimationName = rAnimation.GetName();
	m_iAnimationNumFrames = rAnimation.GetNumFrames();

	CSprite::SetFrameWidth(rAnimation.GetFrameWidth());
	CSprite::SetFrameHeight(rAnimation.GetFrameHeight());

	CSprite::SetFrameStartX(rAnimation.GetStartPositionX());
	CSprite::SetFrameStartY(rAnimation.GetStartPositionY());

	m_fFrameSpeed = rAnimation.GetFrameSpeed();

	m_iCurrentFrame = 0;
}

void
CAnimatedSprite::ClearAnimations()
{	
	std::map<int, CAnimation*>::iterator Iter;

	for (Iter = m_mapAnimation.begin(); Iter != m_mapAnimation.end(); )
	{
		delete (*Iter).second;
		(*Iter).second = 0;

		Iter = m_mapAnimation.erase(Iter);
	}
}