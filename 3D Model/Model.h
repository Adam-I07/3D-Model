#pragma once
#include "Polygon3D.h"
#include "Vertex.h"
#include "Matrix.h"
#include <vector>
#include "Vector3D.h"
#include "Camera.h"
#include <algorithm>
#include "DirectionalLighting.h"
#include "AmbientLighting.h"
#include "PointLighting.h"

class Model
{
public:
	Model();
	~Model();


	const std::vector<Vertex>& GetVertices();
	const std::vector<Vertex>& GetUpdatedVerices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	void ApplyTransformToLocalVertices(const Matrix& transform);
	void ApplyTransformToTransformedVertices(const Matrix& transform);
	Polygon3D GetPolygon(int index);
	void ApplyDehmogonisedVertice();
	void CalculateBackfaces( Camera _camera );
	void Sort(void);
	static bool ascendingSort(const Polygon3D& lhs, const Polygon3D& rhs);
	void CalculateLightingDirectional(vector<DirectionalLighting> directionalLighting);
	float Clamp(float num);
	void CalculateLightingAmbient(AmbientLighting ambientLighting);
	void CalculateLightingPoint(vector<PointLighting> pointLighting);

private:
	std::vector<Polygon3D> _polygons;
	std::vector<Vertex> _vertices;
	std::vector<Vertex> _updatedVertice;
	Vector3D _normalVector;
	Vector3D _vector3D;
	Polygon3D _polygon3D;

	//Directional Lighting
	float _kdRed;
	float _kdGreen;
	float _kdBlue;

	//Ambient Lighting
	float _kaRed;
	float _kaGreen;
	float _kaBlue;

	//Spot lighting
	float _ksRed;
	float _ksGreen;
	float _ksBlue;

	DirectionalLighting _directionalLighting;
	AmbientLighting _ambientLighting;
};

