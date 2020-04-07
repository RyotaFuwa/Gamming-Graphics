#include "Cube.h"

#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"
#include "Tools.h"

#include <vector>
#include <iostream>

using namespace NCL;
using namespace CSC3223;
using namespace CW2Tools;
using std::vector;

Cube::Cube()
{
	createdInside = true;
	mesh = new OGLMesh("cube2.msh");
	mesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	mesh->UploadToGPU();
}

Cube::Cube(CUBEPATTERN cp)
{
	cubePattern = cp;
	createdInside = true;
	mesh = new OGLMesh("cube2.msh");
	mesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	mesh->UploadToGPU();
}

Cube::Cube(MeshGeometry* mesh, Matrix4 mat) : RenderObject(mesh, mat)
{
}

Cube::Cube(vector<Vector3> pos, CUBECOLOUR colourNum)
{
	createdInside = true;
	this->mesh = new OGLMesh();
	this->mesh->SetPrimitiveType(GeometryPrimitive::Triangles);
	this->mesh->SetVertexPositions(pos);
	this->mesh->SetVertexColours(GetColourVectors(pos.size(), colourNum));
	this->mesh->UploadToGPU();
}

Cube::Cube(const std::string& filename)
{
	createdInside = true;
	this->mesh = new OGLMesh(filename);
}

Cube::~Cube()
{
}

void Cube::Move() {
	switch (cubePattern) {
	case BASIC1:
		Basic1Move();
		break;
	case ADVANCED1:
		Advanced1Move();
		break;
	case ADVANCED2:
		Advanced2Move();
		break;
	case ADVANCED3:
		Advanced3Move();
		break;
	default:
		break;
	}
}

void Cube::Basic1Move()
{
	float dt = time - lastTime;
	transform = transform * Matrix4::Rotation(dt * 30, Vector3(1, 1, 1));
	lastTime = time;
}

void Cube::Advanced1Move()
{
	Basic1Move();
}

void Cube::Advanced2Move()
{
	Basic1Move();
}

void Cube::Advanced3Move()
{
	float dt = time - lastTime;
	float rotateRate = 5 + pow(2.75f * time / decayTime + 1.0f, 4.5);
	transform = Matrix4::Rotation(rotateRate * dt, Vector3(0, 1, 0)) * transform * Matrix4::Rotation(dt * 50, Vector3(1, 1, 1));
	lastTime = time;
}

void Cube::AddUniforms(int programID) {
	switch (cubePattern) {
	case BASIC1:
		Basic1Uniform(programID);
		break;
	case ADVANCED1:
		Advanced1Uniform(programID);
		break;
	case ADVANCED2:
		Advanced2Uniform(programID);
		break;
	case ADVANCED3:
		Advanced3Uniform(programID);
		break;
	default:
		break;
	}
}

void Cube::Basic1Uniform(int programID)
{
	int decayRateLocation = glGetUniformLocation(programID, "decay");
	if (decayRateLocation >= 0) {
		float decay = 1.0f - time / decayTime;
		if (decay <= 0.0f)
			decay = 0.0f;
		glUniform1f(decayRateLocation, decay);

	}

	int centerLocation = glGetUniformLocation(programID, "center");
	if (centerLocation >= 0) {
		glUniform3fv(centerLocation, 1, (float*)& center);
	}

}

void Cube::Advanced1Uniform(int programID)
{
	int decayRateLocation = glGetUniformLocation(programID, "decay");
	if (decayRateLocation >= 0) {
		float decay = 1.0f - time / decayTime;
		if (decay <= 0.0f)
			decay = 0.0f;
		glUniform1f(decayRateLocation, decay);

		int giggleLocation = glGetUniformLocation(programID, "giggle");
		if (giggleLocation >= 0) {
			Vector3 giggleVec = RandVec3(0.0f, 0.15f * (1 - decay));
			glUniform3fv(giggleLocation, 1, (float*)& giggleVec);
		}
	}
}

void Cube::Advanced2Uniform(int programID)
{
	int decayRateLocation = glGetUniformLocation(programID, "decay");
	if (decayRateLocation >= 0) {
		float decay = 1.0f - time / decayTime;
		if (decay <= 0.0f)
			decay = 0.0f;
		glUniform1f(decayRateLocation, decay);

	}

	int centerLocation = glGetUniformLocation(programID, "center");
	if (centerLocation >= 0) {
		glUniform3fv(centerLocation, 1, (float*)& center);
	}
}

void Cube::Advanced3Uniform(int programID)
{
	int decayRateLocation = glGetUniformLocation(programID, "decay");
	if (decayRateLocation >= 0) {
		float decay = 1.0f - time / decayTime;
		if (decay <= 0.0f)
			decay = 0.0f;
		glUniform1f(decayRateLocation, decay);
	}

}



