#pragma once
#include "Vector3D.h"

class DirectionalLighting
{
public:
	DirectionalLighting();
	DirectionalLighting(float redItensity, float greenIntensity, float blueIntensity, Vector3D lightSource);

	float GetRedIntensity() const;
	void SetRedIntensity(const float RedIntensity);
	float GetBlueIntensity() const;
	void SetBlueIntensity(const float BlueIntensity);
	float GetGreenIntensity() const;
	void SetGreenIntensity(const float GreenIntensity);
	Vector3D GetLightSource() const;
	void SetLightSource(const Vector3D lightSource);


private:
	float _redIntensity;
	float _greenIntensity;
	float _blueIntensity;
	Vector3D _lightSource;
	

};

