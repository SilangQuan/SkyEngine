#pragma once
#include <stdlib.h>  

class Random
{
public:
	static void SetSeed(int seed){ srand(seed); };

	static float Range(float min, float max)
	{
		float tmp = 0.01f * Range(1, 100);
		if(max > min)
		{
			float delta = max - min;
			return tmp * delta;
		}/*else
		{
			qDebug() << "error! max must bigger than min";
		}*/
	}

	static float Range(int min, int max)
	{
		return rand() % max;
	}

};