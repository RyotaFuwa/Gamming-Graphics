#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "RenderObject.h"
#include "../../Common/Vector2.h"


namespace NCL {
	using namespace Maths;
	namespace CSC3223 {

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
			
			void SetProjectionMatrix(const Matrix4&m) {
				projMatrix = m;
			}

			void SetViewMatrix(const Matrix4&m) {
				viewMatrix = m;
			}

			void SetPolygonMode(GLenum mode) {
				glPolygonMode(GL_FRONT_AND_BACK, mode);
			}

            // added in tutorial 6
			void EnableDepthBuffer(bool state) {
				if (state) {
					glEnable(GL_DEPTH_TEST);
				}
				else {
					glDisable(GL_DEPTH_TEST);
				}
			}
			void WriteDepthBuffer(const string& filepath) const;

			// added in tutorial 7
			void EnableBilinearFiltering(OGLTexture& t);
			void EnableMipMapFiltering(OGLTexture& t);
			void EnableTextureRepeating(OGLTexture& t, bool uRepeat, bool vRepeat);

			// added in tutorial 8
			void EnableAlphaBlending(bool state) {
				if (state) {
					glEnable(GL_BLEND);
				}
				else {
					glDisable(GL_BLEND);
				}
			}

		
			void SetBlendToLinear() {
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			void SetBlendToAdditive() {
				glBlendFunc(GL_ONE, GL_ONE);
			}
			void SetBlendToInvert() {
				glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
			}

		protected:
			void RenderNode(RenderObject* root);
	
			void OnWindowResize(int w, int h)	override;

			void RenderFrame(float dt)	override;
			OGLShader*		defaultShader;

			Matrix4		projMatrix;
			Matrix4		viewMatrix;
			GameTimer frameTimer;

			vector<RenderObject*> renderObjects;
		};
	}
}

