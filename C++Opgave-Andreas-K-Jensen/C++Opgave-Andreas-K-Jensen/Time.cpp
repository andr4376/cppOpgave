#include "Time.h"
#include "GameWorld.h"

static float deltaTime;

static auto start = std::chrono::high_resolution_clock::now();
static auto stop = std::chrono::high_resolution_clock::now();




float Time::GetDeltaTime()
{
	return deltaTime;
}

void Time::Start()
{
	start = std::chrono::high_resolution_clock::now();

}

void Time::Stop()
{
	stop = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> elapsed = stop - start;

	deltaTime = elapsed.count();

	
}

Time::~Time()
{
}

