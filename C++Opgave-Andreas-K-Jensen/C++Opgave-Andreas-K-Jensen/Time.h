#ifndef TIME_H
#define TIME_H

#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliSeconds;
typedef std::chrono::duration<float> fSecond;
typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;
class Time
{
public:
	static float GetDeltaTime(); //returns the time last update cycle took

	static void Start(); //sets starting point in time
	static void Stop();//sets end point in time and calculates elapsed time

	static void SetStartTime(); //sets starting point in time
	float GetTotalGameTime();
	
	~Time();
};

#endif // !TIME_H
