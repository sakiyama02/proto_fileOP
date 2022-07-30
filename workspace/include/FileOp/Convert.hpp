/*
*	Convertクラス
*	作成者：崎山
*/

#pragma once

#include <vector>
#include <string>

struct MoveData
{
	// 使用動作
	// ライントレース位置（右ライン or 左ライン）
	// ゲイン
	// 閾値
	// 目標速度
	// カーブ半径
	// 目標座標
	// 旋回方向
	// アーム角度
	// アーム速度
};

struct DecisionData
{
	// 使用判定
	// 目標座標
	// 目標色
	// 目標距離
	// 目標RGB
	// 使用RGB
	// 目標HSV
	// 使用HSV
	// 目標角度
	// 目標範囲
	// 論理演算方法
};

struct CorrectionData
{
	// 補正座標
	// 補正角度
	// 使用軸
	// 判定情報クラス
};

struct SceneRawData
{
	
};


class Convert {
	private:
	public:
		int8_t decode();
};