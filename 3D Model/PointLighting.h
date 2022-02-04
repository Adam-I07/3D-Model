#pragma once
#include "Vertex.h"
class PointLighting
{
public:
	PointLighting();
	PointLighting(float redIntensity, float greenIntensity, float blueIntensity, float aCoefficient, float bCoefficient, float cCoefficient, Vertex lightSource);

	float GetACoefficient() const;
	void SetACoefficient(const float ACoefficient);
	float GetBCoefficient() const;
	void SetBCoefficient(const float BCoefficient);
	float GetCCoefficient() const;
	void SetCCoefficient(const float CCoefficient);
	Vertex GetLightSource() const;
	void SetLightSource(const Vertex lightSource);
	float GetRedIntensity() const;
	void SetRedIntensity(const float RedIntensity);
	float GetBlueIntensity() const;
	void SetBlueIntensity(const float BlueIntensity);
	float GetGreenIntensity() const;
	void SetGreenIntensity(const float GreenIntensity);


private:
	float _aCoefficient;
	float _bCoefficient;
	float _cCoefficient;
	float _redIntensity;
	float _greenIntensity;
	float _blueIntensity;
	Vertex _lightSource;
};

