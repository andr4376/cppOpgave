#ifndef SOUND_H
#define SOUND_H

#include <irrKlang.h>

using namespace irrklang;

ISoundEngine* engine = nullptr;


class Sound
{
public:
	Sound();
	~Sound();
};

#endif // !SOUND_H
