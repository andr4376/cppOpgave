#include "GameWorld.h"



GameWorld::GameWorld(GLFWwindow * windowContext)
{
	window = windowContext;
	tmpGO = new GameObject();

	glEnable(GL_TEXTURE_2D); //Aktivere tektur mapning
	//Specificere hvorledes tekture interpoliseres over overflader
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}


GameWorld::~GameWorld()
{
	//Husk at ryde op
	delete tmpGO;
}

void GameWorld::GameLoop()
{
	GameLogic();
	Render();
	glfwPollEvents();
}

void GameWorld::GameLogic()
{


	tmpGO->Update();



	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //Tjekker op på at ESC er trykket ned, hvis ja luk vinduet
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		tmpGO->direction = -1; // Gå til venstre
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		tmpGO->direction = 1; // Gå til højre
	}


}

void GameWorld::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity(); //Null stiller OpenGL matrise

	tmpGO->Render();

	glfwSwapBuffers(window);

}