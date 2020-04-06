#include <cmath>
#include <vector>
#include <map>

#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"
#include "RenderObject.h"
#include "RasterisationMesh.h"
#include "BackGround.h"
#include "SpaceObjects.h"
#include "Tools.h"





using namespace NCL;
using namespace CSC3223;
using namespace CW2Tools;


BackGround SpaceScene2D(BackGround& bg2, const Window* w) {
    float width = w->GetScreenSize().x;
    float height = w->GetScreenSize().y;
    int widthHight = width * width;
    int longAxis = max(width, height);

    // cheap space ship
    RenderObject* spaceShip = new SpaceShip(Vector3(0, 0, - bg2.GetDepth()[1] / 2.0), Vector3(5, 5, 5), Vector3(0, 0, 0));
    bg2.SetObject(spaceShip);

    // planet 2D
    int planetNum = 4;
    for (int i = 0; i < planetNum; i++) {
        Vector3 pos = RandVec3(-longAxis / 2.0, longAxis / 2.0);
        pos.z = RandBetween(bg2.GetDepth()[0], bg2.GetDepth()[1]);

        Vector3 size = RandSize(25, 50);
        int planetType = (i % 3); //MOON, SUN, JUPYTER
        RenderObject* planet = new Planet2D((PLANET)planetType, pos, size);
        bg2.SetObject(planet);
    }

    // star field
    SpaceDust2D* dust0 = new SpaceDust2D(Vector3());
    int starNum = (int)widthHight * 0.01;
    for (int i = 0; i < starNum; i++) {
        Vector3 pos = RandVec3(-height / 2.0, height / 2.0);
        pos.z = 0.0f;
        RenderObject* dust = new SpaceDust2D(*dust0, pos);
        bg2.SetObject(dust);
    }
    return bg2;
}


BackGround SpaceScene3D(BackGround& bg3, const Window* w) {
    float width = w->GetScreenSize().x;
    float height = w->GetScreenSize().y;

    // cheap space ship
    RenderObject* spaceShip = new SpaceShip(Vector3(0, 0, bg3.GetDepth()[1] + 10.0), Vector3(5, 5, 5), Vector3(-65, 0, 0));
    bg3.SetObject(spaceShip);

    // little stars 
    int num = 1000;
    SpaceDust3D* starDust0 = new SpaceDust3D(Vector3(), Vector3());
    for (int i = 0; i < num; i++) {
        Vector3 pos;
        pos.x = RandBetween(-width / 2.0, width / 2.0);
        pos.y = RandBetween(-height / 2.0, height / 2.0);
        pos.z = -RandBetween(0, 400);

        Vector3 size = RandSize(1, 4) * 0.25;

        Vector3 velocity(0, 0, 0), angularVelocity(0, 0, 0);
        if (i % 3 == 0) {
            velocity.x = RandBetween(-1.0, 1.0);
            velocity.y = RandBetween(-1.0, 1.0);
            velocity.z = RandBetween(-1.0, 1.0);
            angularVelocity.x = RandBetween(-1.0, 1.0);
            angularVelocity.y = RandBetween(-1.0, 1.0);
            angularVelocity.z = RandBetween(-1.0, 1.0);
        }
        RenderObject* starDust = new SpaceDust3D(*starDust0, pos, size);
        bg3.SetObject(starDust, velocity, angularVelocity);
    }

    return bg3;
}


int main() {
    Window* w = Window::CreateGameWindow("CSC3223 Coursework 1!");
    const float width = w->GetScreenSize().x;
    const float height = w->GetScreenSize().y;
    const float aspect = w->GetScreenAspect();

    if (!w->HasInitialised()) {
        return -1;
    }

    Renderer* renderer = new Renderer(*w);

    BackGround bg2 = BackGround2D(renderer, width, height, Vector2(2.0, 100));
    bg2 = SpaceScene2D(bg2, w);
    BackGround bg3 = BackGround3D(renderer, aspect, 45.0f, Vector2(1.0, 500));
    bg3 = SpaceScene3D(bg3, w);
    BackGround ryotaRastraizaion = RYOTAName(renderer);

    // environment variables
    float time = 0;
    bool stop = false;
    bool depthBuffer = false;
    bool alphaBlend = true;

    // loop starts here
    while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
        BackGround* activeBG = BackGround::GetActiveBG();

        // render here
        float dt = w->GetTimer()->GetTimeDelta();
        w->SetTitle(std::to_string(time));

        if (Window::GetKeyboard()->KeyPressed(KEYBOARD_0)) {
            activeBG->Reset();
        }

        // dynamic objects start or stop
        if (Window::GetKeyboard()->KeyPressed(KEYBOARD_1)) {
            stop = !stop;
        }

        // view change
        if (Window::GetKeyboard()->KeyPressed(KEYBOARD_2)) {
            bg2.Activate();
        }
        if (Window::GetKeyboard()->KeyPressed(KEYBOARD_3)) {
            bg3.Activate();
        }
        if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F9)) {
            ryotaRastraizaion.Activate();
        }


        // basic operation
        if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
            w->ShowConsole(true);
        }
        if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
            w->ShowConsole(false);
        }
        if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
            w->SetFullScreen(true);
        }
        if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
            w->SetFullScreen(false);
        }
        if (Window::GetKeyboard()->KeyDown(KEYBOARD_BACK)) {
        }

        // rasterisation
        if (Window::GetKeyboard()->KeyDown(KEYBOARD_F1)) {
            depthBuffer = !depthBuffer;
            renderer->EnableDepthBuffer(depthBuffer);
        }
        if (Window::GetKeyboard()->KeyDown(KEYBOARD_F2)) {
            glDepthFunc(GL_LEQUAL);
        }
        if (Window::GetKeyboard()->KeyDown(KEYBOARD_F3)) {
            glDepthFunc(GL_ALWAYS);

        }
        if (Window::GetKeyboard()->KeyDown(KEYBOARD_F4)) {
            glDepthFunc(GL_EQUAL);

        }
        if (Window::GetKeyboard()->KeyDown(KEYBOARD_F5)) {
            alphaBlend = !alphaBlend;
            renderer->EnableAlphaBlending(alphaBlend);
        }
        if (Window::GetKeyboard()->KeyDown(KEYBOARD_F6)) {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        if (Window::GetKeyboard()->KeyDown(KEYBOARD_F7)) {
            glBlendFunc(GL_ONE, GL_ONE);
        }
        if (Window::GetKeyboard()->KeyDown(KEYBOARD_F8)) {
            glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
        }


	    if (Window::GetKeyboard()->KeyDown(KEYBOARD_K)) {
            activeBG->SetViewPos(activeBG->GetViewPos() + Vector3(0.0f, 0.5f, 0.0f));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_N)) {
            activeBG->SetViewPos(activeBG->GetViewPos() + Vector3(0.0f, 0.0f, 0.5f));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_H)) {
            activeBG->SetViewPos(activeBG->GetViewPos() + Vector3(0.5f, 0.0f, 0.0f));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_L)) {
            activeBG->SetViewPos(activeBG->GetViewPos() - Vector3(0.5f, 0.0f, 0.0f));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_J)) {
            activeBG->SetViewPos(activeBG->GetViewPos() - Vector3(0.0f, 0.5f, 0.0f));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_M)) {
            activeBG->SetViewPos(activeBG->GetViewPos() - Vector3(0.0f, 0.0f, 0.5f));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
            activeBG->SetViewRot(activeBG->GetViewRot() + Vector3(0.0f, 0.0f, 0.5f));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F)) {
            activeBG->SetViewRot(activeBG->GetViewRot() - Vector3(0.0f, 0.0f, 0.5f));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
            activeBG->SetViewRot(activeBG->GetViewRot() + Vector3(0.5f, 0.0f, 0.0f));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
            activeBG->SetViewRot(activeBG->GetViewRot() - Vector3(0.5f, 0.0f, 0.0f));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_R)) {
            activeBG->SetViewRot(activeBG->GetViewRot() + Vector3(0.0f, 0.5f, 0.0f));
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_B)) {
            activeBG->SetViewRot(activeBG->GetViewRot() - Vector3(0.0f, 0.5f, 0.0f));
		}

		if (Window::GetMouse()->ButtonDown(MOUSE_LEFT)) {
			Vector2 direc = Window::GetMouse()->GetRelativePosition();
            Vector3 viewPos = activeBG->GetViewPos();
			viewPos.x -= direc.x;
			viewPos.y += direc.y;
            activeBG->SetViewPos(viewPos);
		}
		if (Window::GetMouse()->ButtonDown(MOUSE_RIGHT)) {
			Vector2 direc = Window::GetMouse()->GetRelativePosition();
            Vector3 viewRot = activeBG->GetViewRot();
			viewRot.x -= direc.x;
			viewRot.y += direc.y;
            activeBG->SetViewRot(viewRot);
		}
		if (Window::GetMouse()->WheelMoved()) {
            Vector3 viewPos = activeBG->GetViewPos();
			viewPos.z += 3.0 * Window::GetMouse()->GetWheelMovement();
            activeBG->SetViewPos(viewPos);
		}

        if (!stop) {
            BackGround::GetActiveBG()->Update(dt);
            renderer->Update(dt);
            renderer->Render(dt);
			time += dt;
        }

    }
    delete renderer;

    Window::DestroyGameWindow();
}