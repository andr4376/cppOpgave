#ifndef SOUND_H
#define SOUND_H
#include <irrKlang.h>

#define SOUND_TEST "example.wav"

using namespace irrklang;



class Sound
{
public:
	static void Play(const char audioFile[]); //play a specefic file
	static void Play(); //plays test sound


	~Sound();
};



#endif // !SOUND_H
