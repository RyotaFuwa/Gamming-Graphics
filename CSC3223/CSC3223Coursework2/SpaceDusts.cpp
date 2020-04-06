#include "SpaceDusts.h"

SpaceDusts::SpaceDusts()
{
	createdInside = true;
	mesh = new OGLMesh();
	mesh->SetPrimitiveType(GeometryPrimitive::Points);
	mesh->SetVertexPositions({ Vector3(0, 0, 0) });
	mesh->SetVertexColours({ Vector4(1, 1, 1, 0.8) });
	mesh->SetVertexNormals({ Vector3(0, -1, 0) });
	mesh->UploadToGPU();
}

SpaceDusts::SpaceDusts(const SpaceDusts& sd)
{
	loc = sd.loc;
}

SpaceDusts::SpaceDusts(OGLMesh* mesh) : RenderObject(mesh)
{
}

void SpaceDusts::Move()
{
	float dt = time - lastTime;
	transform = transform * Matrix4::Rotation(dt * rotate, Vector3(0, 1, 0));
	lastTime = time;
}

void SpaceDusts::AddUniforms(int programID)
{
	int locLocation = glGetUniformLocation(programID, "loc");
	if(locLocation >= 0)
	    glUniform3fv(locLocation, 1, (float*)& loc);

	if (!FixedCol) {
		int colLocation = glGetUniformLocation(programID, "col");
		if (colLocation >= 0)
			glUniform4fv(colLocation, 1, (float*)& col);
	}
}

void SpaceDusts::SetLocation(){
		if (fillReversePos) {
			float locy = PlusMinus() * RandBetween(0.05, 1.0) * height;
			float tanValue = tan(angle);
			float locx = RandBetween(-1.0, 1.0) * locy / tanValue;
			float locz = RandBetween(-1.0, 1.0) * locy / tanValue;
			loc = Vector3(locx, locy, locz);
			firstPosition = Vector3(locx, 0.0f, locz).Normalised() * 0.0001;
			transform = Matrix4::Translation(firstPosition) * transform;
		}
		else {
			float dis = RandBetween(0.075, 1.0) * height;
			float rad = RandBetween(0.0, 2.0) * 3.1415926535;
			float locx = dis * cos(rad);
			float locz = dis * sin(rad);
			float tanValue = tan(angle);
			float disxz = Vector2(locx, locz).Length();
			float locy =  disxz * tanValue;
			loc = Vector3(locx, locy, locz);
			firstPosition = Vector3(locx, 0.0f, locz).Normalised() * 0.0001;
			transform = Matrix4::Translation(firstPosition) * transform;
		}
}

void SpaceDusts::SetColour()
{
	if (FixedCol)
		col = colRange;
	else {
		if (fillReverseCol) {
			col.x = Rand01() * (1.0 - colRange.x) + colRange.x;
			col.y = Rand01() * (1.0 - colRange.y) + colRange.y;
			col.z = Rand01() * (1.0 - colRange.z) + colRange.z;
			col.w = Rand01() * (1.0 - colRange.w) + colRange.w;
		}
		else {
			col.x = Rand01() * colRange.x;
			col.y = Rand01() * colRange.y;
			col.z = Rand01() * colRange.z;
			col.w = Rand01() * colRange.w;
		}
	}
}
