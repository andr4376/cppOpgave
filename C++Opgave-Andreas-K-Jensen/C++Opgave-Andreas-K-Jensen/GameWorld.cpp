#include "Globals.h"
#include "Asteroid.h"
#include "GameWorld.h"
#include "Player.h"
#include "Sound.h"
#include "Time.h"
#include<thread>
#include<iostream>
#include "Spawner.h"
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

	Time::SetStartTime();

	while (!glfwWindowShouldClose(windowPtr)) // Køre så længe glfw vinduet ikke har fået besked på at lukke (f.eks. tryk på X knappen)
	{
		Time::Start(); //Start timer, to measure update timespan

		SpawnObjectsOnInerval();

		AddGameobjects(); //add all gameobjects that are waiting to be added

		GameLogic(); //update game 
		Render(); //draw game

		glfwPollEvents();


		RemoveGameObjects(); //remove all gameobjects that are waiting to be removed

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

		windowPtr = glfwCreateWindow(SCREEN_WIDHT, SCREEN_HEIGHT, "Andreas K Jensen", NULL, NULL);

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
	/*GameObject* go = new GameObject(VECTOR_ZERO, DEFAULT_OBJECT_SIZE);
	Collider* goC = new Collider(go);

	gameObjects.push_back(go);
	colliders.push_back(goC);*/

	//Asteroid* mGo = new Asteroid(Vector2(-2, 0));
	//Collider* mGoC = new Collider(mGo);

	//gameObjects.push_back(mGo);
	//colliders.push_back(mGoC);

	//asteroids
	/*Asteroid* mGo = new Asteroid(Vector2(-1, 0), ASTEROID_MAX_SIZE, VECTOR_DOWN + VECTOR_RIGHT);
	Collider* mGoC = new Collider(mGo);

	gameObjects.push_back(mGo);
	colliders.push_back(mGoC);

	Asteroid* mGo2 = new Asteroid(Vector2(0, 0), ASTEROID_MIN_SIZE, Vector2(-0.6, 0.33));
	Collider* mGoC2 = new Collider(mGo2);

	gameObjects.push_back(mGo2);
	colliders.push_back(mGoC2);

	Asteroid* mGo3 = new Asteroid(VECTOR_UP, 15, Vector2(-0.3, 0.33));
	Collider* mGoC3 = new Collider(mGo3);

	gameObjects.push_back(mGo3);
	colliders.push_back(mGoC3);*/
	//

	//player
	Player* d = new Player(VECTOR_ZERO, PLAYER_SPEED);
	Collider* dC = new Collider(d);
	gameObjects.push_back(d);
	colliders.push_back(dC);
}

void GameWorld::SpawnObjectsOnInerval()
{
	fSecond elapsedTime = Clock::now() - spawnedObjectsTimeStamp;

	if (elapsedTime.count() >= SPAWN_OBJECTS_COOLDOWN)
	{
		Spawner::SpawnGameObject(ASTEROID);

		spawnedObjectsTimeStamp = Clock::now();

		TEST_AUDIO
	}


}

void GameWorld::AddGameobjects()
{
	while (gameObjectsToAdd.size() > 0)
	{
		gameObjects.push_back(gameObjectsToAdd.top());
		gameObjectsToAdd.pop();

	}

	AddColliders();
}

void GameWorld::RemoveGameObjects()
{
	RemoveColliders();
	for (GameObject* go : gameObjectsToRemove)
	{
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), go), gameObjects.end());

		REMOVE_PTR(go);


	}
	gameObjectsToRemove.clear();

}

void GameWorld::AddColliders()
{
	while (collidersToAdd.size() > 0)
	{
		colliders.push_back(collidersToAdd.top());
		collidersToAdd.pop();

	}
}

void GameWorld::RemoveColliders()
{
	//if there are no colliders to be removed
	if (collidersToRemove.size() == 0)
	{
		//exit method
		return;
	}

	for (Collider* collToRemove : collidersToRemove) //for each collider we want to remove
	{
		//remove it from gw's collider list
		colliders.erase(std::remove(colliders.begin(), colliders.end(), collToRemove), colliders.end());


		//for each collider in gw's collider
		for (Collider* collider : instancePtr->colliders)
		{
			//for each of known collider in the abovementioned collider
			for (Collider* collidersCollider : collider->otherColliders)
			{
				//if that collider is the one we're removing
				if (collidersCollider == collToRemove)
				{
					//remove it from that colliders "other colliders"
					collider->otherColliders.erase(std::remove(collider->otherColliders.begin(),
						collider->otherColliders.end(), collToRemove), collider->otherColliders.end());
				}
			}
		}
		//Delete ptr
		REMOVE_PTR(collToRemove);
	}

	collidersToRemove.clear();
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
	return *instancePtr->windowPtr;
}

std::vector<Collider*>& GameWorld::GetColliders()
{
	return colliders;
}
