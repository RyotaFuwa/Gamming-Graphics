#include "BackGround.h"
#include "Renderer.h"
#include "RasterisationMesh.h"
#include "../../Common/Matrix4.h"

NCL::CSC3223::BackGround* NCL::CSC3223::BackGround::active = nullptr;

NCL::CSC3223::BackGround::BackGround(Renderer* r) :
	renderer(r),
	time(0.0f),
	viewPos(Vector3(0.0f, 0.0f, 0.0f)),
	viewRot(Vector3(0.0f, 0.0f, 0.0f)),
	perspective(Matrix4())
{
	if (active == nullptr)
		active = this;
}

NCL::CSC3223::BackGround::~BackGround()
{
}

void NCL::CSC3223::BackGround::ObjectsUpdate(float dt)
{
	for (unsigned int i = 0; i != objects.size(); i++) {
		Matrix4 mat = objects[i]->GetTransform();
		Vector3 vel = velocities[i];
		Vector3 angVel = angularVelocities[i];
		objects[i]->SetTransform(Matrix4::Translation(vel * dt) * mat * Matrix4::Rotation(angVel.Length() * dt, angVel));
	}
}

void NCL::CSC3223::BackGround::Update(float dt)
{
	ObjectsUpdate(dt);
	ViewUpdate();
}

void NCL::CSC3223::BackGround::Activate()
{
	active = this;
	renderer->SetRenderObjects(active->objects);
}

NCL::CSC3223::BackGround* NCL::CSC3223::BackGround::GetActiveBG()
{
	return active;
}

void NCL::CSC3223::BackGround::SetViewTo(Vector3 pos, Vector3 rot)
{
	viewPos = pos;
	viewRot = rot;
}

void NCL::CSC3223::BackGround::SetViewPos(Vector3 pos)
{
	viewPos = pos;
}

Vector3 NCL::CSC3223::BackGround::GetViewPos()
{
	return viewPos;
}

void NCL::CSC3223::BackGround::SetViewRot(Vector3 rot)
{
	viewRot = rot;
}

Vector3 NCL::CSC3223::BackGround::GetViewRot()
{
	return viewRot;
}

Vector2 NCL::CSC3223::BackGround::GetDepth()
{
	return depth;
}

void NCL::CSC3223::BackGround::Reset()
{
	SetViewTo();
	for (unsigned int i = 0; i != objects.size(); i++) {
		objects[i]->SetTransform(originalPos[i]);
	}
}

void NCL::CSC3223::BackGround::SetObject(RenderObject* ro, Vector3 velocity, Vector3 angularVelocity)
{
	objects.push_back(ro);
	originalPos.push_back(ro->GetTransform());
	velocities.push_back(velocity);
	angularVelocities.push_back(angularVelocity);
}

void NCL::CSC3223::BackGround::RemoveObject(RenderObject* ro)
{
	auto i = std::find(objects.begin(), objects.end(), ro);
	if (i != objects.end()) {
		objects.erase(i);
	}
}

void NCL::CSC3223::BackGround::ViewUpdate()
{
	renderer->SetViewMatrix(
		Matrix4::Translation(viewPos) * Matrix4::Rotation(viewRot.Length(), viewRot)
	);
}

NCL::CSC3223::BackGround2D::BackGround2D(Renderer* r, float width, float height, Vector2 depth) :
	BackGround(r)
{
    perspective = Matrix4::Orthographic(depth[0], depth[1], width / 2.0, -width / 2.0, height / 2.0, -height / 2.0);
	renderer->SetProjectionMatrix(perspective);
	this->depth = depth;
}

NCL::CSC3223::BackGround2D::~BackGround2D()
{
}


NCL::CSC3223::BackGround3D::BackGround3D(Renderer* r, float aspect, float angle, Vector2 depth) :
	BackGround(r)
{
	perspective = Matrix4::Perspective(depth[0], depth[1], aspect, angle);
	renderer->SetProjectionMatrix(perspective);
	this->depth = depth;
}

NCL::CSC3223::BackGround3D::~BackGround3D()
{
}

NCL::CSC3223::RYOTAName::RYOTAName(Renderer* r):
	BackGround(r)
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

    SetObject(new RenderObject(R_above, matR));
	SetObject(new RenderObject(R_leg1, matR));
	SetObject(new RenderObject(R_leg2, matR));

	// Y 
	OGLMesh* Y_above = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({ vecY[0], vecY[1], vecY[2] },
		{ Vector4(0, 0, 1, 1), Vector4(1, 0, 0, 1), Vector4(1, 0, 0, 1) });
	OGLMesh* Y_leg = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecY[0], vecY[3] },
		{ Vector4(0, 0, 1, 1), Vector4(1, 0, 0, 1) }, false);

	Matrix4 matY = Matrix4::Translation(Vector3(220 * 2, 0, 0));

	SetObject(new RenderObject(Y_above, matY));
	SetObject(new RenderObject(Y_leg, matY));

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

	SetObject(new RenderObject(O_outside1, matO));
	SetObject(new RenderObject(O_outside2, matO));
	SetObject(new RenderObject(O_inside1, matO));
	SetObject(new RenderObject(O_inside2, matO));

	// T
	OGLMesh* T_above = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecT[0], vecT[1] },
		{ Vector4(1, 1, 0, 1), Vector4(0, 1, 1, 1) }, false);
	OGLMesh* T_leg = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecT[2], vecT[3] },
		{ Vector4(0.5, 1, 0.5, 1), Vector4(1, 0, 1, 1) }, false);

	Matrix4 matT = Matrix4::Translation(Vector3(220 * 4, 0, 0));

	SetObject(new RenderObject(T_above, matT));
	SetObject(new RenderObject(T_leg, matT));

	// A
	OGLMesh* A_above = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({ vecA[4], vecA[3], vecA[2] },
		{ Vector4(0, 1, 0, 1), Vector4(1, 1, 0, 1), Vector4(0, 1, 1, 1) }, 1);
	OGLMesh* A_leg1 = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecA[0], vecA[2] },
		{ Vector4(0, 1, 0, 1), Vector4(0, 0, 1, 1) }, true);
	OGLMesh* A_leg2 = (OGLMesh*)RasterisationMesh::CreateLineFromPoints({ vecA[1], vecA[3] },
		{ Vector4(1, 1, 0, 1), Vector4(0, 1, 1, 1) }, true);

	Matrix4 matA = Matrix4::Translation(Vector3(220 * 5, 0, 0));

	SetObject(new RenderObject(A_above, matA));
	SetObject(new RenderObject(A_leg1, matA));
	SetObject(new RenderObject(A_leg2, matA));



	//orthographic perspective
	Matrix4 proj2d = Matrix4::Orthographic(-1.0f, 100.0f, 1400, 0, 500, -500);
	renderer->SetProjectionMatrix(proj2d);

}

NCL::CSC3223::RYOTAName::~RYOTAName()
{
}
