#include "Sound.h"

static ISoundEngine* engine = createIrrKlangDevice();

void Sound::Play(const char audioFile[])
{
	engine->play2D(audioFile);
}

void Sound::Play()
{
	Play(SOUND_TEST);
}



Sound::~Sound()
{
}




