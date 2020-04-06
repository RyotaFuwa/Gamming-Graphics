#pragma once
#include "Renderer.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector2.h"

namespace NCL {
	using namespace Maths;
	namespace CSC3223 {
		class RenderObject;
		class BackGround
		{
		public:
			BackGround(Renderer* r);
			~BackGround();

			void SetObject(RenderObject* ro, Vector3 velocity=Vector3(0, 0, 0), Vector3 angularVelocity=Vector3(0, 0, 0));
			void RemoveObject(RenderObject* ro);
			void ViewUpdate();
			void ObjectsUpdate(float dt);
			void Update(float dt);
			void Activate();
			static BackGround* GetActiveBG();

			void SetViewTo(Vector3 pos = Vector3(0.0f, 0.0f, 0.0f), Vector3 rot = Vector3(0.0f, 0.0f, 0.0f));
			void SetViewPos(Vector3 pos);
			Vector3 GetViewPos();
			void SetViewRot(Vector3 rot);
			Vector3 GetViewRot();
			Vector2 GetDepth();
			void Reset();

		protected:
			static BackGround* active;
			Renderer* renderer;
			float time;

			vector<RenderObject*> objects;
			vector<Matrix4> originalPos;
			vector<Vector3> velocities;
			vector<Vector3> angularVelocities;
			Vector3 viewPos;
			Vector3 viewRot;
			Matrix4 perspective;
			Vector2 depth;
		};

		class BackGround2D : public BackGround {
		public:
			BackGround2D(Renderer* r, float width, float height, Vector2 depth);
			~BackGround2D();
		};

		class BackGround3D : public BackGround {
		public:
			BackGround3D(Renderer* r, float aspect, float angle, Vector2 depth);
			~BackGround3D();
		};

		class RYOTAName : public BackGround {
		public:
			RYOTAName(Renderer* r);
			~RYOTAName();
		};
	}
}

