#include "Cube.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"

#include <vector>


using namespace NCL;
using namespace CSC3223;
using std::vector;

Cube::Cube()
{
	cube = nullptr;
}

Cube::Cube(vector<Vector3> pos, CUBECOLOUR colourNum)
{
	cube = new OGLMesh();
	cube->SetPrimitiveType(GeometryPrimitive::Triangles);
	cube->SetVertexPositions(pos);
	std::vector<Vector4> colours = GetColours(colourNum);
	cube->UploadToGPU();
}

Cube::Cube(Renderer& renderer)
{
    cube = new OGLMesh("cube.msh");
	cube->SetPrimitiveType(GeometryPrimitive::Triangles);
	cube->UploadToGPU();
	
	center = GetCentroid(cube->GetPositionData());
}

Vector3 Cube::GetCentroid()
{
	if (cube != nullptr) {
		Vector3 centroid = Vector3(0, 0, 0);
		for (Vector3 each : pos) {
			centroid += each;
		}
		centroid /= pos.size();
		return centroid;
	}
	else
	    return Vector3(0, 0, 0);
}

vector<Vector4> Cube::GetColours(CUBECOLOUR colNum)
{

	return vector<Vector4>();
}
