
#include "RenderObject.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

using namespace NCL;
using namespace CSC3223;
using namespace CW2Tools;
class SpaceDusts :
	public RenderObject
{
public:
	SpaceDusts();
	SpaceDusts(const SpaceDusts& sd);
	SpaceDusts(OGLMesh* mesh);
	void Move() override;
	void AddUniforms(int programID) override;

	void SetLocation();
	void SetColour();

	float GetRotate() { return rotate; }
	void SetRotate(float r) { rotate = r; }
	float GetAngle() { return angle; }
	void SetAngle(float a) { angle = a * 3.14159265f / 180.0f; }
	float GetHeight() { return height; }
	void SetHeight(float h) { height = h; }
	void EnableFillReversePos(bool state) { fillReversePos = state; }

	void EnableFixedCol(bool state) { FixedCol = state; }
	void EnableFillReverseCol(bool state) { fillReverseCol = state; }
	Vector4 GetColRange() { return colRange; }
	void SetColRange(Vector4 cr) { colRange = cr; }

private:
	Vector3 firstPosition = Vector3(0, 0, 0);
	Vector3 loc;
	Vector4 col;

	float rotate = 30.0f;

	bool fillReversePos = true;
	float angle = 85.0f * 3.14159265f / 180.0f;
	float height = 20.0;

	bool FixedCol = true;
	bool fillReverseCol = false;
	Vector4 colRange = Vector4(1, 1, 1, 0.8);
};
