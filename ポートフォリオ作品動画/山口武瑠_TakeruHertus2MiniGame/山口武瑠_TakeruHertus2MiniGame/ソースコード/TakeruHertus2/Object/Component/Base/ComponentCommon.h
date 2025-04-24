#pragma once

//===========================================//
//	全てのコンポーネントのヘッダーファイル
//===========================================//

/*カメラ系*/
#include "../ComponentCamera/Control/ComponentCameraControl.h"

/*移動系*/
#include "../ComponentTransform/ComponentTransform.h"

#include "../ComponentMovement/ComponentMovement.h"

#include "../ComponentAnimation/ComponentAnimation.h"

/*描画系*/
#include "../ComponentGraph/ComponentGraph.h"//画像
#include "../ComponentModel/ComponentModel.h"//３Dモデル
#include "../ComponentFont/ComponentFont.h"	 //フォント


/*物理処理*/
#include "../ComponentPhsycs/RightBody/ComponentRightBody.h"
#include "../ComponentPhsycs/Capsule/ComponentCapsule.h"
#include "../ComponentPhsycs/Sphere/ComponentSphere.h"

/*コンボ系*/
#include "../ComponentComboSystem/ComponentComboSystem.h"//コンボシステム

/*ステータス*/
#include "../ComponentStatus/ComponentStatus.h"