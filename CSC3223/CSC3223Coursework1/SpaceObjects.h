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


		class Planet2D : public RenderObject
		{
		public:
			Planet2D(PLANET p, Vector3 pos=Vector3(0, 0, 0), Vector3 size=Vector3(0, 0, 0));
			Planet2D(const Planet2D& copy, Vector3 pos, Vector3 size);
			~Planet2D() override;
		private:
			bool meshOwner;
		};


		class Planet3D : public RenderObject
		{
		public:
			Planet3D(PLANET p, Vector3 pos=Vector3(0, 0, 0), Vector3 size=Vector3(0, 0, 0));
			Planet3D(const Planet3D& copy, Vector3 pos, Vector3 size);
			~Planet3D() override;
		private:
			bool meshOwner;
		};


		class SpaceDust2D : public RenderObject
		{
		public:
			SpaceDust2D(Vector3 pos=Vector3(0, 0, 0));
			SpaceDust2D(const SpaceDust2D& copy, Vector3 pos);
			~SpaceDust2D();

		private:
			bool meshOwner;
		};


		class SpaceDust3D : public RenderObject
		{
		public:
			SpaceDust3D(Vector3 pos=Vector3(0, 0, 0), Vector3 size=Vector3(1, 1, 1));
			SpaceDust3D(const SpaceDust3D& copy, Vector3 pos, Vector3 size);
			~SpaceDust3D();

		private:
			bool meshOwner;
		};

	
		class Rock2D : public RenderObject
		{
		public:
			Rock2D(COLOUR col, Vector3 pos=Vector3(0, 0, 0), Vector3 size=Vector3(1, 1, 1), Vector3 rot=Vector3(0, 0, 0));
			Rock2D(const Rock2D& copy, Vector3 pos, Vector3 size, Vector3 rot);
			~Rock2D();

		private:
			bool meshOwner;
		};


		class RandomRock : public RenderObject
		{
		public:
			RandomRock(Vector3 pos=Vector3(0, 0, 0), Vector3 size=Vector3(1, 1, 1), Vector3 rot=Vector3(0, 0, 0));
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


