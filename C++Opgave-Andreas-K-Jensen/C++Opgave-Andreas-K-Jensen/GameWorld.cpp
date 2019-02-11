#include "Globals.h"
#include "GameWorld.h"
#include "Player.h"
#include <chrono>
#include "Time.h"
#include<iostream>

static GameWorld* instancePtr = nullptr;

void size_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//Private Constructor for gameworld (Singleton pattern)
GameWorld::GameWorld()
{
	if (windowPtr == nullptr)
	{
		windowPtr = glfwCreateWindow(800, 600, "Andreas K Jensen", NULL, NULL);

		if (windowPtr == NULL)
		{
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(windowPtr); //Sørger for at OpenGL Bruger vinduet som renderings context

	}

	GameObject* go = new GameObject(Vector2());

	gameObjects.push_back(go);

	Player* d = new Player(Vector2(), PLAYER_SPEED, PLAYER_SIZE);

	gameObjects.push_back(d);


	glEnable(GL_TEXTURE_2D); //Aktivere tektur mapning
	//Specificere hvorledes tekture interpoliseres over overflader
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glfwSetFramebufferSizeCallback(windowPtr, size_resize_callback); //Sikre at hvis vinduets størrelse ændres ændres viewport også

}


GameWorld::~GameWorld()
{

	REMOVE_PTR(instancePtr);


	for (GameObject* goPtr : gameObjects)
	{
		REMOVE_PTR(goPtr);

	}
}

void GameWorld::GameLoop()
{
	DEBUG_LOG("Entering Game Loop");

	while (!glfwWindowShouldClose(windowPtr)) // Køre så længe glfw vinduet ikke har fået besked på at lukke (f.eks. tryk på X knappen)
	{
		Time::Start(); //Start timer, to measure update timespan

		GameLogic(); //update game 
		Render(); //draw game

		glfwPollEvents();

		Time::Stop(); // stops timer, saves elapsed time (deltatime)
	}
	DEBUG_LOG("Exiting Game Loop");

}

void GameWorld::GameLogic()
{

	for (GameObject* go : gameObjects)
	{
		go->Update();
	}



	if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS) //Tjekker op på at ESC er trykket ned, hvis ja luk vinduet
	{
		glfwSetWindowShouldClose(windowPtr, true);
	}



}

void GameWorld::Render()
{
	glClearColor(1, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity(); //Null stiller OpenGL matrise

	for (GameObject* go : gameObjects)
	{
		go->Render();
	}

	glfwSwapBuffers(windowPtr);

}

GameWorld& GameWorld::GetInstanceRef()
{
	if (instancePtr == nullptr)
	{
		instancePtr = new GameWorld();
	}

	return *instancePtr;

}

//returns a reference of the game's window
GLFWwindow & GameWorld::GetWindow()
{
	//the window reference = the value of the window pointer, stored on the singleton instance 
	GLFWwindow& win = *instancePtr->windowPtr;

	return win;


}
