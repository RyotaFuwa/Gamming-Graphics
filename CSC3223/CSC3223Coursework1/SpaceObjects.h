#pragma once
#include <vector>
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "RenderObject.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

namespace NCL {
	namespace CSC3223 {
		using namespace Maths;
		using namespace Rendering;

		enum PLANET {
			MOON,
			SUN,
			JUPYTER,
			RAINBOW,
			BLACKHOLE,
		};

		enum COLOUR {
			PINK,
			YELLOW,
			BLUE,
			BROWN
		};

		const std::vector<Vector4> colourVec{
			Vector4(1, 0.1, 0.5, 0.5),
			Vector4(1, 1, 0, 0.5),
			Vector4(0, 0.66, 1, 0.5),
			Vector4(0.3, 0.3, 0.3, 0.5)
		};

		class Planet2D : public RenderObject
		{
		public:
			Planet2D(PLANET p, Vector3 pos, Vector3 size);
			// Planet2D(const Planet2D& copy, Vector3 pos, Vector3 size);
			~Planet2D() override;
		private:
			bool meshOwner;
		};


		class Planet3D : public RenderObject
		{
		public:
			Planet3D(PLANET p, Vector3 pos, Vector3 size);
			Planet3D(const Planet3D& copy, Vector3 pos, Vector3 size);
			~Planet3D() override;
		private:
			bool meshOwner;
		};


		class SpaceDust2D : public RenderObject
		{
		public:
			SpaceDust2D(Vector3 pos);
			SpaceDust2D(const SpaceDust2D& copy, Vector3 pos);
			~SpaceDust2D();

		private:
			bool meshOwner;
		};


		class SpaceDust3D : public RenderObject
		{
		public:
			SpaceDust3D(Vector3 pos, Vector3 size);
			SpaceDust3D(const SpaceDust3D& copy, Vector3 pos, Vector3 size);
			~SpaceDust3D();

		private:
			bool meshOwner;
		};


		const vector<Vector3> fanPos = { Vector3(0, 0, 0), Vector3(0.8, 0.2, 0), Vector3(0.3, 0.6, 0),
			Vector3(-0.2, 0.9, 0) , Vector3(-0.8, 0.5, 0), Vector3(-rand() % 10 / 10.0, -rand() % 10 / 10.0, 0),
			Vector3(0.4, -0.6, 0), Vector3(0.8, -0.5, 0) };
		const vector<unsigned int> fanIndices = { 0, 1, 2, 3, 4, 5, 6, 7, 1 };

		class Rock2D : public RenderObject
		{
		public:
			Rock2D(COLOUR col, Vector3 pos, Vector3 size, Vector3 rot);
			Rock2D(const Rock2D& copy, Vector3 pos, Vector3 size, Vector3 rot);
			~Rock2D();

		private:
			bool meshOwner;
		};


		class RandomRock : public RenderObject
		{
		public:
			RandomRock(Vector3 pos, Vector3 size, Vector3 rot);
			RandomRock(const RandomRock& copy, Vector3 pos, Vector3 size, Vector3 rot);
			~RandomRock();

		private:
			bool meshOwner;
		};


		class SpaceShip : public RenderObject
		{
		public:
			SpaceShip(Vector3 pos, Vector3 size, Vector3 rot);
			SpaceShip(const SpaceShip& copy, Vector3 pos, Vector3 size, Vector3 rot);
			~SpaceShip();
		private:
			bool meshOwner;
		};
	}
}


