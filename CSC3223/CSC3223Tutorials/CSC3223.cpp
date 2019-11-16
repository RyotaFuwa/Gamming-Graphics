#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"

//include RasterisationMesh.h for tutorial 2
#include "RasterisationMesh.h"

using namespace NCL;
using namespace CSC3223;

// tutorial 10
void Tutorial10_1(Renderer& renderer) {
	std::vector<Vector4> rgb = {
		Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), Vector4(0, 0, 1, 1) };

	std::vector<Vector3> verts = {
		Vector3(-1, -1, 0), Vector3(1, -1, 0), Vector3(0, 1, 0) };

	OGLMesh* tri = new OGLMesh();
	tri->SetVertexPositions(verts);
	tri->SetVertexColours(rgb);
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();
	Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, -30)) * Matrix4::Scale(Vector3(5, 5, 5));

	RenderObject* object = new RenderObject(tri, modelMat);
	// object->SetShader(newShader);
	// OGLShader* newShader = new OGLShader("VertexFocus.glsl", "ScreenColourFrag.glsl");
	renderer.AddRenderObject(object);
}


// tutorial 9
void Tutorial9(Renderer& renderer) {
	std::vector<Vector4> rgb = {
		Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), Vector4(0, 0, 1, 1) };

	std::vector<Vector3> verts = {
		Vector3(-1, -1, 0), Vector3(1, -1, 0), Vector3(0, 1, 0) };

	OGLMesh* tri = new OGLMesh();
	tri->SetVertexPositions(verts);
	tri->SetVertexColours(rgb);
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();

	Matrix4 modelMat = Matrix4::Translation(Vector3(50, 50, 0)) * Matrix4::Scale(Vector3(20, 20, 20));

	OGLShader* newShader = new OGLShader("ShrinkObject.glsl", "rasterisationFrag.glsl");
	RenderObject* object = new RenderObject(tri, modelMat);
    object->SetShader(newShader);
	renderer.AddRenderObject(object);
}

// tutorial 8
void Tutorial8_1(Renderer& renderer) {
	std::vector<Vector3> verts = {
		Vector3(-1 , -1 ,0) , Vector3(1 , -1 ,0) , Vector3(0 ,1 ,0) };

	std::vector < Vector4 > red = {
        Vector4(1 ,0 ,0 ,0.25) , Vector4(1 ,0 ,0 ,0.33) , Vector4(1 ,0 ,0 ,0.5) };
	std::vector < Vector4 > blue = {
	    Vector4(0 ,0 ,1 ,0.75) , Vector4(0 ,0 ,1 ,0.75) , Vector4(0 ,0 ,1 ,0.75) };

	OGLMesh* tri_blue = new OGLMesh();
	OGLMesh* tri_red = new OGLMesh();
	tri_blue->SetVertexPositions(verts);
	tri_blue->SetVertexColours(blue);
	tri_blue->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri_blue->UploadToGPU();

	tri_red->SetVertexPositions(verts);
	tri_red->SetVertexColours(red);
	tri_red->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri_red->UploadToGPU();

	Matrix4 modelMat_blue = Matrix4::Translation(Vector3(200, 200, 0)) *
		Matrix4::Scale(Vector3(200, 200, 200));
	RenderObject* renderObj_blue = new RenderObject(tri_blue, modelMat_blue);
	
	Matrix4 modelMat_red = Matrix4::Translation(Vector3(200, 200, 0)) *
		Matrix4::Rotation(30.0f, Vector3(0, 0, 1)) *
		Matrix4::Scale(Vector3(200, 200, 200));
	RenderObject* renderObj_red = new RenderObject(tri_red, modelMat_red);

	renderer.AddRenderObject(renderObj_red);
	renderer.AddRenderObject(renderObj_blue);
}

// tutorial 7
void Tutorial7_1(Renderer& renderer) {
	std::vector<Vector3> verts = {
		Vector3(-1 , -1 ,0) , Vector3(1 , -1 ,0) , Vector3(0 ,1 ,0) };
	std::vector<Vector4> white = {
		Vector4(1, 1, 1, 1), Vector4(1, 1, 1, 1), Vector4(1, 1, 1, 1) };
	std::vector < Vector2 > texCoords = {
		Vector2(0 ,0) , Vector2(10 ,0) , Vector2(5, 10) };

	OGLMesh* tri = new OGLMesh();
	tri->SetVertexPositions(verts);
	tri->SetVertexColours(white);
	tri->SetVertexTextureCoords(texCoords);
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();

	Matrix4 modelMat = Matrix4::Translation(Vector3(200, 200, 0)) *
		              // Matrix4::Rotation(45.0f, Vector3(1, 0, 0)) *
		               Matrix4::Scale(Vector3(200, 200, 200));
	TextureBase* newTex = OGLTexture::RGBATextureFromFilename("NCL.PNG");
    RenderObject* renderObj = new RenderObject(tri, modelMat);
	renderObj->SetBaseTexture(newTex);
    renderer.EnableMipMapFiltering(*(OGLTexture*)newTex);
	renderer.EnableTextureRepeating(*(OGLTexture*)newTex, true, true);
    renderer.AddRenderObject(renderObj);
}

// tutorial6
void Tutorial6_1(Renderer& renderer) {
	std :: vector < Vector4 > red =
		{ Vector4 (1 ,0 ,0 ,1) , Vector4 (1 ,0 ,0 ,1) , Vector4 (1 ,0 ,0 ,1) };
	std :: vector < Vector4 > blue =
		{ Vector4 (0 ,0 ,1 ,1) , Vector4 (0 ,0 ,1 ,1) , Vector4 (0 ,0 ,1 ,1) };
	std :: vector < Vector3 > verts =
		{ Vector3 ( -1 , -1 ,0) , Vector3 (1 , -1 ,0) , Vector3 (0 ,1 ,0) };
     
    OGLMesh* redTri = new OGLMesh();
	redTri->SetVertexPositions(verts);
	redTri->SetVertexColours(red);
	redTri->SetPrimitiveType(GeometryPrimitive::Triangles);
	redTri->UploadToGPU();

	OGLMesh * blueTri = new OGLMesh();
	blueTri->SetVertexPositions(verts);
	blueTri->SetVertexColours(blue);
	blueTri->SetPrimitiveType(GeometryPrimitive::Triangles);
	blueTri->UploadToGPU();
	}

// tutorial 5
void Tutorial5_1(Renderer& renderer) {
	OGLMesh* tri = new OGLMesh("cube.msh");
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();

	for(int y = -4; y < 3; ++y) {
		for(int x = -4; x < 4; ++x) {
			float zAmount = rand() % 30;
			float scaleAmount = (( rand() % 3) + 1);

			Matrix4 translate = Matrix4::Translation(
			Vector3(( x + 1) * 10 , ( y + 1) * 10 , -50 - zAmount ));
			Matrix4 rotate = Matrix4::Rotation(
			(( y * 5) + x ) * 10 , Vector3(0 , 0 , 1));

			Matrix4 scale = Matrix4::Scale(
			Vector3( scaleAmount , scaleAmount , scaleAmount ));

			renderer.AddRenderObject(new RenderObject(tri ,
			translate * rotate * scale ));

		}
	}
}

// tutorial 4
void Tutorial4_1(Renderer& renderer) {
	OGLMesh* tri = new OGLMesh();
	tri->SetVertexPositions(
		{ Vector3(-1, 0, 0), Vector3(1, 0, 0), Vector3(0, 1, 0) });
	tri->SetVertexColours(
		{ Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), Vector4(0, 0, 1, 1) });
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();

	for (int y = 0; y < 5; ++y) {
		for (int x = 0; x < 5; ++x) {
			Matrix4 translate = Matrix4::Translation(
				Vector3((x + 1) * 130, (y + 1) * 120, 0));
			Matrix4 rotate = Matrix4::Rotation(
				((y * 5) + x) * 10, Vector3(0, 0, 1));
			Matrix4 scale = Matrix4::Scale(Vector3(50, 50, 50) / (1 + y));
			Matrix4 modelMat = translate * rotate * scale;

			renderer.AddRenderObject(new RenderObject(tri, modelMat));
		}
	}
}

// tutorial 2
void Tutorial2_1(Renderer& renderer) {
	//Normal OpenGL mesh in top left
	std::vector<Vector3> linePos = { Vector3(150, 50, 0), Vector3(180, 80, 0), Vector3(100, 200, 0), Vector3(150, 150, 0) };
	std::vector<Vector4> lineCol = { Vector4(1, 0, 0, 1), Vector4(0, 0, 1, 1),  Vector4(0, 0, 1, 1),  Vector4(0, 1, 0, 1) };
	OGLMesh* lines = new OGLMesh();
	lines->SetVertexPositions(linePos);
	lines->SetVertexColours(lineCol);
	lines->SetPrimitiveType(GeometryPrimitive::Lines);
	lines->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(lines));

	//point simulation (line)
	OGLMesh* rasterLine = (OGLMesh*)RasterisationMesh::CreateLineFromPoints(linePos, lineCol, false);
	renderer.AddRenderObject(new RenderObject(rasterLine));


	//Norrmal OpenGL mesh in top right
	std::vector<Vector3> triPos = { Vector3(650, 100, 0), Vector3(550, 200, 0), Vector3(750, 200, 0), };
	std::vector<Vector4> triCol = { Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), Vector4(0, 0, 1, 1) };
	OGLMesh* tris = new OGLMesh();
	tris->SetVertexPositions(triPos);
	tris->SetVertexColours(triCol);
	tris->SetPrimitiveType(GeometryPrimitive::Triangles);
	tris->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(tris));

	//point simulation (tri)
	OGLMesh* rasterTri = (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints(triPos, triCol, 0);
	renderer.AddRenderObject(new RenderObject(rasterTri));



	
	//point simulation (triangle)
}

// tutorial 1
void Tutorial1_1(Renderer& renderer) {
	//draw points
	OGLMesh* points = new OGLMesh();
	points->SetVertexPositions({ Vector3(50, 50,0), Vector3(30, 10, 0), Vector3(200, 70, 0) });
	points->SetPrimitiveType(GeometryPrimitive::Points);
	points->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(points));

	//draw lines
	OGLMesh* lines = new OGLMesh();
	lines->SetVertexPositions({ Vector3(600, 50, 0), Vector3(680, 180, 0), Vector3(680, 50, 0), Vector3(600, 180, 0) });
	lines->SetPrimitiveType(GeometryPrimitive::Lines);
	lines->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(lines));

	//draw triangles
	OGLMesh* tris = new OGLMesh();
	tris->SetVertexPositions({ Vector3(50, 450, 0), Vector3(250, 450, 0), Vector3(150, 350, 0) });
	tris->SetPrimitiveType(GeometryPrimitive::Triangles);
	tris->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(tris));

	//draw Triangle Strips
	OGLMesh* triStrip = new OGLMesh();

	triStrip->SetVertexPositions({ Vector3(600, 450, 0), Vector3(700, 450, 0), Vector3(650, 350, 0) });
	triStrip->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	triStrip->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(triStrip));
}

void Tutorial1_2(Renderer& renderer) {
	//draw trianglefan
	OGLMesh* points = new OGLMesh();
	points->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	points->SetVertexPositions({ Vector3(350, 350, 0), Vector3(350, 300, 0), Vector3(385, 325, 0), Vector3(385, 375, 0), Vector3(350, 400, 0), Vector3(315, 375, 0), Vector3(315, 325, 0), Vector3(350, 300, 0) });
	points->UploadToGPU();
	Matrix4 mat = Matrix4::Scale(Vector3(0.2, 0.2, 0));

	renderer.AddRenderObject(new RenderObject(points, mat));

}

// TEST PLACE
void Tutorial_a(Renderer& renderer, int num=1000) {
	OGLMesh* sphere = new OGLMesh("sphere.msh");
	sphere->SetPrimitiveType(GeometryPrimitive::Triangles);
	sphere->UploadToGPU();
	for (int i = 0; i < num; i++) {
		Vector3 pos;
		pos.x = rand() % 200 - 100;
		pos.y = rand() % 200 - 100;
		pos.z = -( rand() % 300 - 50 );

		float size;
		size = 0.2 * (rand() % 3);
		Matrix4 mat = Matrix4::Translation(pos) * Matrix4::Scale(Vector3(size, size, size));
		renderer.AddRenderObject(new RenderObject(sphere, mat));
	}
}

void Tutorial_b(Renderer& renderer) {
	OGLMesh* cube = new OGLMesh("cube.msh");
	cube->SetPrimitiveType(GeometryPrimitive::Triangles);
	cube->UploadToGPU();
	renderer.AddRenderObject(new RenderObject(cube));

	for(int i = 1; i < 3; i++) {
		Matrix4 translation = Matrix4::Translation(Vector3(0, 0, 50 * -i));
		renderer.AddRenderObject(new RenderObject(cube, translation));
	}
}

void Tutorial_c(Renderer& renderer) {
	OGLMesh* point = new OGLMesh();
	point->SetVertexPositions({ Vector3(0, 0, 0) });
	point->SetVertexColours({ Vector4(1, 0, 0, 0) });
	point->SetPrimitiveType(GeometryPrimitive::Points);
	point->UploadToGPU();
	
	Matrix4 mat = Matrix4::Translation(Vector3(50, 50, 0));
	
	renderer.AddRenderObject(new RenderObject(point,mat));
}

int main() {

	
	Window*w = Window::CreateGameWindow("CSC3223 Tutorials!");

	// camera position translation
	Vector3 viewPosition(0, 0, 0); // default view postition
	Vector3 viewRotation(0, 0, 0);

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer*	renderer = new Renderer(*w);
	// tutorial 6
	// renderer->EnableDepthBuffer(true);

	// tutorial 1: set meshes mode
	// renderer->SetPolygonMode(GL_FILL);

	// tutorial 5
	float aspect = w->GetScreenAspect();
	Matrix4 proj = Matrix4::Perspective(1.0f, 200.0f, aspect, 45.0f);
	float currentWidth = Window::GetWindow()->GetScreenSize().x;
    float currentHeight = Window::GetWindow()->GetScreenSize().y;
	Matrix4 mat = Matrix4::Orthographic(-1.0f, 2.0f, - currentWidth * 0.5f, currentWidth * 0.5f,
	currentHeight * 0.5f, -currentHeight * 0.5f);
	// renderer->SetProjectionMatrix(proj);

	// tutorial tasks call
	Tutorial9(*renderer);

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTotalTimeMSec();
		renderer->Update(time);
		renderer->DrawString("B9052919 Ryota Fuwa", Vector2(10, 10));

		// tutorial 8
		// renderer->EnableAlphaBlending(false);
		// renderer->SetBlendToInvert();



		renderer->Render();

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}

		// translation
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_I)) {
			viewPosition.z += 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_N)) {
			viewPosition.z -= 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_H)) {
			viewPosition.x += 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_L)) {
			viewPosition.x -= 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_J)) {
			viewPosition.y += 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_K)) {
			viewPosition.y -= 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
			viewRotation.z += 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F)) {
			viewRotation.z -= 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
			viewRotation.x += 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
			viewRotation.x -= 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_R)) {
			viewRotation.y += 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_B)) {
			viewRotation.y -= 0.5f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_BACK)) {
			viewPosition = Vector3(0, 0, 0);
			viewRotation = Vector3(0, 0, 0);
		}

		// mouse movement
		if (Window::GetMouse()->ButtonDown(MOUSE_LEFT)) {
			Vector2 direc = Window::GetMouse()->GetRelativePosition();
			viewPosition.x -= direc.x;
			viewPosition.y += direc.y;
		}
		if (Window::GetMouse()->ButtonDown(MOUSE_RIGHT)) {
			Vector2 direc = Window::GetMouse()->GetRelativePosition();
			viewRotation.x += direc.y;
			viewRotation.y -= direc.x;
		}
		if (Window::GetMouse()->WheelMoved()) {
			viewPosition.z += 3 * Window::GetMouse()->GetWheelMovement();
		}

		float rotationAbs = viewRotation.Length();
		renderer->SetViewMatrix(Matrix4::Rotation(rotationAbs, viewRotation) * Matrix4::Translation(viewPosition));

		w->SetTitle(std::to_string(time * 1000));

	}
	delete renderer;
	Window::DestroyGameWindow();
	return 0;
}