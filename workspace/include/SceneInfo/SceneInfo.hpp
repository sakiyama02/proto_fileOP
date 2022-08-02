#pragma once



#include <vector>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../FileOp/FileIO.hpp"

using namespace std;

typedef struct GAIN_TAG {
	float p;
	float i;
	float d;
}GAIN;

typedef struct COORDINATE_TAG {
	float x;
	float y;
}COORDINATE;


typedef struct RGB_TAG {	
	unsigned short r;
	unsigned short g;
	unsigned short b;
}RGB_DATA;

//HSVの構造体
typedef struct HSV_TAG {	
	unsigned short h;
	unsigned short s;
	unsigned short v;
}HSV_DATA;

enum Motion{
	LINETRACE,
	CURVE,
	TURN,
	STRAIGHT
};

struct MoveData
{
	unsigned char motion;				// 使用動作
	unsigned char edge;				// ライントレース位置（右ライン or 左ライン）
	GAIN gain;					// ゲイン
	float target_val;			// 閾値
	float speed;				// 目標速度
	float radius;				// カーブ半径
	COORDINATE coordinate;		// 目標座標
	unsigned char direction;			// 旋回方向
	short arm_angle;			// アーム角度
	int arm_pwm;				// アーム速度
};

struct DecisionData
{
	unsigned char decision[2];			// 使用判定
	COORDINATE coordinate;			// 目標座標
	unsigned char coordinate_range[2];	// 目標座標範囲
	unsigned char color;					// 目標色
	unsigned short distance;				// 目標距離
	unsigned char distance_range;			// 目標距離範囲
	RGB_DATA rgb;					// 目標RGB
	unsigned char rgb_range[3];			// 使用RGB
	HSV_DATA hsv;					// 目標HSV
	unsigned char hsv_range[3];			// 使用HSV
	float angle;					// 目標角度
	unsigned char angle_range;			// 目標角度範囲
	unsigned char logic;					// 論理演算方法
};

struct CorrectionData
{
	COORDINATE coordinate; 		// 補正座標
	float angle;				// 補正角度
	unsigned char correction[3];			// 使用軸
	DecisionData decisionData;	// 判定情報クラス
};

struct SceneData
{
	int num;
	MoveData moveData;
	DecisionData decisionData;
	CorrectionData correctionData;
};

enum ScenarioType{
	TIMEATTACK,
	SLALOM,
	GARAGE,
};

enum Pattern{
	common,
	pattern1,
	pattern2,
};


class SceneInfo{
	protected:
	//SceneInfo(){};

	private:

		vector<SceneData> timeAttackData;
		vector<vector<SceneData> > slalomData{3};  // 0=共通,1=パターン1,2=パターン2
		vector<vector<SceneData> > garageData{3};  // 0=共通,1=パターン1,2=パターン2
		
	public:
		SceneInfo(){	

		};
		char init();
		char decode(vector<char>& fileData,vector<SceneData>& sceneData);
		SceneData get(ScenarioType scenario,int scene,Pattern pattern);
		int get(ScenarioType scenario,Pattern pattern);
};