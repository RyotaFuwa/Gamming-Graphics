#include "RYOTADraw.h"
#include <vector>
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/Matrix4.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "RasterisationMesh.h"
#include "RenderObject.h"
#include "Renderer.h"

using namespace NCL::CSC3223;

void NCL::CSC3223::RYOTAName(Renderer& renderer)
{
	// vertices needed to describe the alphabet. (i.e. edges of alphabet)
	std::vector<Vector3> vecR = { Vector3(-100, 0, 0), Vector3(-100, 100, 0), Vector3(100, 50, 0), Vector3(100, -100, 0), Vector3(-100, -100, 0) };
	std::vector<Vector3> vecY = { Vector3(0, 0, 0), Vector3(-100, 100, 0), Vector3(100, 100, 0), Vector3(0, -100, 0) };
	std::vector<Vector3> vecO = { Vector3(100, 100, 0), Vector3(-100, 100, 0), Vector3(-100, -100, 0), Vector3(100, -100, 0) };
	std::vector<Vector3> veco = { Vector3(75, 75, 0), Vector3(-75, 75, 0), Vector3(-75, -75, 0), Vector3(75, -75, 0) };
	std::vector<Vector3> vecT = { Vector3(100, 100, 0), Vector3(-100, 100, 0), Vector3(0, 100, 0), Vector3(0, -100, 0) };
	std::vector<Vector3> vecA = { Vector3(100, -100, 0), Vector3(-100, -100, 0), Vector3(50, 0, 0), Vector3(-50, 0, 0), Vector3(0, 100, 0) };


	// R
	OGLMesh* R_above = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({ vecR[0], vecR[1], vecR[2] },
		{ Vector4(0, 1, 0, 1), Vector4(1, 1, 0, 1), Vector4(0, 1, 1, 1) });
	OGLMesh* R_leg1 = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecR[0], vecR[3] },
		{ Vector4(0, 1, 0, 1), Vector4(0, 0, 1, 1) }, true);
	OGLMesh* R_leg2 = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecR[0], vecR[4] },
		{ Vector4(1, 1, 0, 1), Vector4(0, 1, 1, 1) }, true);

	Matrix4 matR = Matrix4::Translation(Vector3(220 * 1, 0, 0));

	renderer.AddRenderObject(new RenderObject(R_above, matR));
	renderer.AddRenderObject(new RenderObject(R_leg1, matR));
	renderer.AddRenderObject(new RenderObject(R_leg2, matR));

	// Y 
	OGLMesh* Y_above = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({ vecY[0], vecY[1], vecY[2] },
		{ Vector4(0, 0, 1, 1), Vector4(1, 0, 0, 1), Vector4(1, 0, 0, 1) });
	OGLMesh* Y_leg = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecY[0], vecY[3] },
		{ Vector4(0, 0, 1, 1), Vector4(1, 0, 0, 1) }, false);

	Matrix4 matY = Matrix4::Translation(Vector3(220 * 2, 0, 0));

	renderer.AddRenderObject(new RenderObject(Y_above, matY));
	renderer.AddRenderObject(new RenderObject(Y_leg, matY));

	// O 
	OGLMesh* O_outside1 = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({ vecO[0], vecO[1], vecO[2] },
		{ Vector4(1, 0, 0, 1), Vector4(0, 0, 1, 1), Vector4(1, 0, 0, 1) }, 1);
	OGLMesh* O_outside2 = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({ vecO[0], vecO[3], vecO[2] },
		{ Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), Vector4(1, 0, 0, 1) });
	OGLMesh* O_inside1 = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({ veco[0], veco[1], veco[2] },
		{ Vector4(0, 0, 0, 0.2), Vector4(0, 0, 0, 0.2), Vector4(0, 0, 0, 0.2) }, 1);
	OGLMesh* O_inside2 = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({ veco[0], veco[3], veco[2] },
		{ Vector4(0, 0, 0, 0.5), Vector4(0, 0, 0, 0.5), Vector4(0, 0, 0, 0.5) });

	Matrix4 matO = Matrix4::Translation(Vector3(220 * 3, 0, 0));

	renderer.AddRenderObject(new RenderObject(O_outside1, matO));
	renderer.AddRenderObject(new RenderObject(O_outside2, matO));
	renderer.AddRenderObject(new RenderObject(O_inside1, matO));
	renderer.AddRenderObject(new RenderObject(O_inside2, matO));

	// T
	OGLMesh* T_above = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecT[0], vecT[1] },
		{ Vector4(1, 1, 0, 1), Vector4(0, 1, 1, 1) }, false);
	OGLMesh* T_leg = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecT[2], vecT[3] },
		{ Vector4(0.5, 1, 0.5, 1), Vector4(1, 0, 1, 1) }, false);

	Matrix4 matT = Matrix4::Translation(Vector3(220 * 4, 0, 0));

	renderer.AddRenderObject(new RenderObject(T_above, matT));
	renderer.AddRenderObject(new RenderObject(T_leg, matT));

	// A
	OGLMesh* A_above = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({ vecA[4], vecA[3], vecA[2] },
		{ Vector4(0, 1, 0, 1), Vector4(1, 1, 0, 1), Vector4(0, 1, 1, 1) }, 1);
	OGLMesh* A_leg1 = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecA[0], vecA[2] },
		{ Vector4(0, 1, 0, 1), Vector4(0, 0, 1, 1) }, true);
	OGLMesh* A_leg2 = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecA[1], vecA[3] },
		{ Vector4(1, 1, 0, 1), Vector4(0, 1, 1, 1) }, true);

	Matrix4 matA = Matrix4::Translation(Vector3(220 * 5, 0, 0));

	renderer.AddRenderObject(new RenderObject(A_above, matA));
	renderer.AddRenderObject(new RenderObject(A_leg1, matA));
	renderer.AddRenderObject(new RenderObject(A_leg2, matA));



	//orthographic perspective
	Matrix4 proj2d = Matrix4::Orthographic(-1.0f, 100.0f, 1400, 0, 500, -500);
	renderer.SetProjectionMatrix(proj2d);

}

