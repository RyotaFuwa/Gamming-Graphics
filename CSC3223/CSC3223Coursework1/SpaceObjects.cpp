#include "SpaceObjects.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector3.h"
#include "../../Common/Matrix4.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "RenderObject.h"

namespace NCL {
	namespace CSC3223 {
		using namespace NCL::Maths;

		Planet2D::Planet2D(PLANET p, Vector3 pos, Vector3 size)
		{
			meshOwner = true;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size);

			std::vector<Vector3> vertexPos;
			std::vector<Vector4> vertexCol;
			std::vector<Vector2> planetUvCoords;
			float step = 3.14159265 / 12;
			for (int i = 0; i < 13; i++) {
				vertexPos.push_back(Vector3(std::cos(step * i), std::sin(step * i), 0));
				vertexPos.push_back(Vector3(std::cos(step * i), -std::sin(step * i), 0));

				vertexCol.push_back(Vector4(1, 1, 1, 1));
				vertexCol.push_back(Vector4(1, 1, 1, 1));

				planetUvCoords.push_back(Vector2(0.5 * std::cos(step * i) + 0.5, 0.5 * std::sin(step * i) + 0.5));
				planetUvCoords.push_back(Vector2(0.5 * std::cos(step * i) + 0.5, -0.5 * std::sin(step * i) + 0.5));
			}
			mesh = new OGLMesh();
			mesh->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
			mesh->SetVertexPositions(vertexPos);
			mesh->SetVertexColours(vertexCol);
			mesh->SetVertexTextureCoords(planetUvCoords);
			mesh->UploadToGPU();
			switch(p) {
					MOON: SetBaseTexture(OGLTexture::RGBATextureFromFilename("moon.png")); break;
					SUN: SetBaseTexture(OGLTexture::RGBATextureFromFilename("sun.png")); break;
					JUPYTER: SetBaseTexture(OGLTexture::RGBATextureFromFilename("jupyter.png")); break;
					// AURORA: SetBaseTexture(OGLTexture::RGBATextureFromFilename("aurora.png")); break;
					// BLACK: SetBaseTexture(OGLTexture::RGBATextureFromFilename("black.png")); break;
					default: break;
			}
		}

		/*
		Planet2D::Planet2D(const Planet2D& copy, Vector3 pos, Vector3 size)
		{
			meshOwner = false;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size);
			this->mesh = copy.mesh;

			texture = copy.GetBaseTexture();
		}
		*/

		Planet2D::~Planet2D()
		{
			if (meshOwner)
				delete mesh;
		}

		Planet3D::Planet3D(PLANET p, Vector3 pos, Vector3 size)
		{
			meshOwner = true;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size);

			mesh = new OGLMesh();
			mesh->SetPrimitiveType(GeometryPrimitive::Triangles);
			mesh->UploadToGPU();
			switch(p) {
			MOON: SetBaseTexture(OGLTexture::RGBATextureFromFilename("moon.png")); break;
			SUN: SetBaseTexture(OGLTexture::RGBATextureFromFilename("sun.png")); break;
			JUPYTER: SetBaseTexture(OGLTexture::RGBATextureFromFilename("jupyter.png")); break;
			// AURORA: SetBaseTexture(OGLTexture::RGBATextureFromFilename("aurora.png")); break;
			// BLACK: SetBaseTexture(OGLTexture::RGBATextureFromFilename("black.png")); break;
			default: break;
			}
		}

		Planet3D::Planet3D(const Planet3D& copy, Vector3 pos, Vector3 size)
		{
			meshOwner = false;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size);
			this->mesh = copy.mesh;

			texture = copy.GetBaseTexture();
		}

		Planet3D::~Planet3D()
		{
			if (meshOwner)
				delete mesh;
		}

		SpaceDust2D::SpaceDust2D(Vector3 pos)
		{
			meshOwner = true;
			transform = Matrix4::Translation(pos);
			mesh = new OGLMesh();
			mesh->SetPrimitiveType(GeometryPrimitive::Points);
			mesh->SetVertexPositions({ Vector3(0, 0, 0) });
			mesh->SetVertexColours({ Vector4(1, 1, 1, 1) });
			mesh->UploadToGPU();
		}

		SpaceDust2D::SpaceDust2D(const SpaceDust2D& copy, Vector3 pos)
		{
			meshOwner = false;
			transform = Matrix4::Translation(pos);
			this->mesh = copy.mesh;
		}

		SpaceDust2D::~SpaceDust2D()
		{
			if (meshOwner)
				delete mesh;
		}

		SpaceDust3D::SpaceDust3D(Vector3 pos, Vector3 size)
		{
			meshOwner = false;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size);
			mesh = new OGLMesh();
			mesh->SetPrimitiveType(GeometryPrimitive::Triangles);
			mesh->UploadToGPU();
		}

		SpaceDust3D::SpaceDust3D(const SpaceDust3D& copy, Vector3 pos, Vector3 size)
		{
			meshOwner = false;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size);
			this->mesh = copy.mesh;

			texture = copy.GetBaseTexture();
		}

		SpaceDust3D::~SpaceDust3D()
		{
			if (meshOwner)
				delete mesh;
		}

		Rock2D::Rock2D(NCL::CSC3223::COLOUR col, Vector3 pos, Vector3 size, Vector3 rot)
		{
			meshOwner = true;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size) * Matrix4::Rotation(rot.z, Vector3(0, 0, rot.z));
			mesh = new OGLMesh();
			mesh->SetPrimitiveType(GeometryPrimitive::TriangleFan);
			mesh->SetVertexPositions(fanPos);
			vector<Vector4> vertexCols;
			for (unsigned int i = 0; i != fanPos.size(); i++) {
				vertexCols.push_back(colourVec[col]);
			}
			mesh->SetVertexColours(vertexCols);
			mesh->SetVertexIndices(fanIndices);

		}

		Rock2D::Rock2D(const Rock2D& copy, Vector3 pos, Vector3 size, Vector3 rot)
		{
			meshOwner = false;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size) * Matrix4::Rotation(rot.z, Vector3(0, 0, rot.z));
			this->mesh = copy.mesh;
		}

		Rock2D::~Rock2D()
		{
			if (meshOwner)
				delete mesh;
		}

		RandomRock::RandomRock(Vector3 pos, Vector3 size, Vector3 rot)
		{
			meshOwner = true;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size) * Matrix4::Rotation(rot.z, Vector3(0, 0, rot.z));

			std::vector<Vector3> vertexPos = { Vector3(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0), Vector3(-rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0),
				Vector3(-rand() % 10 / 10.0, -rand() % 10 / 10.0, rand() % 10 / 10.0), Vector3(rand() % 10 / 10.0, -rand() % 10 / 10.0, rand() % 10 / 10.0),
				Vector3(-rand() % 10 / 10.0, -rand() % 10 / 10.0, rand() % 10 / 10.0), Vector3(-rand() % 10 / 10.0, rand() % 10 / 10.0, -rand() % 10 / 10.0),
				Vector3(-rand() % 10 / 10.0, -rand() % 10 / 10.0, -rand() % 10 / 10.0), Vector3(rand() % 10 / 10.0, -rand() % 10 / 10.0, -rand() % 10 / 10.0) };
			std::vector<unsigned int> vertexIndices = {
				0, 1, 2, 0, 3, 2, // front
				0, 4, 5, 0, 1, 5, // upper
				3, 7, 6, 3, 2, 6, // bottom
				4, 5, 6, 4, 7, 6, // back
				3, 0, 4, 3, 7, 4, // right side
				5, 1, 2, 5, 6, 2 }; // left side
			std::vector<Vector4> vertexCols;
			for (int i = 0; i < vertexPos.size(); i++) {
				// make it look brown
				float rValue = rand() % 50 / 100.0 + 0.4;
				float gValue = rand() % 30 / 100.0 + 0.1;
				float bValue = rand() % 20 / 100.0;
				vertexCols.push_back(Vector4(rValue, gValue, bValue, 1.0));
			}

			mesh = new OGLMesh();
			mesh->SetPrimitiveType(GeometryPrimitive::Triangles);
			mesh->SetVertexPositions(vertexPos);
			mesh->SetVertexIndices(vertexIndices);
			mesh->SetVertexColours(vertexCols);
			mesh->UploadToGPU();
		}

		RandomRock::RandomRock(const RandomRock& copy, Vector3 pos, Vector3 size, Vector3 rot)
		{
			meshOwner = false;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size) * Matrix4::Rotation(rot.z, Vector3(0, 0, rot.z));
			this->mesh = copy.mesh;

		}

		RandomRock::~RandomRock()
		{
			if (meshOwner)
				delete mesh;
		}

		SpaceShip::SpaceShip(Vector3 pos, Vector3 size, Vector3 rot)
		{
			meshOwner = true;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size) * Matrix4::Rotation(rot.z, Vector3(0, 0, rot.z));

			mesh = new OGLMesh();
			mesh->SetPrimitiveType(GeometryPrimitive::Triangles);
			mesh->SetVertexPositions({ Vector3(0, 0.15, 0), Vector3(0, 2, 0), Vector3(-1, 0, 0), Vector3(1, 0, 0), Vector3(0, 0, -0.75) });
			mesh->SetVertexColours({ Vector4(0, 0, 1, 1), Vector4(0, 0, 1, 1), Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), Vector4(0.75, 0.75, 1, 1) });
			mesh->SetVertexIndices({ 0, 2, 1, 0, 3, 1, 0, 4, 1 });
			mesh->UploadToGPU();

		}

		SpaceShip::SpaceShip(const SpaceShip& copy, Vector3 pos, Vector3 size, Vector3 rot)
		{
			meshOwner = false;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size) * Matrix4::Rotation(rot.z, Vector3(0, 0, rot.z));
			this->mesh = copy.mesh;
		}

		SpaceShip::~SpaceShip()
		{
			if (meshOwner)
				delete mesh;
		}

	}
}
