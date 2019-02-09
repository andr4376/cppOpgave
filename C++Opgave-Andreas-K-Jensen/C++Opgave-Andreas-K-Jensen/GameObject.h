#pragma once
#include <SOIL.h>
#include <GLFW\glfw3.h>
class GameObject
{
private:
	GLuint sprite;

	float x, y,z;
public:

	int direction;

	GameObject();
	GameObject(float _x, float _y, float _z);
	~GameObject();

	void Render();
	void Update();
};

