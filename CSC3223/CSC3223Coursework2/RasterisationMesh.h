#pragma once
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

namespace NCL {
	namespace CSC3223 {
		class RasterisationMesh : public Rendering::OGLMesh {
		public:
			static RasterisationMesh* CreateTriangleFormPoints(
				const std::vector<Vector3>& vertices, int type = false);
			static RasterisationMesh* CreateLineFromPoints(
				const std::vector<Vector3>& vertices, bool bresenham = false);
		protected:
			void RasterLineEquationTriangle(
				const Vector3& p0, const Vector3& p1, const Vector3& p2);
			void RasterSpanTriangle(
				const Vector3 & p0, const Vector3& p1, const Vector3& p2);
			
		    void RasterBasicLine(const Vector3 & p0, const Vector3 & p1);

		    void RasterBresenhamLine(const Vector3 & p0, const Vector3 & p1);
		};
	}
}
