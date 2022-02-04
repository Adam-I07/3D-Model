#include "Model.h"

Model::Model()
{
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
		Vertex v0, v1, v2;
		v0 = _updatedVertice.at(_polygons.at(i).GetIndex(0));
		v1 = _updatedVertice.at(_polygons.at(i).GetIndex(1));
		v2 = _updatedVertice.at(_polygons.at(i).GetIndex(2));
		Vector3D vectorA = v0 - v1;
		Vector3D vectorB = v0 - v2;
		vectorA.normalise();
		vectorB.normalise();
		//Vector3D normalVector = vectorB - vectorA;
		_normalVector = _normalVector.CrossProduct(vectorB, vectorA);
		Vector3D eyeVector = _updatedVertice.at(_polygons.at(i).GetIndex(0)) - _camera.getCameraPosition();
		float dotProduct = _normalVector.DotProduct(_normalVector, eyeVector);
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
	float totalR;
	float totalG;
	float totalB;
	float tempR;
	float tempG;
	float tempB;

	for (int i = 0; i < GetPolygonCount(); i++)
	{
		COLORREF tempStore = _polygons.at(i).GetFinalColor();
		totalR = GetRValue(tempStore);
		totalG = GetGValue(tempStore);
		totalB = GetBValue(tempStore);
		for (int j = 0; j < directionalLighting.size(); j++)
		{
			
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

			tempR = tempR * dotProduct;
			tempG = tempG * dotProduct;
			tempB = tempB * dotProduct;

			totalR = totalR + tempR;
			totalG = totalG + tempG;
			totalB = totalB + tempB;

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
		float totalR = 0.0f;
		float totalG = 0.0f;
		float totalB = 0.0f;
		float tempR;
		float tempG;
		float tempB;


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

/*void Model::CalculateLightingPoint(vector<PointLighting> pointLighting)
{
	float totalR;
	float totalG;
	float totalB;
	float tempR;
	float tempG;
	float tempB;

	for (int i = 0; i < GetPolygonCount(); i++)
	{
		COLORREF tempStore = _polygons.at(i).GetFinalColor();
		totalR = GetRValue(tempStore);
		totalG = GetGValue(tempStore);
		totalB = GetBValue(tempStore);
		for (int j = 0; j < pointLighting.size(); j++)
		{
			float a = 0.0f;
			float b = 1.0f;
			float c = 0.0f;

			Vector3D lightSource = pointLighting.at(j).GetLightSource();
			float firstVertex = float(_polygons.at(j).GetIndex(0));
			//float vector = firstVertex - lightSource;


		}
	}
	
}*/

