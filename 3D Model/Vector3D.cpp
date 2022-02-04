#include "Vector3D.h"

//This class creates variables for the user to add values and store them
Vector3D::Vector3D()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector3D::Vector3D(const Vector3D& other)
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
}

float Vector3D::GetX() const
{
	return _x;
}

void Vector3D::SetX(const float x)
{
	_x = x;
}

float Vector3D::GetY() const
{
	return _y;
}

void Vector3D::SetY(const float y)
{
	_y = y;
}

float Vector3D::GetZ() const
{
	return _z;
}

void Vector3D::SetZ(const float z)
{
	_z = z;
}

//This method works out the DotProduct
float Vector3D::DotProduct(Vector3D vectorU, Vector3D vectorV)
{
	float product = (vectorU.GetX() * vectorV.GetX()) + (vectorU.GetY() * vectorV.GetY()) + (vectorU.GetZ() * vectorV.GetZ());
	return product;
}

//This method works out the cross product
Vector3D Vector3D::CrossProduct(Vector3D vectorU, Vector3D vectorV)
{
	Vector3D crossProduct = { (vectorU.GetY() * vectorV.GetZ()) - (vectorU.GetZ() * vectorV.GetY()),
				(vectorU.GetZ() * vectorV.GetX()) - (vectorU.GetX() * vectorV.GetZ()),
		        (vectorU.GetX() * vectorV.GetY()) - (vectorU.GetY() * vectorV.GetX()) };
	return crossProduct;
}

//This operator allows the user to use the minus operator
const Vector3D Vector3D::operator-(const Vector3D& rhs) const
{
	return Vector3D(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
	
}




//This method normalises values when ever called
void Vector3D::normalise()
{
	float xSquare = _x * _x;
	float ySquare = _y * _y;
	float zSquare = _z * _z;
	float ans = xSquare + ySquare + zSquare;
	float length = sqrtf(ans); 
	_x = _x / length;
	_y = _y / length;
	_z = _z / length;
}