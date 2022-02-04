#include "AmbientLighting.h"

//This class creates variables that will get the intensity values that are assigned in the rasteriser and store them here ready for use
AmbientLighting::AmbientLighting()
{
	_redIntensity = 0.0f;
	_blueIntensity = 150.0f;
	_greenIntensity = 0.0f;
}

AmbientLighting::AmbientLighting(float redIntensity, float greenIntensity, float blueIntensity)
{
	_redIntensity = redIntensity;
	_greenIntensity = greenIntensity;
	_blueIntensity = blueIntensity;
}
float AmbientLighting::GetRedIntensity() const
{
	return _redIntensity;
}

void AmbientLighting::SetRedIntensity(const float RedIntensity)
{
	_redIntensity = RedIntensity;
}

float AmbientLighting::GetBlueIntensity() const
{
	return _blueIntensity;
}

void AmbientLighting::SetBlueIntensity(const float BlueIntensity)
{
	_blueIntensity = BlueIntensity;
}

float AmbientLighting::GetGreenIntensity() const
{
	return _greenIntensity;
}

void AmbientLighting::SetGreenIntensity(const float GreenIntensity)
{
	_greenIntensity = GreenIntensity;
}


