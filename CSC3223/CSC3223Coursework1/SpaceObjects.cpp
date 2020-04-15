#include "SpaceObjects.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector3.h"
#include "../../Common/Matrix4.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "RenderObject.h"
#include "Tools.h";

namespace NCL {
	namespace CSC3223 {
		using namespace NCL::Maths;
		using namespace CW1Tools;


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
					case PLANET::MOON: SetBaseTexture(OGLTexture::RGBATextureFromFilename("moon.png")); break;
					case PLANET::SUN: SetBaseTexture(OGLTexture::RGBATextureFromFilename("sun.png")); break;
					case PLANET::JUPYTER: SetBaseTexture(OGLTexture::RGBATextureFromFilename("jupyter.png")); break;
					case PLANET::NEPTUNE: SetBaseTexture(OGLTexture::RGBATextureFromFilename("neptune.png")); break;
					// case PLANET::AURORA: SetBaseTexture(OGLTexture::RGBATextureFromFilename("aurora.png")); break;
					// case PLANET::BLACK: SetBaseTexture(OGLTexture::RGBATextureFromFilename("black.png")); break;
					default: SetBaseTexture(OGLTexture::RGBATextureFromFilename("moon.png")); break;
			}
		}

		Planet2D::Planet2D(const Planet2D& copy, Vector3 pos, Vector3 size)
		{
			meshOwner = false;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size);
			this->mesh = copy.mesh;

			texture = copy.GetBaseTexture();
		}

		Planet2D::~Planet2D()
		{
			if (meshOwner)
				delete mesh;
		}

		Planet3D::Planet3D(PLANET p, Vector3 pos, Vector3 size)
		{
			meshOwner = true;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size);

			mesh = new OGLMesh("sphere.msh");
			mesh->SetPrimitiveType(GeometryPrimitive::Triangles);
			mesh->UploadToGPU();
			switch(p) {
				case PLANET::MOON: SetBaseTexture(OGLTexture::RGBATextureFromFilename("moon.png")); break;
				case PLANET::SUN: SetBaseTexture(OGLTexture::RGBATextureFromFilename("sun.png")); break;
				case PLANET::JUPYTER: SetBaseTexture(OGLTexture::RGBATextureFromFilename("jupyter.png")); break;
				// case PLANET::AURORA: SetBaseTexture(OGLTexture::RGBATextureFromFilename("aurora.png")); break;
				// case PLANET::BLACK: SetBaseTexture(OGLTexture::RGBATextureFromFilename("black.png")); break;
				default: SetBaseTexture(OGLTexture::RGBATextureFromFilename("moon.png")); break;
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
			meshOwner = true;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size);
			mesh = new OGLMesh("sphere.msh");
			mesh->UploadToGPU();
		}

		SpaceDust3D::SpaceDust3D(const SpaceDust3D& copy, Vector3 pos, Vector3 size)
		{
			meshOwner = false;
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size);
			this->mesh = copy.mesh;
		}

		SpaceDust3D::~SpaceDust3D()
		{
			if (meshOwner)
				delete mesh;
		}

		Rock2D::Rock2D(NCL::CSC3223::COLOUR col, Vector3 pos, Vector3 size, Vector3 rot)
		{
			const std::vector<Vector3> fanPos = { Vector3(0, 0, 0), Vector3(0.8, 0.2, 0), Vector3(0.3, 0.6, 0),
			Vector3(-0.2, 0.9, 0) , Vector3(-0.8, 0.5, 0), Vector3(-rand() % 10 / 10.0, -rand() % 10 / 10.0, 0),
			Vector3(0.4, -0.6, 0), Vector3(0.8, -0.5, 0) };
			const std::vector<unsigned int> fanIndices = { 0, 1, 2, 3, 4, 5, 6, 7, 1 };
			const std::vector<Vector4> colourVec = {
			Vector4(1, 0.1, 0.5, 1.0),
			Vector4(1, 1, 0, 1.0),
			Vector4(0, 0.66, 1, 1.0),
			Vector4(0.5, 0.15, 0.15, 1.0)
			};

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
			mesh->UploadToGPU();
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

			std::vector<Vector3> vertexPos = { 
				Vector3(rand() % 5 / 10.0 + 0.5, rand() % 5 / 10.0 + 0.5, rand() % 5 / 10.0 + 0.5),
				Vector3(-1 * (rand() % 5 / 10.0 + 0.5), rand() % 5 / 10.0 + 0.5, rand() % 5 / 10.0 + 0.5),
				Vector3(-1 * (rand() % 5 / 10.0 + 0.5), -1 * (rand() % 5 / 10.0 + 0.5), rand() % 5 / 10.0 + 0.5),
				Vector3(rand() % 5 / 10.0 + 0.5, -1 * (rand() % 5 / 10.0 + 0.5), rand() % 5 / 10.0 + 0.5),
				Vector3(rand() % 5 / 10.0 + 0.5, rand() % 5 / 10.0 + 0.5, -1 * (rand() % 5 / 10.0 + 0.5)), 
				Vector3(-1 * (rand() % 5 / 10.0 + 0.5), rand() % 5 / 10.0 + 0.5, -1 * (rand() % 5 / 10.0 + 0.5)),
				Vector3(-1 * (rand() % 5 / 10.0 + 0.5), -1 * (rand() % 5 / 10.0 + 0.5), -1 * (rand() % 5 / 10.0 + 0.5)),
				Vector3(rand() % 5 / 10.0 + 0.5, -1 * (rand() % 5 / 10.0 + 0.5), -1 * (rand() % 5 / 10.0 + 0.5))
			};

			typedef std::vector<unsigned int> Indices;
			std::vector<Indices> surfaceIndices;
			surfaceIndices.push_back(Indices{ 0, 1, 2, 4 }); // front
			surfaceIndices.push_back(Indices{ 1, 5, 6, 2 }); // left
			surfaceIndices.push_back(Indices{ 5, 4, 7, 6 }); // rear
			surfaceIndices.push_back(Indices{ 4, 0, 3, 7 }); // right
			surfaceIndices.push_back(Indices{ 6, 7, 3, 2 }); // bottom
			surfaceIndices.push_back(Indices{ 0, 4, 5, 1 }); // top

			std::vector<Vector3> centers;
			for (Indices is : surfaceIndices) {
				std::vector<Vector3> surface;
				for (unsigned int i : is) {
					surface.push_back(vertexPos[i]);
				}
				centers.push_back(GetCentroidVector(surface) + GetSurfaceVector(surface) * (rand() % 10 / 10.0 + 0.25));
			}
			vertexPos.insert(vertexPos.end(), centers.begin(), centers.end());

			std::vector<unsigned int> vertexIndices = {
				0, 1, 8, 1, 2, 8, 2, 3, 8, 0, 3, 8,     // front
				5, 1, 9, 5, 6, 9, 6, 2, 9, 2, 1, 9,     // left
				4, 5, 10, 5, 6, 10, 6, 7, 10, 7, 4, 10, // rear 
				4, 0, 11, 0, 3, 11, 3, 7, 11, 7, 4, 11, // right
				7, 6, 12, 6, 2, 12, 2, 3, 12, 3, 7, 12, // bottom
				4, 5, 13, 5, 1, 13, 1, 0, 13, 0, 4, 13  // top
			};
				
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
			transform = Matrix4::Translation(pos) * Matrix4::Scale(size) * Matrix4::Rotation(rot.Length(), rot);

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
