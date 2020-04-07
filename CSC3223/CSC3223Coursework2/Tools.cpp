#include "Tools.h"

using namespace CW2Tools;


Vector3 CW2Tools::GetCentroidVector(std::vector<Vector3> pos)
{
	Vector3 centroid = Vector3(0, 0, 0);
	for (Vector3 each : pos) {
		centroid += each;
	}
	centroid /= pos.size();
	return centroid;
}

float CW2Tools::RandBetween(float a, float b)
{
	float diff = rand() % (int)(10000 * (b - a) + 1) / 10001.0f;
	return diff + a;
}

float CW2Tools::Rand01()
{
	return RandBetween(0.0f, 1.0f);
}

float CW2Tools::PlusMinus()
{
	float value = Rand01();
	return value < 0.5f ? -1.0f : 1.0f;
}


Vector3 CW2Tools::RandVec3(float a, float b)
{
	float value1 = RandBetween(a, b);
	float value2 = RandBetween(a, b);
	float value3 = RandBetween(a, b);

	return Vector3(value1, value2, value3);
}

std::vector<Vector4> CW2Tools::GetColourVectors(int size, CUBECOLOUR colourNum)
{
	std::vector<Vector4> col;
	switch (colourNum) {
	case CUBECOLOUR::BLACK:
		for (int i = 0; i < size; i++) {
			col.push_back(Vector4(1, 1, 1, 1));
		}
		break;
	case CUBECOLOUR::WHITE:
		for (int i = 0; i < size; i++) {
			col.push_back(Vector4(0, 0, 0, 0));
		}
		break;
	case CUBECOLOUR::RED:
		for (int i = 0; i < size; i++) {
			col.push_back(Vector4(1, 0, 0, 1));
		}
		break;
	case CUBECOLOUR::GREEN:
		for (int i = 0; i < size; i++) {
			col.push_back(Vector4(0, 1, 0, 1));
		}
		break;
	case CUBECOLOUR::BLUE:
		for (int i = 0; i < size; i++) {
			col.push_back(Vector4(0, 0, 0, 1));
		}
		break;
	default:
		break;
	}

	return col;
}

