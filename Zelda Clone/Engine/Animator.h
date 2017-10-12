#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects.h"

enum AnimationType
{
	IDLED,
	IDLEL,
	IDLER,
	IDLEU,
	RUN,
	RUNL,
	RUNU,
	RUND,
	SWINGD,
	SWINGL,
	SWINGR,
	SWINGU,
	SLIMEMOVE,
	SLIMEMOVER,
};

class Animator
{
public:
	Animator(GameObject* AnimatedObj);
	virtual void Update(sf::RenderWindow* window, float dt);

	int GetRow() { return m_row; }

	int ChooseRow(AnimationType type);
	void LoopAnimation(float dt, int framecount);
	
protected:

	GameObject* owner;

	float m_timeElapsed;
	float m_timer;
	bool flip;
   
	int m_column;
	int m_row;
	int framecount;
};