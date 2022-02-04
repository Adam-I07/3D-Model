#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	_polygonCulled = false;
	_polygonZ = 0.0f;
	_finalColorStore = RGB(0, 0, 0);
	_normalVectorStore = { 0.0f, 0.0f, 0.0f };
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_polygonCulled = false;
	_polygonZ = _polygonZ;
	_finalColorStore = _finalColorStore;
	_normalVectorStore = _normalVectorStore;
}

Polygon3D::~Polygon3D()
{
}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	_indices[0] = p.GetIndex(0);
	_indices[1] = p.GetIndex(1);
	_indices[2] = p.GetIndex(2);
	_polygonCulled = p.GetPolygonCulled();
	_polygonZ = p.GetPolygonZ();
	_finalColorStore = p.GetFinalColor();
	_normalVectorStore = p.getNormalVector();

}

int Polygon3D::GetIndex(int index) const
{
	return _indices[index];

}

Polygon3D& Polygon3D::operator=(const Polygon3D& rhs)
{
	if (this != &rhs)
	{
		_indices[0] = rhs.GetIndex(0);
		_indices[1] = rhs.GetIndex(1);
		_indices[2] = rhs.GetIndex(2);
		_polygonCulled = rhs._polygonCulled;
		_polygonZ = rhs._polygonZ;
		_finalColorStore = rhs._finalColorStore;
		_normalVectorStore = rhs._normalVectorStore;
	}
	return *this;
}

bool Polygon3D::GetPolygonCulled() const
{
	return _polygonCulled;
}

void Polygon3D::SetPolygonCulled(const bool polygonCulled)
{
	 _polygonCulled = polygonCulled;
}

float Polygon3D::GetPolygonZ() const
{
	return _polygonZ;
}

void Polygon3D::SetPolygonZ(const float polygonZ)
{
	_polygonZ = polygonZ;
}

Vector3D Polygon3D::getNormalVector() const
{
	return _normalVectorStore;
}

void Polygon3D::setNormalVector(const Vector3D normalVector)
{
	_normalVectorStore = normalVector;
}

COLORREF Polygon3D::GetFinalColor() const
{
	return _finalColorStore;
}

void Polygon3D::SetFinalColor(const COLORREF finalColor)
{
	_finalColorStore = finalColor;
}
