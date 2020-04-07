#pragma once
#include <vector>
#include <string>
#include "../../Common/Vector3.h"


using namespace NCL::Maths;

namespace CW1Tools {
	Vector3 GetCentroidVector(std::vector<Vector3> pos);
	Vector3 GetSurfaceVector(std::vector<Vector3> pos);
	float RandBetween(float a, float b);
	float Rand01();
	float PlusMinus();
	Vector3 RandVec3(float a, float b);
	Vector3 RandSize(float a, float b);
}

inline Vector3 CW1Tools::GetSurfaceVector(std::vector<Vector3> pos)
{
	Vector3 v1 = pos[1] - pos[0];
	Vector3 v2 = pos[2] - pos[0];
	return Vector3::Cross(v1, v2).Normalised();
}

inline Vector3 CW1Tools::GetCentroidVector(std::vector<Vector3> pos)
{
	Vector3 centroid = Vector3(0, 0, 0);
	for (Vector3 each : pos) {
		centroid += each;
	}
	centroid /= pos.size();
	return centroid;
}

inline float CW1Tools::RandBetween(float a, float b)
{
	float diff = rand() % (int)(10000 * (b - a) + 1) / 10001.0f;
	return diff + a;
}

inline float CW1Tools::Rand01()
{
	return RandBetween(0.0f, 1.0f);
}

inline float CW1Tools::PlusMinus()
{
	float value = Rand01();
	return value < 0.5f ? -1.0f : 1.0f;
}


inline Vector3 CW1Tools::RandVec3(float a, float b)
{
	float value1 = RandBetween(a, b);
	float value2 = RandBetween(a, b);
	float value3 = RandBetween(a, b);

	return Vector3(value1, value2, value3);
}

inline Vector3 CW1Tools::RandSize(float a, float b)
{
	float size = RandBetween(a, b);
	return Vector3(size, size, size);
}


