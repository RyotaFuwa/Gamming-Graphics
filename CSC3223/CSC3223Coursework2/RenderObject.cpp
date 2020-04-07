#include "RenderObject.h"
#include "../../Common/MeshGeometry.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"

using namespace NCL;
using namespace CSC3223;
using namespace NCL::Rendering;

RenderObject::RenderObject()
{
	mesh = nullptr;
	transform = Matrix4();
	shader = nullptr;
}

RenderObject::RenderObject(MeshGeometry* inMesh, Matrix4 m)
{
	mesh = inMesh;
	transform = m;
	shader = nullptr;
}

RenderObject::~RenderObject()
{
	if (createdInside) {
		delete mesh;
		mesh = nullptr;
	}
}