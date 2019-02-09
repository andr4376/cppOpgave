#include "Sound.h"


Sound::Sound()
{
	engine = createIrrKlangDevice();
	engine->play2D("example.mp3");


}

Sound::~Sound()
{
}


