#include "Matrix.h"
#include "Vertex.h"
#pragma once
class Camera
{
public:
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position); 

	Matrix getMatrixCamera();
	void createViewMatrix();
	Vertex getCameraPosition();
	float getXRotation() const;
	void setXRotation(const float xRotation);
	float getYRotation() const;
	void setYRotation(const float yRotation);
	float getZRotation() const;
	void setZRotation(const float zRotation);

private:
	float _xRotation;
	float _yRotation;
	float _zRotation;
	Vertex _cameraPosition;
	Matrix _viewMatrix;
};

