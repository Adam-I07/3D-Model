#pragma once
#include "Vector3D.h"
#include "Framework.h"
class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z, float w);
	Vertex(const Vertex& other);

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetW() const;
	void SetW(const float w);
	float GetZ() const;
	void SetZ(const float z);

	// Assignment operator
	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;

	const Vertex operator+ (const Vertex& rhs) const;
	//const Vertex operator- (const Vertex& other) const;
	const Vector3D operator- (const Vertex& rhs) const;

	COLORREF getVertexRGB() const;
	void setVertexRGB(const COLORREF VertexRGB);


	void dehmogonise();

private:
	float _x;
	float _y;
	float _w;
	float _z;
	COLORREF _VertexRGB;
};




