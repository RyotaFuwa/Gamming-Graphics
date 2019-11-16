#pragma once
#include <vector>

#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"

#include "Renderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

using namespace NCL;
using namespace CSC3223;
using std::vector;


enum CUBECOLOUR {
	BLACK = 0,
	WHITE,
	RED,
	GREEN,
	BLUE,
};

class Cube
{
private:
	OGLMesh* cube;
	Vector3 center;
	CUBECOLOUR colourNum;

public:
	Cube();
	Cube(vector<Vector3> pos, CUBECOLOUR colourNum = CUBECOLOUR::WHITE);
	Cube(Renderer& renderer);

	Vector3 GetCentroid();
	vector<Vector4> GetColours(CUBECOLOUR colNum);
};

