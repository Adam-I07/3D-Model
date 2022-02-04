#include "Vertex.h"

//Gets the values that are assigned to vertex by the user and stores them ready to use
Vertex::Vertex()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 0.0f;
	_VertexRGB = RGB( 0, 0, 0 );
}

Vertex::Vertex(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
	_VertexRGB = _VertexRGB;
}

Vertex::Vertex(const Vertex& other)
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
	_w = other.GetW();
	_VertexRGB = other.getVertexRGB();
}

float Vertex::GetX() const
{
	return _x;
}

void Vertex::SetX(const float x)
{
	_x = x;
}

float Vertex::GetY() const
{
	return _y;
}

void Vertex::SetY(const float y)
{
	_y = y;
}

float Vertex::GetW() const
{
	return _w;
}

void Vertex::SetW(const float w)
{
	_w = w;
}

float Vertex::GetZ() const
{
	return _z;
}

void Vertex::SetZ(const float z)
{
	_z = z;
}


Vertex& Vertex::operator=(const Vertex& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_w = rhs.GetW();
		_z = rhs.GetZ();
	}
	return *this;
}

// The const at the end of the declaraion for '==" indicates that this operation does not change
// any of the member variables in this class.

bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _w == rhs.GetW() &&  _z == rhs.GetZ());
}

// You can see three different uses of 'const' here:
//
// The first const indicates that the method changes the return value, but it is not moved in memory
// The second const indicates that the parameter is passed by reference, but it is not modified
// The third const indicates that the operator does not change any of the memory variables in the class.

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _w + rhs.GetW(), _z + rhs.GetZ());
}

/*const Vertex Vertex::operator-(const Vertex& other) const
{
	return Vertex(_x - other.GetX(), _y - other.GetY(), _w - other.GetW(), _z - other.GetZ());
}*/

const Vector3D Vertex::operator- (const Vertex& other) const
{
	return Vector3D(_x - other.GetX(), _y - other.GetY(), _z - other.GetZ());
}

void Vertex::setVertexRGB(const COLORREF VertexRGB)
{
	 _VertexRGB = VertexRGB;
}
COLORREF Vertex::getVertexRGB() const
{
	return _VertexRGB;
}

//Used to dehmogonise values
void Vertex::dehmogonise()
{
	_x = _x / _w;
	_y = _y / _w;
	_w = _w / _w;
	_z = _z / _w;
}


