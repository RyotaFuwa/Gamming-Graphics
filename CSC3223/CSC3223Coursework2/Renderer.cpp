#include "Renderer.h"
#include "Tools.h"

#include "../../Common/TextureWriter.h"
#include "../../Common/Maths.h"
#include "../../Common/Matrix3.h"
using namespace NCL;
using namespace Rendering;
using namespace CSC3223;
using namespace CW2Tools;

Renderer::Renderer(Window& w) : OGLRenderer(w)
{
	defaultShader = new OGLShader("rasterisationVert.glsl", "rasterisationFrag.glsl");
	projMatrix = Matrix4::Orthographic(-10.0f, 100.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer::~Renderer()
{
	delete defaultShader;
}

void Renderer::RenderFrame(float time) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	OGLShader* activeShader = nullptr;

	int modelLocation = 0;

	for (RenderObject* object : renderObjects) {  // why are renderobject not allowed to be modified?
		object->SetTime(time);

		OGLShader* objectShader = (OGLShader*)object->GetShader();
		if (!object->GetMesh()) {
			continue;
		}

		if (object->GetDynamic()) { //move each object dynamically here
			object->Move();
		}

		if (objectShader == nullptr) {
			objectShader = defaultShader;
		}

		if (objectShader != activeShader) {
			activeShader = objectShader;
			BindShader(activeShader);

			// transformation
			int projLocation = glGetUniformLocation(activeShader->GetProgramID(), "projMatrix");
			int viewLocation = glGetUniformLocation(activeShader->GetProgramID(), "viewMatrix");
			modelLocation = glGetUniformLocation(activeShader->GetProgramID(), "modelMatrix");
			glUniformMatrix4fv(projLocation, 1, false, (float*)& projMatrix);
			glUniformMatrix4fv(viewLocation, 1, false, (float*)& viewMatrix);

			// light
			ApplyLightToShader(activeLight, activeShader->GetProgramID());
			Matrix3 rotation = Matrix3(viewMatrix);
			Vector3 invCamPos = viewMatrix.GetPositionVector();
			Vector3 camPos = rotation * -invCamPos;
			glUniform3fv(glGetUniformLocation(
				activeShader->GetProgramID(), "cameraPos"), 1, (float*)& camPos);
		}
		// other uniform variables
		object->AddUniforms(activeShader->GetProgramID());

		Matrix4 mat = object->GetTransform();
		glUniformMatrix4fv(modelLocation, 1, false, (float*)& mat);

		// texture
		int i = 0;
		for (VarTexture vt : object->GetTextures()) {
			BindTextureToShader(vt.tex, vt.var, i);
			i++;
		}

		BindMesh(object->GetMesh());
		DrawBoundMesh();
	}
}

void Renderer::SetLightProperties(Vector3 pos, Vector3 colour, float radius)
{
	activeLight.position = pos;
	activeLight.colour = colour;
	activeLight.radius = radius;
}

void NCL::CSC3223::Renderer::ApplyLightToShader(const Light& l, const int programID)
{

	glUniform3fv(glGetUniformLocation(
		programID, "lightColour"), 1, (float*)& l.colour);
	glUniform3fv(glGetUniformLocation(
		programID, "lightPos"), 1, (float*)& l.position);
	glUniform1f(glGetUniformLocation(
		programID, "lightRadius"), l.radius);
}

void Renderer::OnWindowResize(int w, int h) {
	OGLRenderer::OnWindowResize(w, h);
	projMatrix = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}