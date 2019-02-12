#include "GameObject.h"

#define DUMMY_TEXTURE "test.png"
Vector2 GameObject::GetPosition()
{
	return position;
}

ENTITY_TYPE GameObject::GetEntityType()
{
	return entityType;
}

GameObject::GameObject() : GameObject(Vector2())
{
}

GameObject::GameObject(Vector2 _pos) : GameObject(_pos, PLAYER_SIZE)
{

}

//the constructor all other constructors end up in
GameObject::GameObject(Vector2 _pos, float _size)
{
	size = _size;
	position = _pos;

	if (sprite == NULL)
	{
		sprite = SOIL_load_OGL_texture(DUMMY_TEXTURE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	}

	entityType = BLANK;

	glBindTexture(GL_TEXTURE_2D, sprite); //Binder teksturen (dvs. indlæser den i GPU hukommelsen)
}

GameObject::~GameObject()
{
}

float GameObject::GetSize()
{
	return size;
}

void GameObject::Render()
{
	glPushMatrix(); //Lægger en matrise på stakken, således kun denne manipuleres
	glTranslatef(position.x, position.y, 0);
	glBindTexture(GL_TEXTURE_2D, sprite); //Binder teksturen (Anvender til ved rendering af vertices)
	glBegin(GL_QUADS);
	// Front Face

	//TODO: Scale with actual object size and screen size
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.01f*size, -0.01f*size, 0); //bottom left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.01f*size, -0.01f*size, 0); //bottom right
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.01f*size, 0.01f*size, 0); //top right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.01f*size, 0.01f*size, 0); //top left
	glEnd();
	glPopMatrix(); // Fjerner matrisen på stakken (dvs. nulstiller til udgangspunkt)
}

void GameObject::Update()
{

}

void GameObject::OnCollisionEnter(GameObject & goRef)
{
	DEBUG_LOG("Gameobject collision enter");
	DEBUG_LOG(entityType);
}
