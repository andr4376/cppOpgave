#ifndef VECTOR_2
#define VECTOR_2

struct Vector2
{
	int x;
	int y;

	Vector2();
	Vector2(int _x, int _y);

	//Allows adding vectors together 
	Vector2 operator + (Vector2 otherVector); //operator overload

	~Vector2();

};

#endif // !VECTOR_2
