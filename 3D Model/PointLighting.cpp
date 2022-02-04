#include "PointLighting.h"

//This class creates variables that will get the intensity, coefficient and lighting values that are assigned in the rasteriser and store them here ready for use
PointLighting::PointLighting()
{
	_redIntensity = 0.0f;
	_greenIntensity = 0.0f;
	_blueIntensity = 0.0f;
	_aCoefficient = 0.0f;
	_bCoefficient = 0.0f;
	_cCoefficient = 0.0f;
	_lightSource = { 0.0f, 0.0f, 0.0f, 1.0f };
}

PointLighting::PointLighting(float redIntensity, float greenIntensity, float blueIntensity, float aCoefficient, float bCoefficient, float cCoefficient, Vertex lightSource)
{

	_redIntensity = redIntensity;
	_greenIntensity = greenIntensity;
	_blueIntensity = blueIntensity;
	_aCoefficient = aCoefficient ;
	_bCoefficient = bCoefficient;
	_cCoefficient = cCoefficient;
	_lightSource = lightSource;
}

float PointLighting::GetACoefficient() const
{
	return _aCoefficient;
}

void PointLighting::SetACoefficient(const float ACoefficient)
{
	_aCoefficient = ACoefficient;
}

float PointLighting::GetBCoefficient() const
{
	return _bCoefficient;
}

void PointLighting::SetBCoefficient(const float BCoefficient)
{
	_bCoefficient = BCoefficient;
}

float PointLighting::GetCCoefficient() const
{
	return _cCoefficient;
}

void PointLighting::SetCCoefficient(const float CCoefficient)
{
	_cCoefficient = CCoefficient;
}



Vertex PointLighting::GetLightSource() const
{
	return _lightSource;
}

void PointLighting::SetLightSource(const Vertex lightSource)
{
	_lightSource = lightSource;
}

float PointLighting::GetRedIntensity() const
{
	return _redIntensity;
}

void PointLighting::SetRedIntensity(const float RedIntensity)
{
	_redIntensity = RedIntensity;
}

float PointLighting::GetBlueIntensity() const
{
	return _blueIntensity;
}

void PointLighting::SetBlueIntensity(const float BlueIntensity)
{
	_blueIntensity = BlueIntensity;
}

float PointLighting::GetGreenIntensity() const
{
	return _greenIntensity;
}

void PointLighting::SetGreenIntensity(const float GreenIntensity)
{
	_greenIntensity = GreenIntensity;
}

