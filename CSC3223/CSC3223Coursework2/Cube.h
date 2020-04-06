#pragma once
#include <vector>

#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/Matrix4.h"

#include "Renderer.h"
#include "RenderObject.h"
#include "Tools.h"

using namespace NCL;
using namespace CSC3223;
using namespace CW2Tools;
using std::vector;

enum CUBEPATTERN {
	BASIC1,
	ADVANCED1,
	ADVANCED2,
	ADVANCED3,
};

class Cube : public RenderObject
{
public:
	Cube();
	Cube(CUBEPATTERN cp);
	Cube(MeshGeometry* mesh, Matrix4 mat = Matrix4());
	Cube(vector<Vector3> pos, CUBECOLOUR colourNum = CUBECOLOUR::WHITE);
	Cube(const std::string& filename);
	~Cube();

	void Move() override;
	void Basic1Move();
	void Advanced1Move();
	void Advanced2Move();
	void Advanced3Move();

	void AddUniforms(const int programID) override;
	void Basic1Uniform(int programID);
	void Advanced1Uniform(int programID);
	void Advanced2Uniform(int programID);
	void Advanced3Uniform(int programID);

	void SetCubePattern(CUBEPATTERN cb) { cubePattern = cb; }
	CUBEPATTERN GetCubePattern() { return cubePattern; }
	void SetDynamic(bool state) { dynamic = state; }
	bool GetDynamic() { return dynamic; }
	void SetDecayTime(float t) { decayTime = t; }
	float GetDecayTime() const { return decayTime; }
	void SetFirstPosition(Vector3 fp) {
		firstPosition = fp;
		SetTransform(Matrix4::Translation(firstPosition));
	}
	Vector3 GetFirstPosition() { return firstPosition; }

protected:
	CUBEPATTERN cubePattern = BASIC1;

	float decayTime = 20.0f;
	Vector3 center = Vector3(0, 0, 0);

	// advanced3
	Vector3 firstPosition = Vector3(0, 0, 0);
	float rotateDir = PlusMinus();
	float radius0;
};


