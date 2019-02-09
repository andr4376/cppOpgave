#include <iostream>
#include <GLFW\glfw3.h>
#include "GameObject.h"
#include "GameWorld.h"

GameWorld * gw;

void size_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{

	glfwInit(); //Initialisering af glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); //Sætte øvre OpenGl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); //Sætte nedre OpenGl Version

	GLFWwindow* window = glfwCreateWindow(800, 600, "MyGLFWGLAD1", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Kunne ikke oprette OpenGL Vindue" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //Sørger for at OpenGL Bruger vinduet som renderings context



	glViewport(0, 0, 800, 600); //Oprettet en viewport gennem OpenGL kald

	glfwSetFramebufferSizeCallback(window, size_resize_callback); //Sikre at hvis vinduets størrelse ændres ændres viewport også

	gw = new GameWorld(window);

	while (!glfwWindowShouldClose(window)) // Køre så længe glfw vinduet ikke har fået besked på at lukke (f.eks. tryk på X knappen)
	{
		gw->GameLoop();


	}
	glfwTerminate(); //Lukker evt. åbnede vinduer og frigiver resurse brugt her til
	return 0;
}