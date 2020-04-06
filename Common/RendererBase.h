/*
Part of Newcastle University's Game Engineering source code.

Use as you see fit!

Comments and queries to: richard-gordon.davison AT ncl.ac.uk
https://research.ncl.ac.uk/game/
*/
#pragma once
#include "Window.h"

namespace NCL {
	namespace Rendering {
		enum VerticalSyncState {
			VSync_ON,
			VSync_OFF,
			VSync_ADAPTIVE
		};
		class RendererBase {
		public:
			friend class NCL::Window;

			RendererBase(Window& w);
			virtual ~RendererBase();

			virtual bool HasInitialised() const {return true;}

			virtual void Update(float dt) {}

			void Render(float time) {
				BeginFrame();
				RenderFrame(time);
				EndFrame();
			}

			virtual bool SetVerticalSync(VerticalSyncState s) {
				return false;
			}

		protected:
			virtual void OnWindowResize(int w, int h) = 0;
			virtual void OnWindowDetach() {}; //Most renderers won't care about this
			
			virtual void BeginFrame()	= 0;
			virtual void RenderFrame(float time)	= 0;
			virtual void EndFrame()		= 0;
			
			Window& hostWindow;

			int currentWidth;
			int currentHeight;
		};
	}
}
