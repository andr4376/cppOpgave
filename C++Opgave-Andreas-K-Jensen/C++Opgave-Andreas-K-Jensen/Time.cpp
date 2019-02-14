#include "Time.h"
#include "GameWorld.h"

static float deltaTime;

static TimePoint gameStartTime = Clock::now();

static TimePoint start = Clock::now();
static TimePoint stop = Clock::now();




float Time::GetDeltaTime()
{
	return deltaTime;
}

void Time::Start()
{
	start = Clock::now();

}

//Stops the timer, and sets deltatime (elapsed time this update)
void Time::Stop()
{
	stop = Clock::now();

	fSecond elapsed = stop - start;

	deltaTime = elapsed.count();


}

//sets start time for when we entered the game loop
void Time::SetStartTime()
{
	gameStartTime = Clock::now();
}

//returns the amoun of time (f) since we entered the game loop
float Time::GetTotalGameTime()
{

	fSecond elapsed = Clock::now() - gameStartTime;

	return elapsed.count();
}

Time::~Time()
{

}

