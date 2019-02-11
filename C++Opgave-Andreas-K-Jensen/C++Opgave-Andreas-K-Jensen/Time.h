#ifndef SOUND_H
#define SOUND_H

#include <chrono>

class Time
{
public:
	static float GetDeltaTime(); //returns the time last update cycle took

	static void Start(); //sets starting point in time
	static void Stop();//sets end point in time and calculates elapsed time


	~Time();
};

#endif // !SOUND_H
