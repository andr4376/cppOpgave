#ifndef GLOBALS_H
#define GLOBALS_H
//This .h file contains global functions, variables, macros and definitions



//Macro that removes Pointers. 
//TODO: caution! consider making <template>funtion instead, this macro is not unsafe
#define  REMOVE_PTR(ptr) if (ptr != nullptr) {delete ptr; ptr = nullptr;}


//game window settings
#define SCREEN_WIDHT 800
#define SCREEN_HEIGHT 800


#define LEFT_GAME_BORDER -1
#define RIGHT_GAME_BORDER 1
#define TOP_GAME_BORDER 1
#define BOTTOM_GAME_BORDER -1

//game settings
//Player
#define PLAYER_SPEED 1
#define PLAYER_SIZE 10
#define PLAYER_BASE_HEALTH  3
#define PLAYER_MOVEMENT_DAMPENING -2


//Objects in general
#define DEFAULT_OBJECT_SIZE 15

//MovingObject
#define DEFAULT_MOVING_ENTITY_SPEED 0.4

//Asteroids
#define ASTEROID_MIN_SIZE 5
#define ASTEROID_MAX_SIZE 30
#define ASTEROID_SPEED_MODIFER 5
#define ASTEROID_HEALTH_MODIFER 10
#define ASTEROID_ROTATION_SPEED 200



//Macros that will change/disable functionality depending on Configuration (debug / release)
#pragma region DEBUG/RELEASE Macros

#ifdef __DEBUG__

//Play a test sound to check if audio works
#define TEST_AUDIO Sound::Play();

//Writes to console window, only if debug mode
#define DEBUG_LOG(x) std::cout<< x << std::endl;

//Plays in windowed mode if DEBUG
#define FULLSCREEN_IF_RELEASE NULL
#endif // __DEBUG__



#ifdef __RELEASE__
//blank in release
#define TEST_AUDIO 

//blank in release
#define DEBUG_LOG(x) 

//Sets game to fullscreen if executed in Release mode
#define FULLSCREEN_IF_RELEASE glfwGetPrimaryMonitor()
#endif // __RELEASE__

#pragma endregion

#endif // !GLOBALS_H



