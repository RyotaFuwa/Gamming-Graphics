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
#include "Cube.h"
#include "SpaceDusts.h"
#include "Tools.h"

using namespace NCL;
using namespace CSC3223;
using namespace CW2Tools;

void BasicCube(Renderer& renderer) {
	Cube* cubeBasic1 = new Cube(BASIC1);

	ShaderBundle sbBasic1;
	sbBasic1.vert = "CW2Basic1Vert.glsl";
	sbBasic1.frag = "CW2Basic1Frag.glsl";
	OGLShader* s = new OGLShader(sbBasic1);
	cubeBasic1->SetShader(s);

	VarTexture cleanBubble("cleanBubble", "bubbleClean.png");
	VarTexture dirtyBubble("dirtyBubble", "bubbleDirty.png");
	cubeBasic1->AddTexture(cleanBubble);
	cubeBasic1->AddTexture(dirtyBubble);
	cubeBasic1->SetDynamic(true);

	renderer.AddRenderObject(cubeBasic1);
	renderer.EnableLight(false);
}

void Advanced1Cube(Renderer& renderer) {
	Cube* cubeAdvanced1 = new Cube(ADVANCED1);

	ShaderBundle sbAdvanced1;
	sbAdvanced1.vert = "CW2Advanced1Vert.glsl";
	sbAdvanced1.frag = "CW2Advanced1Frag.glsl";
	sbAdvanced1.geom = "CW2Advanced1Geom.glsl";
	OGLShader* s = new OGLShader(sbAdvanced1);
	cubeAdvanced1->SetShader(s);

	VarTexture magma1("magma1", "magma1.png");
	cubeAdvanced1->AddTexture(magma1);

	cubeAdvanced1->SetDynamic(true);
	renderer.AddRenderObject(cubeAdvanced1);
	renderer.SetLightProperties(Vector3(0, 0, 0), Vector3(0.10f, 0.0f, 0.0f), 200.0f);
}

void Advanced2Cube(Renderer& renderer) {
	OGLMesh* mesh = new OGLMesh("cube.msh");
	mesh->SetPrimitiveType(GeometryPrimitive::Patches);
	mesh->UploadToGPU();

	GLint maxVerticesNum = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxVerticesNum);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	Cube* cubeAdvanced2 = new Cube(mesh);
	cubeAdvanced2->SetCubePattern(ADVANCED2);

	ShaderBundle sbAdvanced2;
	sbAdvanced2.vert = "CW2Advanced2Vert.glsl";
	sbAdvanced2.tessCtrl = "CW2Advanced2Ctrl.glsl";
	sbAdvanced2.tessEval = "CW2Advanced2Eval.glsl";
    sbAdvanced2.frag = "CW2Advanced2Frag.glsl";
	OGLShader* s = new OGLShader(sbAdvanced2);
	cubeAdvanced2->SetShader(s);

	VarTexture chessBoard("chessBoard", "chessBoard.png");
	cubeAdvanced2->AddTexture(chessBoard);
	cubeAdvanced2->SetDynamic(true);
	renderer.AddRenderObject(cubeAdvanced2);
	renderer.EnableLight(false);
}

void Advanced3Cube(Renderer& renderer) {
	OGLMesh* meshAdvanced3 = new OGLMesh("cube2.msh");
	meshAdvanced3->UploadToGPU();
	OGLMesh* points = new OGLMesh();
	points->SetPrimitiveType(GeometryPrimitive::Points);
	points->SetVertexPositions({ Vector3(0, 0, 0) });
	points->SetVertexColours({ Vector4(1, 1, 1, 0.8) });
	points->SetVertexNormals({ Vector3(0, -1, 0) });
	points->UploadToGPU();

	ShaderBundle sbAdvanced3;
	sbAdvanced3.vert = "CW2Advanced3Vert.glsl";
	sbAdvanced3.frag = "CW2Advanced3Frag.glsl";
	OGLShader* s3 = new OGLShader(sbAdvanced3);
	ShaderBundle sbForSpaceDusts;
	sbForSpaceDusts.vert = "CW2SpaceDustsVert.glsl";
	sbForSpaceDusts.frag = "CW2SpaceDustsFrag.glsl";
	sbForSpaceDusts.geom = "CW2SpaceDustsGeom.glsl";
	OGLShader* ssb = new OGLShader(sbForSpaceDusts);

	VarTexture moon("planet", "moon.png"), sun("planet", "sun.png"),
		jupyter("planet", "jupyter.png"), neptune("planet", "neptune.png");

	for (int i = 0; i < 15; i++) {
		float r			= Rand01();
		float rx		= PlusMinus() * RandBetween(0.2f, 1.0f);
		float ry		= RandBetween(-1.0f, 1.0f);
		float rz        = PlusMinus() * RandBetween(-0.2f, 1.0f);
		Cube* cube		= new Cube(meshAdvanced3);
		cube->SetCubePattern(ADVANCED3);
		Vector3 fp(20.0f * rx, 2.5 * ry, 20.0f * rz);
		cube->SetFirstPosition(fp);
		cube->SetTransform(Matrix4::Translation(fp) * Matrix4::Scale(Vector3(1.20 * r, 1.20 * r, 1.20 * r)));
		cube->SetDynamic(true);
		cube->SetShader(s3);

		int planet = rand() % 4;
		switch (planet) {
		case 0:
			cube->AddTexture(moon);
			break;
		case 1:
			cube->AddTexture(sun);
			break;
		case 2:
			cube->AddTexture(jupyter);
			break;
		case 3:
			cube->AddTexture(neptune);
			break;
		default:
			cube->AddTexture(neptune);
			break;
		}
		renderer.AddRenderObject(cube);
	}

	// star dusts 1
	for (int j = 0; j < 500; j++) {
		SpaceDusts* sd = new SpaceDusts(points);
		sd->SetDynamic(true);
		sd->SetShader(ssb);

		sd->SetAngle(87.50f);
		sd->SetHeight(20.0f);
		sd->EnableFillReversePos(true);
		sd->SetLocation();

		sd->EnableFixedCol(false);
		sd->EnableFillReverseCol(true);
		sd->SetColRange(Vector4(0.25, 0.25, 1.0, 1.0));
		sd->SetColour();

		renderer.AddRenderObject(sd);
	}

	// star dusts 2
	for (int j = 0; j < 1500; j++) {
		SpaceDusts* sd = new SpaceDusts(points);
		sd->SetRotate(2.0f);
		sd->SetDynamic(true);
		sd->SetShader(ssb);

		sd->SetAngle(5.0f);
		sd->SetHeight(150.0f);
		sd->EnableFillReversePos(false);
		sd->SetLocation();

		sd->EnableFixedCol(false);
		sd->EnableFillReverseCol(false);
		sd->SetColRange(Vector4(1.0, 1.0, 1.0, 1.0));
		sd->SetColour();
		
		renderer.AddRenderObject(sd);
	}
}


int main() {
	Window* w = Window::CreateGameWindow("CSC3223 Coursework 2!");
	float cubeLife = 20.0f;

	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer* renderer = new Renderer(*w);
	renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));
	Vector3 viewPosition(0, 0, -5);
	Vector3 viewRotation(0, 0, 0);


	CUBEPATTERN cp = BASIC1;
	BasicCube(*renderer);

	float time = 0.0f;
	float startTime = 0.0f;
	float lastTime = 0.0f;
	float pausedTime = 0.0f;
	bool pause = false;
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {

		if (!pause) {
			time = w->GetTimer()->GetTotalTime() - startTime - pausedTime;
			renderer->Update(time);
		}

		// lights, camera, etc.
		if (time < cubeLife) {
			float colChange = pow((cubeLife - time) / cubeLife, 5);
			float intensity = pow((1 + 2 * time / cubeLife), 3);
			switch (cp) {
			case BASIC1:
				break;
			case ADVANCED1:
				renderer->SetLightProperties(Vector3(0, 0, 0), Vector3(1.0f, colChange, colChange), 100.0f);
				break;
			case ADVANCED2:
				break;
			case ADVANCED3:
				renderer->SetLightProperties(Vector3(0, 0, 0), Vector3(1.0f, 1.0f, 1.0f), 10.0f);

				break;
			default:
				break;
			}
		}


		// predefined from codeBase
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

		// keyboard operations
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_P)) { // pause
			float tmpTime = w->GetTimer()->GetTotalTime();
			if(pause)
			    pausedTime += tmpTime - lastTime;
			else
				lastTime = tmpTime;
			pause = !pause;
		}
		if (pause && Window::GetKeyboard()->KeyPressed(KEYBOARD_0)) { // basic1
			startTime = w->GetTimer()->GetTotalTime();
			renderer->DeleteAllRenderObjects();
			BasicCube(*renderer);
			pausedTime = 0.0f;
			pause = !pause;
			cp = BASIC1;
			viewPosition = Vector3(0, 0, -5);
			viewRotation = Vector3(0, 0, 0);

		}
		if (pause && Window::GetKeyboard()->KeyPressed(KEYBOARD_1)) { // advanced1
			startTime = w->GetTimer()->GetTotalTime();
			renderer->DeleteAllRenderObjects();
			Advanced1Cube(*renderer);
			pausedTime = 0.0f;
			pause = !pause;
			cp = ADVANCED1;
			viewPosition = Vector3(0, 0, -5);
			viewRotation = Vector3(0, 0, 0);
		}
		if (pause && Window::GetKeyboard()->KeyPressed(KEYBOARD_2)) { // advanced2
			startTime = w->GetTimer()->GetTotalTime();
			renderer->DeleteAllRenderObjects();
			Advanced2Cube(*renderer);
			pausedTime = 0.0f;
			pause = !pause;
			cp = ADVANCED2;
			viewPosition = Vector3(0, 0, -5);
			viewRotation = Vector3(0, 0, 0);
		}
		if (pause && Window::GetKeyboard()->KeyPressed(KEYBOARD_3)) { // advanced3
			startTime = w->GetTimer()->GetTotalTime();
			renderer->DeleteAllRenderObjects();
			Advanced3Cube(*renderer);
			pausedTime = 0.0f;
			pause = !pause;
			cp = ADVANCED3;

			renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 60.0f));
			viewPosition = Vector3(0, -2.5, -7.5);
			viewRotation = Vector3(30, 0, 0);
		}

		// mouse movement
		if (Window::GetMouse()->ButtonDown(MOUSE_LEFT)) {
			Vector2 direc = Window::GetMouse()->GetRelativePosition();
			viewPosition.x -= direc.x * 0.5;
			viewPosition.y += direc.y * 0.5;
		}
		if (Window::GetMouse()->ButtonDown(MOUSE_RIGHT)) {
			Vector2 direc = Window::GetMouse()->GetRelativePosition();
			viewRotation.x += direc.y * 0.5;
			viewRotation.y -= direc.x * 0.5;
		}
		if (Window::GetMouse()->WheelMoved()) {
			viewPosition.z += Window::GetMouse()->GetWheelMovement();
		}

		float rotAbs = viewRotation.Length();
		renderer->SetViewMatrix(Matrix4::Rotation(rotAbs, viewRotation) * Matrix4::Translation(viewPosition));
		w->SetTitle(std::to_string(time));

		renderer->Render(time);
	}

	delete renderer;

	Window::DestroyGameWindow();
}

