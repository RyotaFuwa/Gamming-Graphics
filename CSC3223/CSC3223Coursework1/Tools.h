#pragma once
#include <vector>
#include <string>
#include "../../Common/Vector3.h"


using namespace NCL::Maths;

namespace CW2Tools {
	float RandBetween(float a, float b);
	float Rand01();
	float PlusMinus();
	Vector3 RandVec3(float a, float b);
	Vector3 RandSize(float a, float b);
}
