#pragma once
#include "../Base/SceneBase.h"
#include "../../MathLib/MathLib.h"

class SceneClear : public SceneBase
{
private:
	std::shared_ptr<MathLib> m_mathLib;


	int graphHandle;
	int pixelShaderHandle;
	int vertexShaderHandle;
	VERTEX3DSHADER vert[6] = { 0.0f };

public:
	SceneClear();
	~SceneClear()override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

private:
	
	struct Capsule
	{
		VECTOR pos;
		float heght;
		float radius;
	}m_capsule, m_capsule2;

	struct Polygon
	{
		VECTOR vertex[3];
		VECTOR Normal;
		VECTOR center;
	}m_polygon;

	VECTOR segment2 = VGet(0,0,0);
	VECTOR segment1 = VGet(0, 0, 0);
	void MathTestCapsule();

	VECTOR Cto01Segmtnt = VGet(0,0,0);
	VECTOR Cto12Segmtnt = VGet(0, 0, 0);
	VECTOR Cto20Segmtnt = VGet(0, 0, 0);

	VECTOR Cto01Segmtnt01 = VGet(0, 0, 0);
	VECTOR Cto12Segmtnt12 = VGet(0, 0, 0);
	VECTOR Cto20Segmtnt20 = VGet(0, 0, 0);

	void MathTestPolygonToCapusle();

};

