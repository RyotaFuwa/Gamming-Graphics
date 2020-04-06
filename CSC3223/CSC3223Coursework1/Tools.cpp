#include "Tools.h"
#include "../../Common/Vector3.h"

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

Vector3 CW2Tools::RandSize(float a, float b)
{
	float size = RandBetween(a, b);
	return Vector3(size, size, size);
}

