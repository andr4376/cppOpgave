#ifndef GAMEWORLD_H
#define GAMEWORLD_H



#include <GLFW\glfw3.h>
#include "GameObject.h"
#include <vector>


class GameWorld
{
private:
	std::vector<GameObject*> gameObjects;

	GameWorld();
	~GameWorld();

	void GameLogic();
	void Render();
	GLFWwindow * window;

public:

	void GameLoop();
	static GameWorld* GetInstance();
	static GLFWwindow& GetWindow();



};

#endif // !GAMEWORLD_H
