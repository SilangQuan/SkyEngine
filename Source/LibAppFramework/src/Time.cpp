#include "../include/Time.h"
#include "../../3rdParty/include/SDL/SDL.h"
float Time::deltaTime = 0;
float Time::time = 0;
float Time::fps = 0;

float inv1000 = 1.0f / 1000;
Time::Time()
{
	
}

Time::~Time()
{
	
}

void Time::Start()
{
	startMark = SDL_GetTicks() * inv1000;
	lastUpdateMark = SDL_GetTicks()* inv1000;
}

void Time::Stop()
{
	
}

void Time::Restart()
{
	
}

void Time::Update()
{
	lastUpdateMark = time;
	time = SDL_GetTicks() * inv1000 - startMark;
	deltaTime = time - lastUpdateMark;
	//qDebug() <<"deltaTime" << deltaTime;
	fps = 1.0 / deltaTime;
}