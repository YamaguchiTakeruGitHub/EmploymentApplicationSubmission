#include "SceneClear.h"

SceneClear::SceneClear()
	: graphHandle(-1)
	, pixelShaderHandle(-1)
	, vertexShaderHandle(-1)
	, vert{0.0f}
{
	m_mathLib = std::make_shared<MathLib>();
}

SceneClear::~SceneClear()
{
}

void SceneClear::Init()
{
	m_Idm->Init();

	
	graphHandle = LoadGraph("../Data/Asset/2D/Texture0.bmp");
	vertexShaderHandle = LoadVertexShader("../../VertexShader_1.vso");
	pixelShaderHandle = LoadPixelShader("../../PixelShader_1.pso");
	
	vert[0].pos = VGet(100.0f, 356.0f, 0.0f);
	vert[1].pos = VGet(356.0f, 356.0f, 0.0f);
	vert[2].pos = VGet(100.0f, 100.0f, 0.0f);
	vert[3].pos = VGet(356.0f, 100.0f, 0.0f);

	vert[0].dif = GetColorU8(255, 255, 255, 255);
	vert[1].dif = GetColorU8(255, 255, 255, 255);
	vert[2].dif = GetColorU8(255, 255, 255, 255);
	vert[3].dif = GetColorU8(255, 255, 255, 255);

	vert[0].u = 0.0f; vert[0].v = 0.0f;
	vert[1].u = 1.0f; vert[1].v = 0.0f;
	vert[2].u = 0.0f; vert[3].v = 1.0f;
	vert[3].u = 1.0f; vert[2].v = 1.0f;
	vert[4] = vert[2];
	vert[5] = vert[1];

	/*カプセルテスト*/
	m_capsule.pos = VGet(100, 100, 0);
	m_capsule.heght = 100.0f;
	m_capsule.radius = 60.0f;

	/*カプセルテスト2*/
	m_capsule2.pos = VGet(500, 100, 0);
	m_capsule2.heght = 100.0f;
	m_capsule2.radius = 60.0f;

	/*ポリゴンテスト*/
	m_polygon.vertex[0] = VGet(200, 200, 0);
	m_polygon.vertex[1] = VGet(300, 300, 0);
	m_polygon.vertex[2] = VGet(400, 200, 0);

}

void SceneClear::Update()
{
	m_Idm->Update();

	/*vert[1].pos.x++;
	vert[5].pos.x++;

	vert[3].pos.x++;*/
	
	//HitTest();

	if (CheckHitKey(KEY_INPUT_UP)) m_capsule.pos.y++;
	if (CheckHitKey(KEY_INPUT_DOWN)) m_capsule.pos.y--;
	if (CheckHitKey(KEY_INPUT_RIGHT)) m_capsule.pos.x++;
	if (CheckHitKey(KEY_INPUT_LEFT)) m_capsule.pos.x--;


	m_polygon.Normal =	VNorm(m_mathLib->PolygonNormalize(m_polygon.vertex[0], m_polygon.vertex[1], m_polygon.vertex[2]));
	m_polygon.center = m_mathLib->PolygonCenter(m_polygon.vertex[0], m_polygon.vertex[1], m_polygon.vertex[2]);
}

void SceneClear::Draw()
{
	//SetUseTextureToShader(0, graphHandle);
	//SetUseVertexShader(vertexShaderHandle);
	//SetUsePixelShader(pixelShaderHandle);
	//
	//DrawPolygon3DToShader(vert, 2);

	//SetUseVertexShader(-1);
	//SetUsePixelShader(-1);

#ifdef _DEBUG
	DrawString(0, 0, "ClearScene", 0xffffff);


	//MathTestPolygonToCapusle();
	MathTestCapsule();

#endif // _DEBUG

}

void SceneClear::Final()
{
	DeleteShader(vertexShaderHandle);
	DeleteShader(pixelShaderHandle);
}

void SceneClear::MathTestCapsule()
{
	/*カプセルテスト*/
	DrawLine3D(m_capsule.pos, VAdd(m_capsule.pos, VGet(0, m_capsule.heght, 0)), 0xff0000);
	DrawCapsule3D(m_capsule.pos, VAdd(m_capsule.pos, VGet(0, m_capsule.heght, 0)), m_capsule.radius, 5, 0xffffff, 0xffffff, false);

	DrawLine3D(m_capsule2.pos, VAdd(m_capsule2.pos, VGet(0, m_capsule.heght, 0)), 0xff0000);
	DrawCapsule3D(m_capsule2.pos, VAdd(m_capsule2.pos, VGet(0, m_capsule2.heght, 0)), m_capsule2.radius, 5, 0xffffff, 0xffffff, false);

	segment1 = m_mathLib->Line_Segment_Point_VECTOR(m_capsule.pos, VAdd(m_capsule.pos, VGet(0, m_capsule.heght, 0)), segment2);
	segment2 = m_mathLib->Line_Segment_Point_VECTOR(m_capsule2.pos, VAdd(m_capsule2.pos, VGet(0, m_capsule2.heght, 0)), segment1);

	VECTOR segmentLineToLine = VSub(segment1, segment2);

	if (VSize(segmentLineToLine) <= m_capsule.radius + m_capsule2.radius)
	{
		DrawLine3D(segment1, segment2, 0xff0000);
		VECTOR pushBack = VScale(VNorm(segmentLineToLine), m_capsule.radius + m_capsule2.radius - VSize(segmentLineToLine));
		m_capsule.pos = VAdd(m_capsule.pos, pushBack);

		VECTOR pushBack2 = VScale(VNorm(segmentLineToLine), m_capsule.radius + m_capsule2.radius - VSize(segmentLineToLine));
		m_capsule2.pos = VSub(m_capsule2.pos, pushBack2);
	}
	else
	{
		DrawLine3D(segment1, segment2, 0xffffff);
	}
}

void SceneClear::MathTestPolygonToCapusle()
{
	/*ポリゴン*/
	DrawTriangle3D(m_polygon.vertex[0], m_polygon.vertex[1], m_polygon.vertex[2], 0xffffff, true);

	/*カプセル*/
	DrawCapsule3D(m_capsule.pos, VAdd(m_capsule.pos, VGet(0, m_capsule.heght, 0)), m_capsule.radius, 5, 0xffffff, 0xffffff, false);
	DrawLine3D(m_capsule.pos, VAdd(m_capsule.pos, VGet(0, m_capsule.heght, 0)), 0xff0000);

	/*計算*/
	//カプセルの線分とポリゴンの01の変の最近接点
	Cto01Segmtnt = m_mathLib->Line_Segment_Point_VECTOR(m_capsule.pos, VAdd(m_capsule.pos, VGet(0, m_capsule.heght, 0)), Cto01Segmtnt01);
	Cto12Segmtnt = m_mathLib->Line_Segment_Point_VECTOR(m_capsule.pos, VAdd(m_capsule.pos, VGet(0, m_capsule.heght, 0)), Cto12Segmtnt12);
	Cto20Segmtnt = m_mathLib->Line_Segment_Point_VECTOR(m_capsule.pos, VAdd(m_capsule.pos, VGet(0, m_capsule.heght, 0)), Cto20Segmtnt20);

	Cto01Segmtnt01 = m_mathLib->Line_Segment_Point_VECTOR(m_polygon.vertex[0], m_polygon.vertex[1], Cto01Segmtnt);
	Cto12Segmtnt12 = m_mathLib->Line_Segment_Point_VECTOR(m_polygon.vertex[1], m_polygon.vertex[2], Cto12Segmtnt);
	Cto20Segmtnt20 = m_mathLib->Line_Segment_Point_VECTOR(m_polygon.vertex[2], m_polygon.vertex[0], Cto20Segmtnt);


	// 各辺との距離を計算
	float dist01 = VSize(VSub(Cto01Segmtnt, Cto01Segmtnt01));
	float dist12 = VSize(VSub(Cto12Segmtnt, Cto12Segmtnt12));
	float dist20 = VSize(VSub(Cto20Segmtnt, Cto20Segmtnt20));

	// 最も距離が近い辺を特定
	float minDist = dist01;
	VECTOR closestSegmentStart = Cto01Segmtnt;
	VECTOR closestSegmentEnd = Cto01Segmtnt01;

	if (dist12 < minDist) {
		minDist = dist12;
		closestSegmentStart = Cto12Segmtnt;
		closestSegmentEnd = Cto12Segmtnt12;
	}

	if (dist20 < minDist) {
		minDist = dist20;
		closestSegmentStart = Cto20Segmtnt;
		closestSegmentEnd = Cto20Segmtnt20;
	}

	if (VSize(VSub(closestSegmentEnd, closestSegmentStart)) <= m_capsule.radius)
	{
		DrawLine3D(closestSegmentStart, closestSegmentEnd, 0xff0000);

		// 押し戻しベクトルの計算
		VECTOR pushBack = VScale(m_polygon.Normal, m_capsule.radius - minDist);

		// カプセルの位置を更新
		m_capsule.pos = VAdd(m_capsule.pos, pushBack);

	}
	else
	{
		DrawLine3D(closestSegmentStart, closestSegmentEnd, 0xffffff);
	}

}


