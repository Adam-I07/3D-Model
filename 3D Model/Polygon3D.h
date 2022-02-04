#pragma once
#include "Framework.h"
#include "Vector3D.h"
#include <vector>
class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);

	int GetIndex(int index) const;
	Polygon3D& operator= (const Polygon3D& rhs);

	bool GetPolygonCulled() const;
	void SetPolygonCulled(const bool polygonCulled);

	float GetPolygonZ() const;
	void SetPolygonZ(const float polygonZ);
	
	Vector3D getNormalVector() const;
	void setNormalVector(const Vector3D normalVector);

	COLORREF GetFinalColor() const;
	void SetFinalColor(const COLORREF finalColor);



private:
	Vector3D _normalVectorStore;
	int _indices[3];
	bool _polygonCulled;
	float _polygonZ;
	COLORREF _finalColorStore;
};

