#include "Rasteriser.h"

Rasteriser app;

//Loading the Md2 model and assigns all the private variables.
bool Rasteriser::Initialise()
{
	if (!MD2Loader::LoadModel("marvin.md2", _model,
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}
	count = 0;
	_cameraPosition = { 0, 0, -50, 0 };
	_newCamera = { 0 , 0, 0, _cameraPosition };
	_vecLighting = { 0.5f , -0.5f, 0.5f};
	_ambientLighting = { 0.0f,0.0f,80.0f};
	_directionalLight = { 200.0f,0.0f,0.0f, _vecLighting };
	_directionalLightStore.push_back(_directionalLight);
	_lightingPosition = Vertex{ 0,0,-50,1 };
	_pointLighting = PointLighting{ 0.0f, 85.0f, 0.0f, 0.0f, 1.0f, 0.0f,_lightingPosition };
	_pointLightingStore.push_back(_pointLighting);
	
	return true;
}

void Rasteriser::Render(const Bitmap& bitmap)
{
	bitmap.Clear(RGB(0, 0, 0));

	
	//Displays all the rotations, scaling, translation and the different stages of new features.
	if (count <= 200)
	{

		DrawString(bitmap, L"Scale");
		_model.ApplyTransformToLocalVertices(_currentModelTranformation);//World Transformation
		_model.ApplyTransformToTransformedVertices(_newCamera.getMatrixCamera());//Camera
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);//Perspective Transformation
		_model.ApplyDehmogonisedVertice();//dehmogonise vertices
		_model.ApplyTransformToTransformedVertices(_screenViewMatrix);//Screen Transformation
		DrawWireFrame(bitmap);

	}

	if (count >= 201 && count <= 900)
	{
		DrawString(bitmap, L"Rotation on X Axis");
		_model.ApplyTransformToLocalVertices(_currentModelTranformation);//World Transformation
		_model.ApplyTransformToTransformedVertices(_newCamera.getMatrixCamera());//Camera
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);//Perspective Transformation
		_model.ApplyDehmogonisedVertice();//dehmogonise vertices
		_model.ApplyTransformToTransformedVertices(_screenViewMatrix);//Screen Transformation
		DrawWireFrame(bitmap);
	}


	if (count >= 901 && count <= 1600)
	{
		DrawString(bitmap, L"Rotation on Y Axis");
		_model.ApplyTransformToLocalVertices(_currentModelTranformation);//World Transformation
		_model.ApplyTransformToTransformedVertices(_newCamera.getMatrixCamera());//Camera
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);//Perspective Transformation
		_model.ApplyDehmogonisedVertice();//dehmogonise vertices
		_model.ApplyTransformToTransformedVertices(_screenViewMatrix);//Screen Transformation
		DrawWireFrame(bitmap);
	}


	if (count >= 1601 && count <= 2300)
	{
		DrawString(bitmap,L"Rotation on Z Axis");
		_model.ApplyTransformToLocalVertices(_currentModelTranformation);//World Transformation
		_model.ApplyTransformToTransformedVertices(_newCamera.getMatrixCamera());//Camera
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);//Perspective Transformation
		_model.ApplyDehmogonisedVertice();//dehmogonise vertices
		_model.ApplyTransformToTransformedVertices(_screenViewMatrix);//Screen Transformation
		DrawWireFrame(bitmap);
	}


	if (count >= 2301 && count <= 2400)
	{
		DrawString(bitmap, L"Translation");
		_model.ApplyTransformToLocalVertices(_currentModelTranformation);//World Transformation
		_model.ApplyTransformToTransformedVertices(_newCamera.getMatrixCamera());//Camera
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);//Perspective Transformation
		_model.ApplyDehmogonisedVertice();//dehmogonise vertices
		_model.ApplyTransformToTransformedVertices(_screenViewMatrix);//Screen Transformation
		DrawWireFrame(bitmap);
	}
	if (count >= 2401 && count <= 3100)
	{
		DrawString(bitmap, L"Vectors and BackfaceCulling");
		_model.ApplyTransformToLocalVertices(_currentModelTranformation);//World Transformation
		_model.CalculateBackfaces(_newCamera);
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_newCamera.getMatrixCamera());//Camera
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);//Perspective Transformation
		_model.ApplyDehmogonisedVertice();//dehmogonise vertices
		_model.ApplyTransformToTransformedVertices(_screenViewMatrix);//Screen Transformation
		DrawWireFrame(bitmap);

	}
	if (count >= 3101 && count <= 3800)
	{
		DrawString(bitmap, L"Solid Shading");
		_model.ApplyTransformToLocalVertices(_currentModelTranformation);//World Transformation
		_model.CalculateBackfaces(_newCamera);
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_newCamera.getMatrixCamera());//Camera
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);//Perspective Transformation
		_model.ApplyDehmogonisedVertice();//dehmogonise vertices
		_model.ApplyTransformToTransformedVertices(_screenViewMatrix);//Screen Transformation
		DrawSolidFlat(bitmap);

	}
	if (count >= 3801 && count <= 4500)
	{
		DrawString(bitmap, L"Ambient Lighting");
		_model.ApplyTransformToLocalVertices(_currentModelTranformation);//World Transformation
		_model.CalculateBackfaces(_newCamera);
		_model.CalculateLightingAmbient(_ambientLighting);
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_newCamera.getMatrixCamera());//Camera
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);//Perspective Transformation
		_model.ApplyDehmogonisedVertice();//dehmogonise vertices
		_model.ApplyTransformToTransformedVertices(_screenViewMatrix);//Screen Transformation
		DrawSolidFlat(bitmap);

	}
	if (count >= 4501 && count <= 5200)
	{
		DrawString(bitmap, L"Ambient Lighting + Directional Lighting");
		_model.ApplyTransformToLocalVertices(_currentModelTranformation);//World Transformation
		_model.CalculateBackfaces(_newCamera);
		_model.CalculateLightingAmbient(_ambientLighting);
		_model.CalculateLightingDirectional(_directionalLightStore);
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_newCamera.getMatrixCamera());//Camera
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);//Perspective Transformation
		_model.ApplyDehmogonisedVertice();//dehmogonise vertices
		_model.ApplyTransformToTransformedVertices(_screenViewMatrix);//Screen Transformation
		DrawSolidFlat(bitmap);

	}
	if (count >= 5201 && count <= 5900)
	{
		DrawString(bitmap, L"Ambient, Directional + Point Lighting");
		_model.ApplyTransformToLocalVertices(_currentModelTranformation);//World Transformation
		_model.CalculateBackfaces(_newCamera);
		_model.CalculateLightingAmbient(_ambientLighting);
		_model.CalculateLightingDirectional(_directionalLightStore);
		_model.CalculateLightingPoint(_pointLightingStore);
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_newCamera.getMatrixCamera());//Camera
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);//Perspective Transformation
		_model.ApplyDehmogonisedVertice();//dehmogonise vertices
		_model.ApplyTransformToTransformedVertices(_screenViewMatrix);//Screen Transformation
		DrawSolidFlat(bitmap);

	}
	if (count >= 5901 && count <= 6600)
	{
		DrawString(bitmap, L"My Own rasterisation code");
		_model.ApplyTransformToLocalVertices(_currentModelTranformation);//World Transformation
		_model.CalculateBackfaces(_newCamera);
		_model.CalculateLightingAmbient(_ambientLighting);
		_model.CalculateLightingDirectional(_directionalLightStore);
		_model.CalculateLightingPoint(_pointLightingStore);
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_newCamera.getMatrixCamera());//Camera
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);//Perspective Transformation
		_model.ApplyDehmogonisedVertice();//dehmogonise vertices
		_model.ApplyTransformToTransformedVertices(_screenViewMatrix);//Screen Transformation
		MyDrawSolidFlat(bitmap);

	}
	count++;
}


//This method applys all the rotations for the model and created the perspective and screen matrixes.
void Rasteriser::Update(const Bitmap& bitmap)
{
	if (count <= 200)
	{
		
		Scale();
		
	}
	
	if (count >= 201 && count <= 900)
	{
		RotationX();
	}

	if (count >= 901 && count <= 1600)
	{
		RotationY();
	}

	if (count >= 1601 && count <= 2300)
	{
		RotationZ();
	}
	if (count >= 2301 && count <= 2400)
	{
		
		Translation();
	}
	if (count >= 2401 && count <= 6600)
	{
		
		RotationY();
	}
	count++;

	GeneratePerspectiveMatrix(1, float(bitmap.GetWidth()) / float(bitmap.GetHeight()));
	GenerateViewMatrix(1, bitmap.GetWidth(), bitmap.GetHeight());
}

//Rotates the model on the X axis
void Rasteriser::RotationX()
{
	_degreeTransformation += 1.0f;
	float rotation = _degreeTransformation * 3.14159f / 180.0f;
	_currentModelTranformation = { 1, 0, 0, 0,
						0, float(cos(rotation)), float(-sin(rotation)), 0,
						0, float(sin(rotation)), float(cos(rotation)), 0,
						0, 0, 0, 1 };
}

//Rotates the model on the Y axis
void Rasteriser::RotationY()
{
	_degreeTransformation += 1.0f;
	float rotation = _degreeTransformation * 3.14159f / 180.0f;
	_currentModelTranformation = { float(cos(rotation)), 0, float(sin(rotation)), 0,
						0, 1, 0, 0,
						float(-sin(rotation)), 0, float(cos(rotation)), 0,
						0, 0, 0, 1 };
}

//Rotates the model on the Z axis
void Rasteriser::RotationZ()
{
	_degreeTransformation += 1.0f;
	float rotation = _degreeTransformation * 3.14159f / 180.0f;
	_currentModelTranformation = { float(cos(rotation)), float(-sin(rotation)), 0, 0,
						float(sin(rotation)), float(cos(rotation)), 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1 };
}

//Scales the model 
void Rasteriser::Scale()
{
	_scale +=  0.01f;
	_currentModelTranformation = { float(_scale) ,0 ,0,0,
					0, float(_scale), 0, 0,
					0,0,float(_scale),0,
					0,0,0,1 };
}

//Translates the model
void Rasteriser::Translation()
{
	_translate += 1;
	Vertex moveObj = Vertex(float(_translate), 0, 0, 1);
	_currentModelTranformation = { 1.0f,0.0f, 0.0f, -moveObj.GetX(),
					0.0f,1.0f,0.0f,-moveObj.GetY(),
					0.0f,0.0f,1.0f,-moveObj.GetZ(),
					0.0f,0.0f,0.0f,1.0f };
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	_perspectiveMatrix = { d / aspectRatio, 0.0f, 0.0f, 0.0f,
						0.0f, d, 0.0f, 0.0f,
						0.0f, 0.0f, d, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f };
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	_screenViewMatrix = { width / 2.0f, 0.0f, 0.0f, width / 2.0f,
							0.0f, -height / 2.0f, 0.0f, height / 2.0f,
							0.0f, 0.0f, d / 2.0f, d / 2.0f,
							0.0f, 0.0f, 0.0f, 1.0f };
}

//Draws a basic wireframe of the md2 Model
void Rasteriser::DrawWireFrame(const Bitmap& bitmap)
{
	HDC hdc = bitmap.GetDC();
	HPEN hPenOld;
	HPEN hLinePen;
	COLORREF qLineColor;
	qLineColor = RGB(0, 0, 255);
	hLinePen = CreatePen(PS_SOLID, 1, qLineColor);
	hPenOld = (HPEN)SelectObject(hdc, hLinePen);

	for (int i = 0; i < _model.GetPolygonCount(); i++)
	{
		if (!_model.GetPolygon(i).GetPolygonCulled())
		{
			Vertex firstVertex = _model.GetUpdatedVerices()[_model.GetPolygon(i).GetIndex(0)];
			Vertex secondVertex = _model.GetUpdatedVerices()[_model.GetPolygon(i).GetIndex(1)];
			Vertex thirdVertex = _model.GetUpdatedVerices()[_model.GetPolygon(i).GetIndex(2)];
			MoveToEx(hdc, int(firstVertex.GetX()), int(firstVertex.GetY()), NULL);
			LineTo(hdc, int(secondVertex.GetX()), int(secondVertex.GetY()));
			LineTo(hdc, int(thirdVertex.GetX()), int(thirdVertex.GetY()));
			LineTo(hdc, int(firstVertex.GetX()), int(firstVertex.GetY()));
		}

	}
	DeleteObject(hPenOld);
	DeleteObject(hLinePen);

}

//A new method to draw the model and solid fill the model(colour it)
void Rasteriser::DrawSolidFlat(const Bitmap& bitmap)
{
	HDC hdc = bitmap.GetDC();
	HPEN hPenOld;
	HPEN hLinePen;
	HBRUSH hBrushNew;
	HBRUSH hBrushOld;
	COLORREF qLineColor;
	
	

	for (int i = 0; i < _model.GetPolygonCount(); i++)
	{
		qLineColor = _model.GetPolygon(i).GetFinalColor();
		//RGB(0, 0, 0); 
		hLinePen = CreatePen(PS_SOLID, 4, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);
		hBrushNew = CreateSolidBrush(_model.GetPolygon(i).GetFinalColor());
		hBrushOld = (HBRUSH)SelectObject(hdc, hBrushNew);
		if (!_model.GetPolygon(i).GetPolygonCulled())
		{
			Vertex firstVertex = _model.GetUpdatedVerices()[_model.GetPolygon(i).GetIndex(0)];
			Vertex secondVertex = _model.GetUpdatedVerices()[_model.GetPolygon(i).GetIndex(1)];
			Vertex thirdVertex = _model.GetUpdatedVerices()[_model.GetPolygon(i).GetIndex(2)];
			POINT point1 = { long(firstVertex.GetX()), long(firstVertex.GetY()) };
			POINT point2 = { long(secondVertex.GetX()), long(secondVertex.GetY()) };
			POINT point3 = { long(thirdVertex.GetX()), long(thirdVertex.GetY()) };
			POINT _verticePointStore[3] = { point1, point2, point3 };
			Polygon(hdc,_verticePointStore, sizeof(_verticePointStore)/ sizeof(_verticePointStore[0]));
		}

		DeleteObject(hBrushNew);
		DeleteObject(hPenOld);
		DeleteObject(hLinePen);
	}
	
	

}


bool Rasteriser::sortVerticesAscendingByY(const Vertex& lhs, const Vertex& rhs)
{
	return lhs.GetY() < rhs.GetY();
}


//My own rasterisation code to draw and fill in the model.
void Rasteriser::MyDrawSolidFlat(const Bitmap& bitmap)
{
	HDC hdc = bitmap.GetDC();
	HPEN hPenOld;
	HPEN hLinePen;
	HBRUSH hBrushNew;
	HBRUSH hBrushOld;
	COLORREF qLineColor;



	for (int i = 0; i < _model.GetPolygonCount(); i++)
	{
		qLineColor = _model.GetPolygon(i).GetFinalColor();
		//RGB(0, 0, 0); 
		hLinePen = CreatePen(PS_SOLID, 4, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);
		hBrushNew = CreateSolidBrush(_model.GetPolygon(i).GetFinalColor());
		hBrushOld = (HBRUSH)SelectObject(hdc, hBrushNew);
		Vertex firstVertex = _model.GetUpdatedVerices()[_model.GetPolygon(i).GetIndex(0)];
		Vertex secondVertex = _model.GetUpdatedVerices()[_model.GetPolygon(i).GetIndex(1)];
		Vertex thirdVertex = _model.GetUpdatedVerices()[_model.GetPolygon(i).GetIndex(2)];
		firstVertex.setVertexRGB(_model.GetPolygon(i).GetFinalColor());
		secondVertex.setVertexRGB(_model.GetPolygon(i).GetFinalColor());
		thirdVertex.setVertexRGB(_model.GetPolygon(i).GetFinalColor());

		if (!_model.GetPolygon(i).GetPolygonCulled())
		{
			vector<Vertex> _vertexPointStore = { firstVertex, secondVertex, thirdVertex };
			FillPolygonFlat(hdc, _vertexPointStore);
			//Polygon(hdc, _verticePointStore, sizeof(_verticePointStore) / sizeof(_verticePointStore[0]));
		}

		DeleteObject(hBrushNew);
		DeleteObject(hPenOld);
		DeleteObject(hLinePen);
	}
}

/*this method gets the vertexesand compared them with each other to make sure they are not the same.If the secondVertex.GetY()) == int(thirdVertex.GetY() it will call the FillBottomFlatTriangle function,
if firstVertex.GetY()) == int(secondVertex.GetY() it will call the fillTopFlatTriangle function else it will get all the vertexes and apply the appropriate sums and send them to the 
FillBottomFlatTriangle function and the fillTopFlatTriangle function*/
void Rasteriser::FillPolygonFlat(HDC& hdc, vector<Vertex>& polygonPoints)
{

	/* at first sort the three vertices by y-coordinate ascending,
		* so p1 is the topmost vertice */
	std::sort(polygonPoints.begin(), polygonPoints.end(), sortVerticesAscendingByY);
	Vertex firstVertex = polygonPoints[0];
	Vertex secondVertex = polygonPoints[1];
	Vertex thirdVertex = polygonPoints[2];

	COLORREF firstVertexColor = firstVertex.getVertexRGB();
	COLORREF secondVertexColor = secondVertex.getVertexRGB();
	COLORREF thirdVertexColor = thirdVertex.getVertexRGB();

	/* here we know that v1.y <= v2.y <= v3.y */
	   /* check for trivial case of bottom-flat triangle */
	if (int(secondVertex.GetY()) == int(thirdVertex.GetY()))
	{
		FillBottomFlatTriangle(hdc, firstVertex, secondVertex, thirdVertex, firstVertexColor, secondVertexColor, thirdVertexColor);
	}
	/* check for trivial case of top-flat triangle */
	else if (int(firstVertex.GetY()) == int(secondVertex.GetY()))
	{
		fillTopFlatTriangle(hdc, firstVertex, secondVertex, thirdVertex, firstVertexColor, secondVertexColor, thirdVertexColor);
	}
	else
	{
		/* general case - split the triangle in a top-flat and bottom-flat one */
		Vertex vTmp = Vertex((firstVertex.GetX() + (float((secondVertex.GetY() - firstVertex.GetY())) / float((thirdVertex.GetY() - firstVertex.GetY()))) * (thirdVertex.GetX() - firstVertex.GetX())), secondVertex.GetY(), float(1), float(1));
		/* get the intermediate color at the temporary point */
		float cBlue = GetBValue(firstVertexColor) + (float((secondVertex.GetY() - firstVertex.GetY())) / float((thirdVertex.GetY() - firstVertex.GetY()))) * (GetBValue(thirdVertexColor) - GetBValue(firstVertexColor));
		float cRed = GetRValue(firstVertexColor) + (float((secondVertex.GetY() - firstVertex.GetY())) / float((thirdVertex.GetY() - firstVertex.GetY()))) * (GetRValue(thirdVertexColor) - GetRValue(firstVertexColor));
		float cGreen = GetGValue(firstVertexColor) + (float((secondVertex.GetY() - firstVertex.GetY())) / float((thirdVertex.GetY() - firstVertex.GetY()))) * (GetGValue(thirdVertexColor) - GetGValue(firstVertexColor));
		COLORREF cTmp = RGB(cRed, cGreen, cBlue);

		FillBottomFlatTriangle(hdc, firstVertex, secondVertex, vTmp, firstVertexColor, secondVertexColor, cTmp);
		fillTopFlatTriangle(hdc, secondVertex, vTmp, thirdVertex, secondVertexColor, cTmp, thirdVertexColor);
	}

}


void Rasteriser::FillBottomFlatTriangle(const HDC& hdc, Vertex v1, Vertex v2, Vertex v3, COLORREF c1, COLORREF c2, COLORREF c3)
{
	float slope1 = (v2.GetX() - v1.GetX()) / (v2.GetY() - v1.GetY());
	float slope2 = (v3.GetX() - v1.GetX()) / (v3.GetY() - v1.GetY());

	float x1 = float(v1.GetX());
	float x2 = float(v1.GetX() + 0.5f);

	//Colour change along the v2 v1 edge
	float v2v1Diff = (v2.GetY() - v1.GetY());
	float colorSlopeBlue1 = (GetBValue(c2) - GetBValue(c1)) / v2v1Diff;
	float colorSlopeRed1 = (GetRValue(c2) - GetRValue(c1)) / v2v1Diff;
	float colorSlopeGreen1 = (GetGValue(c2) - GetGValue(c1)) / v2v1Diff;

	//Colour change along the v3,v1 edge
	float v3v1Diff = (v2.GetY() - v1.GetY());
	float colorSlopeBlue2 = (GetBValue(c3) - GetBValue(c1)) / v3v1Diff;
	float colorSlopeRed2 = (GetRValue(c3) - GetRValue(c1)) / v3v1Diff;
	float colorSlopeGreen2 = (GetGValue(c3) - GetGValue(c1)) / v3v1Diff;

	//Get starting values
	float cBlue1 = GetBValue(c1);
	float cRed1 = GetRValue(c1);
	float cGreen1 = GetGValue(c1);
	float cBlue2 = GetBValue(c1);
	float cRed2 = GetRValue(c1);
	float cGreen2 = GetGValue(c1);

	/* as we will do not fill in a complete line using fillrect but instead
		 * we will loop over all pixels of a horizontal line, we need a predefined
		 * direction -> choose left to right. This means that x1 must be the smaller
		 * compared to x2 so slope1 must be smaller than slope2. If not we gonna
		 * swap it here.
		 */
	if (slope2 < slope1)
	{
		float slopeTMP = slope1;
		slope1 = slope2;
		slope2 = slopeTMP;

		slopeTMP = colorSlopeRed1;
		colorSlopeRed1 = colorSlopeRed2;
		colorSlopeRed2 = slopeTMP;

		slopeTMP = colorSlopeGreen1;
		colorSlopeGreen1 = colorSlopeGreen2;
		colorSlopeGreen2 = slopeTMP;

		slopeTMP = colorSlopeBlue1;
		colorSlopeBlue1 = colorSlopeBlue2;
		colorSlopeBlue2 = slopeTMP;
	}

	for (int scanlineY = int(round(v1.GetY())); scanlineY <= int(v2.GetY()); scanlineY++)
	{
		/* loop over each pixel of horizontal line */
		for (int xPos = int(ceil(x1)); xPos < int(x2); xPos++)
		{
			float t = (xPos - x1) / (x2 - x1);

			int red = int(((1 - t) * cRed1 + t * cRed2));
			int green = int(((1 - t) * cGreen1 + t * cGreen2));
			int blue = int(((1 - t) * cBlue1 + t * cBlue2));
			
			COLORREF setColor = RGB(red, green, blue);
			SetPixel(hdc, xPos, scanlineY, setColor);
			
		}
		/* get new x-coordinate of endpoints of horizontal line */
		x1 += slope1;
		x2 += slope2;

		/* get new color of left endpoint of horizontal line */
		cRed1 += colorSlopeRed1;
		cGreen1 += colorSlopeGreen1;
		cBlue1 += colorSlopeBlue1;

		/* get new color of right endpoint of horizontal line */
		cRed2 += colorSlopeRed2;
		cGreen2 += colorSlopeGreen2;
		cBlue2 += colorSlopeBlue2;
	}

	

}

void Rasteriser::fillTopFlatTriangle(const HDC& hdc, Vertex v1, Vertex v2, Vertex v3, COLORREF c1, COLORREF c2, COLORREF c3)
{
	float slope1 = float((v3.GetX() - v1.GetX())) / float((v3.GetY() - v1.GetY()));
	float slope2 = float((v3.GetX() - v2.GetX())) / float((v3.GetY() - v2.GetY()));

	float x1 = v3.GetX();
	float x2 = v3.GetX() + 0.5f;

	/* get the change of color components along edge (v3,v1) */
	float v3v1Diff = float((v3.GetY() - v1.GetY()));
	float colorSlopeBlue1 = float((GetBValue(c3) - GetBValue(c1))) / v3v1Diff;
	float colorSlopeRed1 = float((GetRValue(c3) - GetRValue(c1))) / v3v1Diff;
	float colorSlopeGreen1 = float((GetGValue(c3) - GetGValue(c1))) / v3v1Diff;

	/* get the change of color components along edge (v3,v2) */
	float v3v2Diff = float((v3.GetY() - v2.GetY()));
	float colorSlopeBlue2 = float((GetBValue(c3) - GetBValue(c2))) / v3v2Diff;
	float colorSlopeRed2 = float((GetRValue(c3) - GetRValue(c2))) / v3v2Diff;
	float colorSlopeGreen2 = float((GetGValue(c3) - GetGValue(c2))) / v3v2Diff;

	/* set starting values */
	float cBlue1 = GetBValue(c3);
	float cRed1 = GetRValue(c3);
	float cGreen1 = GetGValue(c3);
	float cBlue2 = GetBValue(c3);
	float cRed2 = GetRValue(c3);
	float cGreen2 = GetGValue(c3);

	/* as we will do not fill in a complete line using fillrect but instead
		 * we will loop over all pixels of a horizontal line, we need a predefined
		 * direction -> choose left to right. This means that x1 must be the smaller
		 * compared to x2 so slope1 must be smaller than slope2. If not we gonna
		 * swap it here.
		 */
	if (slope1 < slope2)
	{
		float slopeTMP = slope1;
		slope1 = slope2;
		slope2 = slopeTMP;

		slopeTMP = colorSlopeRed1;
		colorSlopeRed1 = colorSlopeRed2;
		colorSlopeRed2 = slopeTMP;

		slopeTMP = colorSlopeGreen1;
		colorSlopeGreen1 = colorSlopeGreen2;
		colorSlopeGreen2 = slopeTMP;

		slopeTMP = colorSlopeBlue1;
		colorSlopeBlue1 = colorSlopeBlue2;
		colorSlopeBlue2 = slopeTMP;
	}

	for(int scanLineY = int(round(v3.GetY())); scanLineY > int(v1.GetY()); scanLineY--)
	{
		/* get new x-coordinate of endpoints of horizontal line */
		for (int xPos = int(ceil(x1)); xPos < int(x2); xPos++)
		{
			float t = (xPos - x1) / (x2 - x1);

			int red = int(((1 - t) * cRed1 + t * cRed2));
			int green = int(((1 - t) * cGreen1 + t * cGreen2));
			int blue = int(((1 - t) * cBlue1 + t * cBlue2));

			COLORREF setColour = RGB(red, green, blue);
			SetPixel(hdc, xPos, scanLineY, setColour);
			
		}
		/* get new x-coordinate of endpoints of horizontal line */
		x1 -= slope1;
		x2 -= slope2;

		/* get new x-coordinate of endpoints of horizontal line */
		cRed1 -= colorSlopeRed1;
		cGreen1 -= colorSlopeGreen1;
		cBlue1 -= colorSlopeBlue1;

		/* get new x-coordinate of endpoints of horizontal line */
		cRed2 -= colorSlopeRed2;
		cGreen2 -= colorSlopeGreen2;
		cBlue2 -= colorSlopeBlue2;
	}
}

void Rasteriser::DrawString(const Bitmap& bitmap, LPCTSTR text)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}




