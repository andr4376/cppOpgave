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

GameObject::GameObject() : GameObject(Vector2(), DEFAULT_OBJECT_SIZE, 0)
{
}

GameObject::GameObject(Vector2 _pos) : GameObject(_pos, DEFAULT_OBJECT_SIZE, 0)
{

}

//the constructor all other constructors end up in
GameObject::GameObject(Vector2 _pos, float _size) : GameObject(_pos, _size, 0)
{

}

//the constructor all other constructors end up in
GameObject::GameObject(Vector2 _pos, float _size, float _rotation)
{
	size = _size;
	position = _pos;

	if (sprite == NULL)
	{
		sprite = SOIL_load_OGL_texture(DUMMY_TEXTURE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	}

	entityType = BLANK;

	rotation = _rotation;

	glBindTexture(GL_TEXTURE_2D, sprite); //Binder teksturen (dvs. indlæser den i GPU hukommelsen)
}

GameObject::~GameObject()
{
}

//Made for small Increments
void GameObject::SetRotation(float newRotation)
{
	rotation = newRotation;

	if (rotation > 360)
	{
		rotation = 0;
	}

	if (rotation < 0)
	{
		rotation = 360;
	}

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
	glRotatef(rotation, 0, 0, 1); //Roter matricen gældende for efterfølgende vertices
	glBegin(GL_QUADS);
	// Front Face


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

void GameObject::OnCollisionStay(GameObject & goRef)
{
}

void GameObject::OnCollisionExit(GameObject & goRef)
{
}
