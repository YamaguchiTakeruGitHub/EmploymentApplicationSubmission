#pragma once
#include <DxLib.h>

class MathLib
{
private:
public:

	/*���w�֐�*/

	//�l�������I��_minVal�`_maxVal�̊Ԃ͈͓̔��ɂ��邱��
	float Clamp(float _minVal, float _maxVal, float _val);
	
	//VECTOR��float�̊|���Z
	VECTOR Vector_X_float(VECTOR _vval, float _fval);

	/*���Ɛ�*/
	bool CheckLineIntersection(VECTOR _posStart1, VECTOR _posEnd1, VECTOR _posStart2, VECTOR _posEnd2);//�����蔻��
	
	//========================================================
	// �|���S���֘A
	//========================================================
	//�|���S���̖@���x�N�g�������߂�
	VECTOR PolygonNormalize(VECTOR A, VECTOR B, VECTOR C);
	//�|���S���̏d�S�����߂�i���S���W�j
	VECTOR PolygonCenter(VECTOR A, VECTOR B, VECTOR C);
	
	float Distance_Target_Polygon(VECTOR A, VECTOR B, VECTOR C, VECTOR P);

	


	//========================================================
	// �ŋߓ_���֘A
	//========================================================
	/// <summary>
	/// �����Ɠ_�̍ŋߓ_��
	/// </summary>
	/// <param name="A">���̒[</param>
	/// <param name="B">���̒[</param>
	/// <param name="P">�_</param>
	/// <returns>�ŋߓ_���̍��W:VECTOR�^</returns>
	VECTOR Line_Segment_Point_VECTOR(VECTOR A, VECTOR B, VECTOR P);
	/// <summary>
	/// �����Ɠ_�̍ŋߓ_��
	/// </summary>
	/// <param name="A">���̒[</param>
	/// <param name="B">���̒[</param>
	/// <param name="P">�_</param>
	/// <returns>�ŋߓ_���̋���:float�^</returns>
	float Line_Segment_Point_FLOAT(VECTOR A, VECTOR B, VECTOR P);
	

	/// <summary>
	/// �����Ɛ����̍ŋߓ_��
	/// </summary>
	/// <param name="A"></param>
	/// <param name="aHeight"></param>
	/// <param name="B"></param>
	/// <param name="bHeight"></param>
	/// <returns>�ŋߓ_���̍��W:VECTOR�^</returns>
	VECTOR Line_Segment_Line_VECTOR(VECTOR A, float aHeight, VECTOR B, float bHeight);

	/// <summary>
	/// �����Ɛ����̍ŋߓ_��
	/// </summary>
	/// <param name="A"></param>
	/// <param name="aHeight"></param>
	/// <param name="B"></param>
	/// <param name="bHeight"></param>
	/// <returns> �ŋߓ_���̋����Ffloat�^</returns>
	float Line_Segment_Line_FLOAT(VECTOR A, float aHeight, VECTOR B, float bHeight);


	//========================================================
	// �J�v�Z���ƃJ�v�Z���̓����蔻��
	//========================================================
	bool Capsule_Capsule_HitCheck(VECTOR A, float aHeight, float aRadius, VECTOR B, float bHeight, float bRadius);


	//========================================================
	// �J�v�Z���ƎO�p�`�̓����蔻��
	//========================================================
	
	/// <summary>
	/// �|���S���ƃJ�v�Z���̓����蔻��
	/// </summary>
	/// <param name="A"></param>
	/// <param name="aHeight"></param>
	/// <param name="aRadius"></param>
	/// <param name="poly"></param>
	/// <returns></returns>
	bool Polygon_Capsule_HitCheck(VECTOR A, float aHeight, float aRadius, VECTOR poly[3]);

	/// <summary>
	/// �|���S���ƃJ�v�Z���̉����߂��x�N�g�������߂�
	/// </summary>
	/// <param name="A"></param>
	/// <param name="aHeight"></param>
	/// <param name="aRadius"></param>
	/// <param name="poly"></param>
	/// <returns></returns>
	VECTOR Polygon_Capsule_PushBack(VECTOR A, float aHeight, float aRadius, VECTOR poly[3]);


};

