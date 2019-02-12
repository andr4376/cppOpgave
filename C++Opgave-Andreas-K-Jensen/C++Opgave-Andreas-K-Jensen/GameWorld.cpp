#include "Globals.h"
#include "Asteroid.h"
#include "GameWorld.h"
#include "Player.h"

#include "Time.h"
#include<thread>
#include<iostream>

static GameWorld* instancePtr = nullptr;

void size_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//Private Constructor for gameworld (Singleton pattern)
GameWorld::GameWorld()
{

	Init();


}


GameWorld::~GameWorld()
{

	REMOVE_PTR(instancePtr);


	for (GameObject* goPtr : gameObjects)
	{
		REMOVE_PTR(goPtr);
	}
	for (Collider* colliderPtr : colliders)
	{
		REMOVE_PTR(colliderPtr);
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

		//std::this_thread::sleep_for(std::chrono::milliseconds(64)); //fps

		Time::Stop(); // stops timer, saves elapsed time (deltatime)
	}
	DEBUG_LOG("Exiting Game Loop");

}

void GameWorld::GameLogic()
{

	for (GameObject* goPtr : gameObjects)
	{
		goPtr->Update();
	}

	for (Collider* colliderPtr : colliders)
	{
		colliderPtr->CheckCollision();
	}


	if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS) //Tjekker op på at ESC er trykket ned, hvis ja luk vinduet
	{
		glfwSetWindowShouldClose(windowPtr, true);
	}



}

void GameWorld::Render()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity(); //Null stiller OpenGL matrise

	for (GameObject* go : gameObjects)
	{
		go->Render();
	}

	glfwSwapBuffers(windowPtr);

}

void GameWorld::Init()
{
	SetupWindow();

	PlaceGameObjects();
}

void GameWorld::SetupWindow()
{


	if (windowPtr == nullptr)
	{

		windowPtr = glfwCreateWindow(SCREEN_WIDHT, SCREEN_HEIGHT, "Andreas K Jensen", FULLSCREEN_IF_RELEASE, NULL);

		if (windowPtr == NULL)
		{
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(windowPtr); //Sørger for at OpenGL Bruger vinduet som renderings context

	}


	glEnable(GL_TEXTURE_2D); //Aktivere tektur mapning
	//Specificere hvorledes tekture interpoliseres over overflader
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glfwSetFramebufferSizeCallback(windowPtr, size_resize_callback); //Sikre at hvis vinduets størrelse ændres ændres viewport også
}

void GameWorld::PlaceGameObjects()
{
	GameObject* go = new GameObject(VECTOR_ZERO, DEFAULT_OBJECT_SIZE);
	Collider* goC = new Collider(go);

	gameObjects.push_back(go);
	colliders.push_back(goC);

	Asteroid* mGo = new Asteroid(Vector2(-2, 0));
	Collider* mGoC = new Collider(mGo);

	gameObjects.push_back(mGo);
	colliders.push_back(mGoC);

	Player* d = new Player(VECTOR_LEFT, PLAYER_SPEED);
	Collider* dC = new Collider(d);
	gameObjects.push_back(d);
	colliders.push_back(dC);
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

std::vector<Collider*>& GameWorld::GetColliders()
{
	return colliders;
}
