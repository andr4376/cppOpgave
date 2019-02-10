#include "GameWorld.h"
#include "Player.h"
#include <chrono>
#include "Time.h"

static GameWorld* instance = nullptr;

void size_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

///Private Constructor for gameworld (Singleton pattern)
GameWorld::GameWorld()
{
	if (window == nullptr)
	{
		window = glfwCreateWindow(800, 600, "Andreas K Jensen", NULL, NULL);
		if (window == NULL)
		{
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(window); //Sørger for at OpenGL Bruger vinduet som renderings context

	}

	GameObject* go = new GameObject();

	gameObjects.push_back(go);

	Player* d = new Player();

	gameObjects.push_back(d);


	glEnable(GL_TEXTURE_2D); //Aktivere tektur mapning
	//Specificere hvorledes tekture interpoliseres over overflader
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glfwSetFramebufferSizeCallback(window, size_resize_callback); //Sikre at hvis vinduets størrelse ændres ændres viewport også

}


GameWorld::~GameWorld()
{

	REMOVE_PTR(instance);


	for (GameObject* go : gameObjects)
	{
		REMOVE_PTR(go);
	}
}

void GameWorld::GameLoop()
{
	while (!glfwWindowShouldClose(window)) // Køre så længe glfw vinduet ikke har fået besked på at lukke (f.eks. tryk på X knappen)
	{
		Time::Start();

		GameLogic();
		Render();
		glfwPollEvents();


		auto finish = std::chrono::high_resolution_clock::now();

		

		Time::Stop();
	}
}

void GameWorld::GameLogic()
{

	for (GameObject* go : gameObjects)
	{
		go->Update();
	}



	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //Tjekker op på at ESC er trykket ned, hvis ja luk vinduet
	{
		glfwSetWindowShouldClose(window, true);
	}



}

void GameWorld::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity(); //Null stiller OpenGL matrise

	for (GameObject* go : gameObjects)
	{
		go->Render();
	}

	glfwSwapBuffers(window);

}

GameWorld* GameWorld::GetInstance()
{
	if (instance == 0)
	{
		instance = new GameWorld();
	}

	return instance;

}

GLFWwindow & GameWorld::GetWindow()
{
	GLFWwindow& win = *GetInstance()->window;

	return win;


}
