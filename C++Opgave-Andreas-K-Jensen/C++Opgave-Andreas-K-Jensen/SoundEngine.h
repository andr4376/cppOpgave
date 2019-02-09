#pragma once
#include <irrKlang.h>
using namespace irrklang;

static class SoundEngine
{
public:
	 static  ISoundEngine* engine;

	 static void Play(const char audioFile[]);
};

