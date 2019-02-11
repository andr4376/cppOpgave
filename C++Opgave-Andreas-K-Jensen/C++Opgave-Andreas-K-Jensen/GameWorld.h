#ifndef GAMEWORLD_H
#define GAMEWORLD_H



#include <GLFW\glfw3.h>
#include "GameObject.h"
#include <vector>


class GameWorld
{
private:
	std::vector<GameObject*> gameObjects; //Containter of all gameobjects 
	//(vector fordi jeg gerne ønsker at kunne fjerne et specefikt element. Jeg ved ikke hvor mange spil objekter,
	//så array er ikke muligt) - note: vector bruger dog meget energi på at resize sig selv, hver gang et element tilføkes.

	GameWorld(); //private because Singleton
	~GameWorld(); //destructor - deletes all gameobject ptrs and sets them too null 

	void GameLogic(); //update all the logic of the game (and all its objects)
	void Render(); //draws the whole game
	GLFWwindow * windowPtr;

public:

	void GameLoop(); //calls update and render in a loop
	static GameWorld& GetInstanceRef(); //returns a reference of the static singleton instance
	static GLFWwindow& GetWindow(); //returns a reference of the game window



};

#endif // !GAMEWORLD_H
