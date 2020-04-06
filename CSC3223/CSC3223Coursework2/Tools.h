#pragma once
#include <vector>
#include <string>
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/TextureBase.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

using namespace NCL::Rendering;
using namespace NCL::Maths;
using namespace std;

namespace CW2Tools {
	enum CUBECOLOUR {
		BLACK = 0,
		WHITE,
		RED,
		GREEN,
		BLUE,
		FROMFILE
	};

	struct VarTexture {
		VarTexture(string v, string fn) : var(v),
			filename(fn), tex(OGLTexture::RGBATextureFromFilename(fn)) {}
		string var;
		string filename;
		TextureBase* tex;
	};

	struct ShaderBundle {
		ShaderBundle(string v = "rasterisationVert.glsl", string f = "rasterisationFrag.glsl", string g = "", string tc = "", string te = "") :
			vert(v), frag(f), geom(g), tessCtrl(tc), tessEval(te) {}
		string vert;
		string frag;
		string geom;
		string tessCtrl;
		string tessEval;
	};


	std::vector<Vector4> GetColourVectors(int size, CUBECOLOUR colNum);
	Vector3 GetCentroidVector(std::vector<Vector3> pos);
	float RandBetween(float a, float b);
	float Rand01();
	float PlusMinus();
	Vector3 RandVec3(float a, float b);

}
