#pragma once
#include <DxLib.h>

class MathLib
{
private:
public:

	/*数学関数*/

	//値を強制的に_minVal～_maxValの間の範囲内にすること
	float Clamp(float _minVal, float _maxVal, float _val);
	
	//VECTORとfloatの掛け算
	VECTOR Vector_X_float(VECTOR _vval, float _fval);

	/*線と線*/
	bool CheckLineIntersection(VECTOR _posStart1, VECTOR _posEnd1, VECTOR _posStart2, VECTOR _posEnd2);//当たり判定
	
	//========================================================
	// ポリゴン関連
	//========================================================
	//ポリゴンの法線ベクトルを求める
	VECTOR PolygonNormalize(VECTOR A, VECTOR B, VECTOR C);
	//ポリゴンの重心を求める（中心座標）
	VECTOR PolygonCenter(VECTOR A, VECTOR B, VECTOR C);
	
	float Distance_Target_Polygon(VECTOR A, VECTOR B, VECTOR C, VECTOR P);

	


	//========================================================
	// 最近点線関連
	//========================================================
	/// <summary>
	/// 線分と点の最近点線
	/// </summary>
	/// <param name="A">線の端</param>
	/// <param name="B">線の端</param>
	/// <param name="P">点</param>
	/// <returns>最近点線の座標:VECTOR型</returns>
	VECTOR Line_Segment_Point_VECTOR(VECTOR A, VECTOR B, VECTOR P);
	/// <summary>
	/// 線分と点の最近点線
	/// </summary>
	/// <param name="A">線の端</param>
	/// <param name="B">線の端</param>
	/// <param name="P">点</param>
	/// <returns>最近点線の距離:float型</returns>
	float Line_Segment_Point_FLOAT(VECTOR A, VECTOR B, VECTOR P);
	

	/// <summary>
	/// 線分と線分の最近点線
	/// </summary>
	/// <param name="A"></param>
	/// <param name="aHeight"></param>
	/// <param name="B"></param>
	/// <param name="bHeight"></param>
	/// <returns>最近点線の座標:VECTOR型</returns>
	VECTOR Line_Segment_Line_VECTOR(VECTOR A, float aHeight, VECTOR B, float bHeight);

	/// <summary>
	/// 線分と線分の最近点線
	/// </summary>
	/// <param name="A"></param>
	/// <param name="aHeight"></param>
	/// <param name="B"></param>
	/// <param name="bHeight"></param>
	/// <returns> 最近点線の距離：float型</returns>
	float Line_Segment_Line_FLOAT(VECTOR A, float aHeight, VECTOR B, float bHeight);


	//========================================================
	// カプセルとカプセルの当たり判定
	//========================================================
	bool Capsule_Capsule_HitCheck(VECTOR A, float aHeight, float aRadius, VECTOR B, float bHeight, float bRadius);


	//========================================================
	// カプセルと三角形の当たり判定
	//========================================================
	
	/// <summary>
	/// ポリゴンとカプセルの当たり判定
	/// </summary>
	/// <param name="A"></param>
	/// <param name="aHeight"></param>
	/// <param name="aRadius"></param>
	/// <param name="poly"></param>
	/// <returns></returns>
	bool Polygon_Capsule_HitCheck(VECTOR A, float aHeight, float aRadius, VECTOR poly[3]);

	/// <summary>
	/// ポリゴンとカプセルの押し戻しベクトルを求める
	/// </summary>
	/// <param name="A"></param>
	/// <param name="aHeight"></param>
	/// <param name="aRadius"></param>
	/// <param name="poly"></param>
	/// <returns></returns>
	VECTOR Polygon_Capsule_PushBack(VECTOR A, float aHeight, float aRadius, VECTOR poly[3]);


};

