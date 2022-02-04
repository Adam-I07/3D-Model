#pragma once
#include "Framework.h"
#include "Model.h"
#include "MD2Loader.h"
#include "Model.h"
#include "Camera.h"
#include "DirectionalLighting.h"
#include "AmbientLighting.h"
#include "PointLighting.h"
#include "Vertex.h"
#include <algorithm>

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Render(const Bitmap& bitmap);
	void Update(const Bitmap& bitmap);
	void RotationY();
	void RotationX();
	void RotationZ();
	void Scale();
	void Translation();
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);
	void DrawWireFrame(const Bitmap& bitmap);
	void DrawSolidFlat(const Bitmap& bitmap);
	static bool sortVerticesAscendingByY(const Vertex& lhs, const Vertex& rhs);
	void MyDrawSolidFlat(const Bitmap& bitmap);
	void FillPolygonFlat(HDC& hdc, vector<Vertex>& points);
	void FillBottomFlatTriangle(const HDC& hdc, Vertex v1, Vertex v2, Vertex v3, COLORREF c1, COLORREF c2, COLORREF c3);
	void fillTopFlatTriangle(const HDC& hdc, Vertex v1, Vertex v2, Vertex v3, COLORREF c1, COLORREF c2, COLORREF c3);
	void DrawString(const Bitmap& bitmap, LPCTSTR text);



private:
	Vertex _vertex[4];
	int _translate;
	Model _model;
	Matrix _perspectiveMatrix;
	Matrix _screenViewMatrix;
	Matrix _currentModelTranformation;
	Vertex _cameraPosition;
	Camera _newCamera;
	Vertex  _lightingPosition;
	float _degreeTransformation = 1.0;
	Vector3D _vecLighting;
	DirectionalLighting _directionalLight;
	vector<DirectionalLighting> _directionalLightStore;
	AmbientLighting _ambientLighting;
	PointLighting _pointLighting;
	vector<PointLighting> _pointLightingStore;
	float count;
	float _scale;
};
