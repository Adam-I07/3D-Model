#include "Model.h"

Model::Model()
{
	//sets base values for private variables
	_ksRed = 1.0f;
	_ksGreen = 1.0f;
	_ksBlue = 1.0f;
	_kdRed = 1.0f;
	_kdGreen = 1.0f;
	_kdBlue = 1.0f;
	_kaRed = 1.0f;
	_kaGreen = 1.2f;
	_kaBlue = 1.3f;

	
}

Model::~Model()
{

}

const std::vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}

const std::vector<Vertex>& Model::GetUpdatedVerices()
{
	return _updatedVertice;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

void Model::AddVertex(float x, float y, float z)
{
	Vertex vertexCollection = { float(x), float(y), float(z), 1 };
	_vertices.push_back(vertexCollection);
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	Polygon3D polygonCollection = { i0, i1, i2 };
	_polygons.push_back(polygonCollection);
}


void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{
	_updatedVertice.clear();
	for (int i = 0; i < GetVertexCount(); i++)
	{
		
		Vertex transformation = transform * _vertices.at(i);
		_updatedVertice.push_back(transformation);
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (int i = 0; i < GetVertexCount(); i++)
	{
		_updatedVertice.at(i) = transform * _updatedVertice.at(i);
	}
}

Polygon3D Model::GetPolygon(int index)
{
	return _polygons.at(index);
}

void Model::ApplyDehmogonisedVertice()
{
	for (int i = 0; i < GetVertexCount(); i++)
	{
		_updatedVertice.at(i).dehmogonise();
	}
}


void Model::CalculateBackfaces(Camera _camera)
{
	for (int i = 0; i < GetPolygonCount(); i++)
	{
		//Gets the 3 vertices
		Vertex v0, v1, v2;
		v0 = _updatedVertice.at(_polygons.at(i).GetIndex(0));
		v1 = _updatedVertice.at(_polygons.at(i).GetIndex(1));
		v2 = _updatedVertice.at(_polygons.at(i).GetIndex(2));
		Vector3D vectorA = v0 - v1;
		Vector3D vectorB = v0 - v2;
		//normalises the two values above
		vectorA.normalise();
		vectorB.normalise();
		_normalVector = _normalVector.CrossProduct(vectorB, vectorA);
		Vector3D eyeVector = _updatedVertice.at(_polygons.at(i).GetIndex(0)) - _camera.getCameraPosition();
		float dotProduct = _normalVector.DotProduct(_normalVector, eyeVector);
		//if the worked out dot product is higher than 1 it will set the polygon to be culled else it will set it as false and then stores the outcome
		if (dotProduct < 0)
		{
			_polygons.at(i).SetPolygonCulled(true);
		}
		else
		{
			_polygons.at(i).SetPolygonCulled(false);
		}
		_polygons.at(i).setNormalVector(_normalVector);
	}
}

void Model::Sort(void)
{
	for (int i = 0; i < GetPolygonCount(); i++)
	{
		Vertex v0, v1, v2;
		v0 = _updatedVertice.at(_polygons.at(i).GetIndex(0));
		v1 = _updatedVertice.at(_polygons.at(i).GetIndex(1));
		v2 = _updatedVertice.at(_polygons.at(i).GetIndex(2));
		float zAverage = (v0.GetZ() + v1.GetZ() + v2.GetZ()) / 3.0f;
		_polygons.at(i).SetPolygonZ(zAverage);

	}
	std::sort(_polygons.begin(), _polygons.end(), ascendingSort);
}

bool Model::ascendingSort(const Polygon3D& lhs, const Polygon3D& rhs)
{
	
	return lhs.GetPolygonZ() > rhs.GetPolygonZ();
}

void Model::CalculateLightingDirectional(vector<DirectionalLighting> directionalLighting)
{
	//temporary variables to be used in the class
	float totalR;
	float totalG;
	float totalB;
	float tempR;
	float tempG;
	float tempB;

	for (int i = 0; i < GetPolygonCount(); i++)
	{
		//get the current rgb value that have been stored and assigns them to total rgb
		COLORREF tempStore = _polygons.at(i).GetFinalColor();
		totalR = GetRValue(tempStore);
		totalG = GetGValue(tempStore);
		totalB = GetBValue(tempStore);
		for (int j = 0; j < directionalLighting.size(); j++)
		{
			//gets the intensity values stored in the class
			tempR = directionalLighting.at(j).GetRedIntensity() ;
			tempG = directionalLighting.at(j).GetGreenIntensity() ;
			tempB = directionalLighting.at(j).GetBlueIntensity();

			tempR = tempR * _kdRed;
			tempG = tempG * _kdGreen;
			tempB = tempB * _kdBlue;

			Vector3D normalVector = directionalLighting.at(j).GetLightSource();
			normalVector.normalise();
			Vector3D normaliseVector = _polygons.at(i).getNormalVector();
			normaliseVector.normalise();
			float dotProduct = _normalVector.DotProduct(normalVector, normaliseVector);
			//if the dot product is higher than zero it will get the values and multiply them and add it then clamp and store them else it will clamp and store.
			if (dotProduct > 0)
			{
				tempR = tempR * dotProduct;
				tempG = tempG * dotProduct;
				tempB = tempB * dotProduct;

				totalR = totalR + tempR;
				totalG = totalG + tempG;
				totalB = totalB + tempB;
			}

		}
		totalR = Clamp(totalR);
		totalG = Clamp(totalG);
		totalB = Clamp(totalB);
		totalR = roundf(totalR);
		totalG = roundf(totalG);
		totalB = roundf(totalB);
		_polygons.at(i).SetFinalColor(RGB(totalR, totalG, totalB));
	}
}

//The clamp functions gets numbers and will check if they are lower than 0 it will clamp the value at 0 or higher than 250 will clamp it at 250 else it will return the number
float Model::Clamp(float num)
{
	float highNum = 250.0f;
	float lowNum = 0.0f;
	float ans = 0.0f;
	if (highNum < num)
	{
		ans = highNum;
	}
	else if (num < lowNum)
	{
		ans = lowNum;
	}
	else
	{
		ans = num;
	}
	return ans;
}

void Model::CalculateLightingAmbient(AmbientLighting ambientLighting)
{
	for (int i = 0; i < GetPolygonCount(); i++)
	{
		//temporary variables to be used in the class
		float totalR = 0.0f;
		float totalG = 0.0f;
		float totalB = 0.0f;
		float tempR;
		float tempG;
		float tempB;

		//gets the intensity values stored in the class
		tempR = ambientLighting.GetRedIntensity();
		tempG = ambientLighting.GetGreenIntensity();
		tempB = ambientLighting.GetBlueIntensity();


		tempR = tempR * _kdRed;
		tempG = tempG * _kdGreen;
		tempB = tempB * _kdBlue;

		totalR = totalR + tempR;
		totalG = totalG + tempG;
		totalB = totalB + tempB;

		totalR = Clamp(totalR);
		totalG = Clamp(totalG);
		totalB = Clamp(totalB);
		totalR = roundf(totalR);
		totalG = roundf(totalG);
		totalB = roundf(totalB);
		_polygons.at(i).SetFinalColor(RGB(totalR, totalG, totalB));

	}
}

void Model::CalculateLightingPoint(vector<PointLighting> pointLighting)
{
	//temporary variables to be used in the class
	float totalR;
	float totalG;
	float totalB;
	float tempR = 0.0f;
	float tempG = 0.0f;
	float tempB = 0.0f;

	for (int i = 0; i < GetPolygonCount(); i++)
	{
		//get the current rgb value that have been stored and assigns them to total rgb
		COLORREF tempStore = _polygons.at(i).GetFinalColor();
		totalR = GetRValue(tempStore);
		totalG = GetGValue(tempStore);
		totalB = GetBValue(tempStore);
		for (int j = 0; j < pointLighting.size(); j++)
		{
			//gets the intensity values stored in the class
			tempR = pointLighting.at(j).GetRedIntensity();
			tempG = pointLighting.at(j).GetGreenIntensity();
			tempB = pointLighting.at(j).GetBlueIntensity();

			tempR = tempR * _ksRed;
			tempG = tempG * _ksGreen;
			tempB = tempB * _ksBlue;

			Vertex firstVertex = GetUpdatedVerices()[GetPolygon(i).GetIndex(0)];
			Vector3D vectToLight = { (firstVertex.GetX() - pointLighting.at(j).GetLightSource().GetX()),
			(firstVertex.GetY() - pointLighting.at(j).GetLightSource().GetY()),
			(firstVertex.GetZ() - pointLighting.at(j).GetLightSource().GetZ()) };


			float distance = sqrtf((vectToLight.GetX() * vectToLight.GetX()) + (vectToLight.GetY() * vectToLight.GetY()) + (vectToLight.GetZ() * vectToLight.GetZ()));
			vectToLight.normalise();

			Vector3D normaliseVector = _polygons.at(i).getNormalVector();
			normaliseVector.normalise();
			float dotProduct = _normalVector.DotProduct(vectToLight, normaliseVector);

			float attenuation = (1 / (pointLighting.at(j).GetACoefficient() + (pointLighting.at(j).GetBCoefficient() * distance) + (pointLighting.at(j).GetCCoefficient() * (distance * distance))));
			//if the dot product is higher than zero it will get the values and multiply them and add it then clamp and store them else it will clamp and store.
			if (dotProduct > 0)
			{
				tempR = tempR *  dotProduct *attenuation * 100;
				tempG = tempG * dotProduct * attenuation * 100;
				tempB = tempB * dotProduct * attenuation * 100;

				totalR = totalR + tempR;
				totalG = totalG + tempG;
				totalB = totalB + tempB;
			}

			

		}
		totalR = Clamp(totalR);
		totalG = Clamp(totalG);
		totalB = Clamp(totalB);
		totalR = roundf(totalR);
		totalG = roundf(totalG);
		totalB = roundf(totalB);
		_polygons.at(i).SetFinalColor(RGB(totalR, totalG, totalB));
	}
}

