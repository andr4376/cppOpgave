#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Globals.h"
#include <SOIL.h>
#include <GLFW\glfw3.h>



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
