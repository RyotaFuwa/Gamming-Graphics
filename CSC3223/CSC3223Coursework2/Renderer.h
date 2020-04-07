#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "RenderObject.h"
#include "../../Common/Vector2.h"

namespace NCL {
	namespace CSC3223 {

		struct Light {
			Vector3 position;
			float radius;
			Vector3 colour;
		};

		class Renderer : public OGLRenderer
		{
		public:
			Renderer(Window& w);
			~Renderer();

			void AddRenderObject(RenderObject* ro) {
				renderObjects.emplace_back(ro);
			}

			void DeleteAllRenderObjects() {
				for (const RenderObject* object : renderObjects) {
					delete object;
				}
				renderObjects.clear();
			}

			void SetProjectionMatrix(const Matrix4& m) {
				projMatrix = m;
			}

			void SetViewMatrix(const Matrix4& m) {
				viewMatrix = m;
			}

			void EnableLight(bool state) {
				light = state;
			}

			void SetLightProperties(Vector3 pos, Vector3 colour, float radius);


		protected:
			void ApplyLightToShader(const Light& l, const int programID);
			void RenderNode(RenderObject* root);
			void OnWindowResize(int w, int h)	override;
			void RenderFrame(float time)	override;
			OGLShader* defaultShader;
			Matrix4		projMatrix;
			Matrix4		viewMatrix;
			vector<RenderObject*> renderObjects;

			bool light = true;
			Light activeLight;
			GameTimer frameTimer;
			float time = 0.0f;


		};
	}
}

