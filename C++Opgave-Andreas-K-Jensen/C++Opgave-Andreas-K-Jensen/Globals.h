#ifndef GLOBALS_H
#define GLOBALS_H



//Removes Pointers. 
#define  REMOVE_PTR(ptr) if (ptr != nullptr) {delete ptr; ptr = nullptr;}

#define SCREEN_WIDHT 800
#define SCREEN_HEIGHT 600

#pragma region DEBUG/RELEASE Macros

#ifdef __DEBUG__
#define TEST_AUDIO Sound::Play();
#define DEBUG_LOG(x) std::cout<< x << std::endl;
#endif // __DEBUG__



#ifdef __RELEASE__
#define TEST_AUDIO 
#define DEBUG_LOG(x) 

#endif // __RELEASE__

#pragma endregion

#endif // !GLOBALS_H



