#pragma once
#include <chrono>

class Time
{
public:
	static float GetDeltaTime( );
	   
	static void Start();
	static void Stop();


	~Time();
};

