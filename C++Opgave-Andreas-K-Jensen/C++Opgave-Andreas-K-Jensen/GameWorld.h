#ifndef GAMEWORLD_H
#define GAMEWORLD_H



#include <GLFW\glfw3.h>
#include "GameObject.h"
#include <vector>
#include "Collider.h"

class Collider; //Defining the class, so the two classes can refer to each other (collider needs Gameworld Instance)

class GameWorld
{
private:
	//(vector fordi jeg gerne ønsker at kunne fjerne et specefikt element. Jeg ved ikke hvor mange spil objekter,
	//så array er ikke muligt) - note: vector bruger dog meget energi på at resize sig selv, hver gang et element tilføkes.

	std::vector<GameObject*> gameObjects; //Containter of all gameobjects 	
	std::vector<Collider*> colliders;

	GameWorld(); //private because Singleton
	~GameWorld(); //destructor - deletes all gameobject ptrs and sets them too null 

	void GameLogic(); //update all the logic of the game (and all its objects)
	void Render(); //draws the whole game
	GLFWwindow * windowPtr;

public:


	void GameLoop(); //calls update and render in a loop
	static GameWorld& GetInstanceRef(); //returns a reference of the static singleton instance
	static GLFWwindow& GetWindow(); //returns a reference of the game window
	std::vector<Collider*>& GetColliders();


};

#endif // !GAMEWORLD_H
