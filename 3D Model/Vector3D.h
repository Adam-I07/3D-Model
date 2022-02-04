#pragma once
#include <math.h>
class Vector3D
{
public:
	Vector3D();
	Vector3D(float x, float y, float z); 
	Vector3D(const Vector3D& other);

	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);

	static float DotProduct(Vector3D vectorU, Vector3D vectorV);
	static Vector3D CrossProduct(Vector3D vectorU, Vector3D vectorV);
	const Vector3D operator- (const Vector3D& rhs) const;
	void normalise();



private:
	float _x;
	float _y;
	float _z;
};

