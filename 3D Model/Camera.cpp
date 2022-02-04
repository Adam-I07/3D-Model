#include "Camera.h"
#include <math.h>

//This class gets the values assigned for the camera and stores them 
Camera::Camera()
{
	_xRotation = 0.0f;
	_yRotation = 0.0f;
	_zRotation = 0.0f;
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRotation = zRotation;
	_cameraPosition = position;
	createViewMatrix();
}

Matrix Camera::getMatrixCamera()
{
	return _viewMatrix;
}

//works out the viewing transformation
void Camera::createViewMatrix()
{
	Matrix xTranform = { 1, 0, 0, 0,
						 0, cosf(_xRotation), sinf(_xRotation), 0,
						 0, -sinf(_xRotation), cosf(_xRotation), 0,
						 0, 0, 0, 1 };

	Matrix yTransform = { cosf(_yRotation), 0, -sinf(_yRotation), 0,
						  0, 1, 0, 0,
						  sinf(_yRotation), 0, cosf(_yRotation), 0,
						  0, 0, 0, 1 };

	Matrix zTransform = { cosf(_zRotation), sinf(_zRotation), 0, 0,
						-sinf(_zRotation), cosf(_zRotation), 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1 };

	Matrix cameraPosition = { 1, 0, 0, -_cameraPosition.GetX(), 
							0, 1, 0, -_cameraPosition.GetY(), 
							0, 0, 1, -_cameraPosition.GetZ(), 
							0, 0, 0, 1 };

	_viewMatrix = xTranform * yTransform * zTransform * cameraPosition;
}

Vertex Camera::getCameraPosition()
{
	return _cameraPosition;
}

float Camera::getXRotation() const
{
	return _xRotation;
}

void Camera::setXRotation(const float xRotation)
{
	_xRotation = xRotation;
	createViewMatrix();
}

float Camera::getYRotation() const
{
	return _yRotation;
}

void Camera::setYRotation(const float yRotation)
{
	_yRotation = yRotation;
	createViewMatrix();

}

float Camera::getZRotation() const
{
	
	return _zRotation;
	
}

void Camera::setZRotation(const float zRotation)
{
	_zRotation = zRotation;
	createViewMatrix();
}
