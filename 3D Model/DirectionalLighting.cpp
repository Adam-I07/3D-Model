#include "DirectionalLighting.h"

//This class creates variables that will get the intensity and lighting values that are assigned in the rasteriser and store them here ready for use
DirectionalLighting::DirectionalLighting()
{
	_redIntensity = 0.0f;
	_blueIntensity = 0.0f;
	_greenIntensity = 0.0f;
	_lightSource = { 0.0f, 0.0f, 0.0f};
}

DirectionalLighting::DirectionalLighting(float redIntensity, float greenIntensity, float blueIntensity, Vector3D lightSource)
{
	_redIntensity = redIntensity;
	_greenIntensity = greenIntensity;
	_blueIntensity = blueIntensity;
	_lightSource = lightSource;
}

float DirectionalLighting::GetRedIntensity() const
{
	return _redIntensity;
}

void DirectionalLighting::SetRedIntensity(const float RedIntensity)
{
	_redIntensity = RedIntensity;
}

float DirectionalLighting::GetBlueIntensity() const
{
	return _blueIntensity;
}

void DirectionalLighting::SetBlueIntensity(const float BlueIntensity)
{
	_blueIntensity = BlueIntensity;
}

float DirectionalLighting::GetGreenIntensity() const
{
	return _greenIntensity;
}

void DirectionalLighting::SetGreenIntensity(const float GreenIntensity)
{
	_greenIntensity = GreenIntensity;
}

Vector3D DirectionalLighting::GetLightSource() const
{
	return _lightSource;
}

void DirectionalLighting::SetLightSource(const Vector3D lightSource)
{
	_lightSource = lightSource;
}
