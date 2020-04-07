#pragma once
#include <vector>
#include <map>

#include "../../Common/Vector3.h"
#include "../../Common/Matrix4.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Common/ShaderBase.h"

#include "Tools.h"


namespace NCL {
	using namespace NCL::Rendering;
	class MeshGeometry;
	namespace CSC3223 {
		using namespace Maths;
		using namespace CW2Tools;

		class RenderObject
		{
		public:
			RenderObject();
			RenderObject(MeshGeometry* mesh, Matrix4 m = Matrix4());
			~RenderObject();

			void SetMesh(MeshGeometry* mesh) {
				this->mesh = mesh;
			}

			MeshGeometry* GetMesh() const {
				return mesh;
			}

			void SetTransform(Matrix4 mat) {
				transform = mat;
			}

			Matrix4 GetTransform() const {
				return transform;
			}

			void AddTexture(const VarTexture& vt) {
				textures.push_back(vt);
			}

			std::vector<VarTexture> GetTextures() const {
				return textures;
			}


			void SetShader(OGLShader* s) {
				shader = s;
			}

			ShaderBase* GetShader() const {
				return shader;
			}

			void SetTime(float t) {
				time = t;
			}

			float GetTime() {
				return time;
			}

			void SetDynamic(bool state) {
				dynamic = state;
			}

			bool GetDynamic() const {
				return dynamic;
			}

			virtual void Move() {}
			virtual void AddUniforms(const int programID) {}

		protected:
			bool createdInside = false;
			MeshGeometry* mesh;
			std::vector<VarTexture> textures;
			OGLShader* shader;
			Matrix4			transform;

			float time = 0.0f;
			float lastTime = 0.0f;
			bool dynamic = false;
		};
	}
}

