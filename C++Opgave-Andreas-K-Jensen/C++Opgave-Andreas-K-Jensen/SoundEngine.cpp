#include "SoundEngine.h"
#include <irrKlang.h>

void SoundEngine::Play(const char audioFile[])
{
	if (!engine)
	{
		engine = createIrrKlangDevice();
	}
	engine->play2D(audioFile);

}
