#include "Globals.h"
#include <iostream>
#include <GLFW\glfw3.h>
#include "GameWorld.h"
#include "GameObject.h"
#include "Sound.h"
#include "Vector2.h"


int main()
{
	TEST_AUDIO
	glfwInit(); //Initialisering af glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); //S�tte �vre OpenGl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); //S�tte nedre OpenGl Version

	glViewport(0, 0, SCREEN_HEIGHT, SCREEN_WIDHT); //Oprettet en viewport gennem OpenGL kald



	GameWorld::GetInstanceRef();


	GameWorld::GetInstanceRef().GameLoop();





	glfwTerminate(); //Lukker evt. �bnede vinduer og frigiver resurse brugt her til
	return 0;
}