#pragma once
#include "Vertex.h"
class AmbientLighting
{
public:
	AmbientLighting();
	AmbientLighting(float redIntensity, float greenIntensity, float blueIntensity);
	
	float GetRedIntensity() const;
	void SetRedIntensity(const float RedIntensity);
	float GetBlueIntensity() const;
	void SetBlueIntensity(const float BlueIntensity);
	float GetGreenIntensity() const;
	void SetGreenIntensity(const float GreenIntensity);


private:
	float _redIntensity;
	float _greenIntensity;
	float _blueIntensity;
};

