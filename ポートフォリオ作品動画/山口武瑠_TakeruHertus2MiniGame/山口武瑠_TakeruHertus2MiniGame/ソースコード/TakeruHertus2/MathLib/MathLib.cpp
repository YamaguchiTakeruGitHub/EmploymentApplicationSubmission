#include "MathLib.h"
#include <cmath>

float MathLib::Clamp(float _minVal, float _maxVal, float _val)
{
	if (_val < _minVal) return _val = _minVal;
	else if (_val > _maxVal) return _val = _maxVal;
}

VECTOR MathLib::Vector_X_float(VECTOR _vval, float _fval)
{
	VECTOR result;
	result.x = _vval.x * _fval;
	result.y = _vval.y * _fval;
	result.z = _vval.z * _fval;
	return result;
}

bool MathLib::CheckLineIntersection(VECTOR _posStart1, VECTOR _posEnd1, VECTOR _posStart2, VECTOR _posEnd2)
{
	VECTOR p1_Line = VSub(_posStart1, _posEnd1);//1の線分

	VECTOR p1S_To_p2S_Line = VSub(_posStart1, _posStart2);//1の開始地点と２の開始地点の線分

	VECTOR p1S_To_p2E_Line = VSub(_posStart1, _posEnd2);//１の開始地点と２の終了地点の線分

	VECTOR p2_Line = VSub(_posStart2, _posEnd2);//2の線分
	
	VECTOR p2S_To_p1S_Line = VSub(_posStart2, _posStart1);//2の開始地点と1の開始地点の線分

	VECTOR p2S_To_p1E_Line = VSub(_posStart2, _posEnd1);//2の開始地点と1の終了地点の線分

	//==================================================================================

	VECTOR cross1 = VCross(p1_Line, p1S_To_p2S_Line);

	VECTOR cross2 = VCross(p1_Line, p1S_To_p2E_Line);

	VECTOR cross3 = VCross(p2_Line, p2S_To_p1S_Line);

	VECTOR cross4 = VCross(p2_Line, p2S_To_p1E_Line);

	return (VDot(cross1, cross2) < 0) && (VDot(cross3, cross4) < 0);

	//return (VDot(cross1, cross2) < 0.0f) && (VDot(cross3, cross4) < 0.0f);
}

VECTOR MathLib::PolygonNormalize(VECTOR A, VECTOR B, VECTOR C)
{
	return VNorm(VCross(VSub(B, A), VSub(C, A)));
}

VECTOR MathLib::PolygonCenter(VECTOR A, VECTOR B, VECTOR C)
{
	VECTOR a = VAdd(A, VAdd(B, C));

	return VGet(a.x / 3, a.y / 3, a.z / 3);;
}

float MathLib::Distance_Target_Polygon(VECTOR A, VECTOR B, VECTOR C, VECTOR P)
{
	VECTOR normal = PolygonNormalize(A, B, C);
	VECTOR center = PolygonCenter(A, B, C);
	VECTOR diff = VSub(P, center);
	return VDot(normal, diff);
}

VECTOR MathLib::Line_Segment_Point_VECTOR(VECTOR A, VECTOR B, VECTOR P)
{
	VECTOR AB = VSub(B, A);//線分の距離（ABベクトル）
	VECTOR AP = VSub(P, A);//線分の端から点の距離（APベクトル）
	float t = VDot(AP, AB) / VDot(AB, AB);//内積を使って線分の長さを求める
	t = Clamp(0.0f, 1.0f, t);//線分の長さを0～1の間に収める
	return VAdd(A, VScale(AB, t));//最近点を求める
}

float MathLib::Line_Segment_Point_FLOAT(VECTOR A, VECTOR B, VECTOR P)
{
	VECTOR AB = VSub(B, A);//線分の距離（ABベクトル）
	VECTOR AP = VSub(P, A);//線分の端から点の距離（APベクトル）
	float t = VDot(AP, AB) / VDot(AB, AB);//内積を使って線分の長さを求める
	t = Clamp(0.0f, 1.0f, t);//線分の長さを0～1の間に収める
	VECTOR closest =  VAdd(A, VScale(AB, t));//最近点を求める
	return VSize(VSub(P, closest));//最近点と点の距離を求める
}

VECTOR MathLib::Line_Segment_Line_VECTOR(VECTOR A, float aHeight, VECTOR B, float bHeight)
{
	VECTOR segment1 = VGet(0,0,0);
	VECTOR segment2 = VGet(0,0,0);

	segment1 = Line_Segment_Point_VECTOR(A, VAdd(A, VGet(0, aHeight, 0)), segment2);
	segment2 = Line_Segment_Point_VECTOR(B, VAdd(B, VGet(0, bHeight, 0)), segment1);
	
	return VSub(segment1, segment2);
}

float MathLib::Line_Segment_Line_FLOAT(VECTOR A, float aHeight, VECTOR B, float bHeight)
{
	VECTOR segment1 = VGet(0, 0, 0);
	VECTOR segment2 = VGet(0, 0, 0);

	segment1 = Line_Segment_Point_VECTOR(A, VAdd(A, VGet(0, aHeight, 0)), segment2);
	segment2 = Line_Segment_Point_VECTOR(B, VAdd(B, VGet(0, bHeight, 0)), segment1);

	VECTOR segment =  VSub(segment1, segment2);

	return VSize(segment);
}

bool MathLib::Capsule_Capsule_HitCheck(VECTOR A, float aHeight, float aRadius, VECTOR B, float bHeight, float bRadius)
{
	/*線分と線分の最近点線*/
	VECTOR segmtntLineToLine = Line_Segment_Line_VECTOR(A, aHeight, B, bHeight);

	/*最近点線の距離が半径寄り小さければ*/
	if (VSize(segmtntLineToLine) <= aRadius + aRadius)
	{
		return true;//衝突
	}

	return false;//衝突していない
}


bool MathLib::Polygon_Capsule_HitCheck(VECTOR A, float aHeight, float aRadius, VECTOR poly[3])
{
	VECTOR Cto01Segmtnt01 = VGet(0, 0, 0);
	VECTOR Cto12Segmtnt12 = VGet(0, 0, 0);
	VECTOR Cto20Segmtnt20 = VGet(0, 0, 0);

	VECTOR Cto01Segmtnt = Line_Segment_Point_VECTOR(A, VAdd(A, VGet(0, aHeight, 0)), Cto01Segmtnt01);
	VECTOR Cto12Segmtnt = Line_Segment_Point_VECTOR(A, VAdd(A, VGet(0, aHeight, 0)), Cto12Segmtnt12);
	VECTOR Cto20Segmtnt = Line_Segment_Point_VECTOR(A, VAdd(A, VGet(0, aHeight, 0)), Cto20Segmtnt20);

	Cto01Segmtnt01 = Line_Segment_Point_VECTOR(poly[0], poly[1], Cto01Segmtnt);
	Cto12Segmtnt12 = Line_Segment_Point_VECTOR(poly[1], poly[2], Cto12Segmtnt);
	Cto20Segmtnt20 = Line_Segment_Point_VECTOR(poly[2], poly[0], Cto20Segmtnt);

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

	VECTOR normal = PolygonNormalize(poly[0], poly[1], poly[2]);

	if (VSize(VSub(closestSegmentEnd, closestSegmentStart)) <= aRadius)
	{
		return true;
	}

	return false;
}

VECTOR MathLib::Polygon_Capsule_PushBack(VECTOR A, float aHeight, float aRadius, VECTOR poly[3])
{
	VECTOR Cto01Segmtnt01 = VGet(0, 0, 0);
	VECTOR Cto12Segmtnt12 = VGet(0, 0, 0);
	VECTOR Cto20Segmtnt20 = VGet(0, 0, 0);

	VECTOR Cto01Segmtnt = Line_Segment_Point_VECTOR(A, VAdd(A, VGet(0, aHeight, 0)), Cto01Segmtnt01);
	VECTOR Cto12Segmtnt = Line_Segment_Point_VECTOR(A, VAdd(A, VGet(0, aHeight, 0)), Cto12Segmtnt12);
	VECTOR Cto20Segmtnt = Line_Segment_Point_VECTOR(A, VAdd(A, VGet(0, aHeight, 0)), Cto20Segmtnt20);

	Cto01Segmtnt01 = Line_Segment_Point_VECTOR(poly[0], poly[1], Cto01Segmtnt);
	Cto12Segmtnt12 = Line_Segment_Point_VECTOR(poly[1], poly[2], Cto12Segmtnt);
	Cto20Segmtnt20 = Line_Segment_Point_VECTOR(poly[2], poly[0], Cto20Segmtnt);

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

	VECTOR normal = PolygonNormalize(poly[0], poly[1], poly[2]);

	if (VSize(VSub(closestSegmentEnd, closestSegmentStart)) <= aRadius)
	{
		// 押し戻しベクトルの計算
		VECTOR pushBack = VScale(normal, aRadius - minDist);

		// カプセルの位置を更新
		return VAdd(A, pushBack);
	}

}

