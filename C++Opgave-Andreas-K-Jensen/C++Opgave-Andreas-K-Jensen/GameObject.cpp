#include "GameObject.h"


GameObject::GameObject() : GameObject(0, 0, 0)
{
}

GameObject::GameObject(float _x, float _y, float _z)

{
	x = _x;
	y = _y;
	z = _z;
	sprite = SOIL_load_OGL_texture("test.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	glBindTexture(GL_TEXTURE_2D, sprite); //Binder teksturen (dvs. indlæser den i GPU hukommelsen)


	direction = 1;
}


GameObject::~GameObject()
{
}

void GameObject::Render()
{
	glPushMatrix(); //Lægger en matrise på stakken, således kun denne manipuleres
	glTranslatef(x, y, z);
	glBindTexture(GL_TEXTURE_2D, sprite); //Binder teksturen (Anvender til ved rendering af vertices)
	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
	glPopMatrix(); // Fjerner matrisen på stakken (dvs. nulstiller til udgangspunkt)
}

void GameObject::Update()
{
	x += direction * 0.001;

}
