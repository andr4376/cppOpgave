#ifndef GLOBALS_H
#define GLOBALS_H
//This .h file contains global functions, variables, macros and definitions


//Macro that removes Pointers. 
//TODO: caution! consider making <template>funtion instead, this macro is not unsafe
#define  REMOVE_PTR(ptr) if (ptr != nullptr) {delete ptr; ptr = nullptr;}


//game window settings
#define SCREEN_WIDHT 800
#define SCREEN_HEIGHT 600


#define LEFT_GAME_BORDER -1
#define RIGHT_GAME_BORDER 1
#define TOP_GAME_BORDER 1
#define BOTTOM_GAME_BORDER -1

//game settings
#define PLAYER_SPEED 1
#define PLAYER_SIZE 10

//Macros that will change/disable functionality depending on Configuration (debug / release)
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



