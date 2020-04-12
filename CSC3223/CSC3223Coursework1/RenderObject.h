#pragma once
#include <vector>
#include <map>

#include "../../Common/Vector3.h"
#include "../../Common/Matrix4.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Common/ShaderBase.h"


namespace NCL {
	using namespace NCL::Rendering;

	class MeshGeometry;
	namespace CSC3223 {
		using namespace Maths;

		class RenderObject
		{
		public:
			RenderObject();
			RenderObject(MeshGeometry* mesh, Matrix4 m = Matrix4());
			virtual ~RenderObject();

			MeshGeometry*		GetMesh() const {
				return mesh;
			}

			void  SetTransform(Matrix4 mat) {
				transform = mat;
			}

			Matrix4 GetTransform() const {
				return transform;
			}

			void SetBaseTexture(TextureBase* t) {
				texture = t;
			}

			TextureBase* GetBaseTexture() const {
				return texture;
			}


			void SetShader(ShaderBase* s) {
				shader = s;
			}

			ShaderBase* GetShader() const {
				return shader;
			}

		protected:
			MeshGeometry*	mesh;
			TextureBase*	texture;
			ShaderBase*		shader;
			Matrix4			transform;
		};
	}
}

