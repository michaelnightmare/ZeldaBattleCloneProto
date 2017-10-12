#include "Animator.h"
#include <iostream>


Animator::Animator(GameObject* AnimatedObj) : owner(AnimatedObj),

m_column(0), m_row(0), m_timer(0.15f), m_timeElapsed(0.f)
{
	
}

void Animator::Update(sf::RenderWindow* window, float dt)
{
	//Starts idle (base row = 0, base column = 0)

	owner->body.setTextureRect(sf::IntRect(m_column * 65, m_row * 65, 65, 67));
	
	LoopAnimation(dt,framecount);
}

int Animator::ChooseRow(AnimationType type)
{
	switch (type)
	{
	
	case AnimationType::IDLED:
	{	
		framecount = 4;
		return m_row = 2;
		break;
	}
	case AnimationType::IDLER:
	{
		framecount = 3;
		return m_row = 3;
		break;
	}
	case AnimationType::IDLEU:
	{
		framecount = 3;
		return m_row = 0;
		break;
	}
	case AnimationType::IDLEL:
	{
		framecount = 3;
		return m_row = 1;
		break;
	}


	case AnimationType::RUN:
	{
		
		framecount = 8;
		return m_row = 11;
		break;
	}

	case AnimationType::RUNL:
	{
		
		framecount = 8;
		return m_row = 9;
		break;
	}

	case AnimationType::RUNU:
	{

		framecount = 8;
		return m_row = 8;
		break;
	}

	case AnimationType::RUND:
	{

		framecount = 8;
		return m_row = 10;
		break;
	}

	case AnimationType::SWINGD:
	{

		framecount = 5;
		return m_row = 14;
		break;
	}

	case AnimationType::SWINGU:
	{

		framecount = 5;
		return m_row = 12;
		break;
	}
	case AnimationType::SWINGR:
	{

		framecount = 5;
		return m_row = 15;
		break;
	}
	case AnimationType::SWINGL:
	{

		framecount = 5;
		return m_row = 13;
		break;
	}

	case AnimationType::SLIMEMOVE:
	{
		framecount = 1;
		return m_row = 0;
		break;
	}
	case AnimationType::SLIMEMOVER:
	{
		framecount = 1;
		return m_row = 1;
		break;
	}
	
	}
}

void Animator::LoopAnimation(float dt,int framecount)
{
	m_timeElapsed -= dt;

	if (m_timeElapsed <= 0)
	{
		m_timeElapsed = m_timer;
		m_column++;
	}

	if (m_column > framecount)

	{
		m_column = 0;

	}
}