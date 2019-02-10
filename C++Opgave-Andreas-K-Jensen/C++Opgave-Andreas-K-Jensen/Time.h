#ifndef SOUND_H
#define SOUND_H

#include <chrono>

class Time
{
public:
	static float GetDeltaTime( );
	   
	static void Start();
	static void Stop();


	~Time();
};

#endif // !SOUND_H
