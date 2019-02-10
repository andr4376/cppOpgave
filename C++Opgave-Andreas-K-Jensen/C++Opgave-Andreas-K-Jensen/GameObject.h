#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SOIL.h>
#include <GLFW\glfw3.h>

//Removes Pointers. 
#define REMOVE_PTR(x) delete x; x = nullptr; // TODO: Find appropriate location. Research: Why is it globally accessible here, but not GameWorld?


class GameObject
{
private:
	GLuint sprite;

protected:
	float x, y, z;
public:


	GameObject();
	GameObject(float _x, float _y, float _z);
	~GameObject();

	virtual void Render();
	virtual void Update();
};

#endif // !GAMEOBJECT_H
