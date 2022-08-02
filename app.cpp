/**
 ******************************************************************************
 ** ファイル名 : app.c
 **
 ** 概要 : 二輪差動型ライントレースロボットのTOPPERS/HRP3用Cサンプルプログラム
 **
 ** 注記 : sample_c4 (sample_c3にBluetooth通信リモートスタート機能を追加)
 ******************************************************************************
 **/
#include "ev3api.h"
#include "app.h"
#include "etroboc_ext.h"
#include "./workspace/include/FileOp/FileIO.hpp"
#include "./workspace/include/SceneInfo/SceneInfo.hpp"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif
bool flag = false;
/**
 * EV3システム生成
 * モーター設定
 */
static void user_system_create()
{

}
static void user_system_destroy()
{

}
/*  スタート処理タスク */
void start_task(intptr_t unused)
{

    

    ev3_sensor_config(EV3_PORT_1, TOUCH_SENSOR);
    /* 動的に生成するインスタンスの初期化 */
    user_system_create();
	user_system_destroy();
    //フライング
    while (1)
    {
        if (ev3_touch_sensor_is_pressed(EV3_PORT_1) == 1)
        {
            break;
        }
        tslp_tsk(10 * 1000U);
    }

    act_tsk(MAIN_TASK);
    ext_tsk();
}

/* メインタスク */
void main_task(intptr_t unused)
{
	// シミュレータでファイル操作する方法
	// simdistの__ev3rtfsにcsvファイルを入れる
	// 名前は↓これにしてほしいな
	// timeAttack.csv
	// slalom.csv
	// slalom1.csv  パターン１
	// slalom2.csv　パターン２
	// garage.csv
	// garage1.csv　パターン１
	// garage2.csv　パターン２

	SceneInfo& sceneInfo    = SceneInfo::getInstance();
	sceneInfo.init();
	SceneData sceneData;

	// get(scenarioType,シーン番号,パターン)
	// パターン１を選択したい場合は1を入力
	sceneData = sceneInfo.get(TIMEATTACK,1,common);
	sceneData = sceneInfo.get(SLALOM,1,common);
	sceneData = sceneInfo.get(SLALOM,1,pattern1);
	sceneData = sceneInfo.get(SLALOM,1,pattern2);
	sceneData = sceneInfo.get(GARAGE,1,common);
	sceneData = sceneInfo.get(GARAGE,1,pattern1);
	sceneData = sceneInfo.get(GARAGE,1,pattern2);

	// 動作情報の取り出し方
	printf ("使用動作=%d\n", sceneData.moveData.motion);
	printf ("ライン位置=%d\n", sceneData.moveData.edge);
	printf ("PID.p=%0.1f\n", sceneData.moveData.gain.p);
	printf ("PID.i=%0.1f\n", sceneData.moveData.gain.i);
	printf ("PID.d=%0.1f\n", sceneData.moveData.gain.d);
	printf ("閾値=%0.1f\n", sceneData.moveData.target_val);
	printf ("速度=%0.1f\n", sceneData.moveData.speed);
	printf ("半径=%0.1f\n", sceneData.moveData.radius);
	printf ("座標ｘ=%0.1f\n", sceneData.moveData.coordinate.x);
	printf ("座標ｙ=%0.1f\n", sceneData.moveData.coordinate.y);
	printf ("旋回方向=%d\n", sceneData.moveData.direction);
	printf ("アーム位置=%d\n", sceneData.moveData.arm_angle);
	printf ("アーム速度=%d\n", sceneData.moveData.arm_pwm);
	// 判定の取り出し方
	printf ("動作使用判定1=%d\n", sceneData.decisionData.decision[0]);
	printf ("動作使用判定2=%d\n", sceneData.decisionData.decision[1]);
	printf ("座標範囲ｘ=%d\n", sceneData.decisionData.coordinate.x);
	printf ("座標範囲ｙ=%d\n", sceneData.decisionData.coordinate.y);
	printf ("目標座標ｘ=%0.1f\n", sceneData.decisionData.coordinate_range[0]);
	printf ("目標座標ｙ=%0.1f\n", sceneData.decisionData.coordinate_range[1]);
	printf ("距離範囲=%d\n", sceneData.decisionData.distance_range);
	printf ("目標距離=%d\n", sceneData.decisionData.distance);
	printf ("目標色=%d\n", sceneData.decisionData.color);
	printf ("R範囲=%d\n", sceneData.decisionData.rgb_range[0]);
	printf ("g範囲=%d\n", sceneData.decisionData.rgb_range[1]);
	printf ("b範囲=%d\n", sceneData.decisionData.rgb_range[2]);
	printf ("R=%d\n", sceneData.decisionData.rgb.r);
	printf ("g=%d\n", sceneData.decisionData.rgb.g);
	printf ("b=%d\n", sceneData.decisionData.rgb.b);
	printf ("h範囲=%d\n", sceneData.decisionData.hsv_range[0]);
	printf ("s範囲=%d\n", sceneData.decisionData.hsv_range[1]);
	printf ("v範囲=%d\n", sceneData.decisionData.hsv_range[2]);
	printf ("h=%d\n", sceneData.decisionData.hsv.h);
	printf ("s=%d\n", sceneData.decisionData.hsv.s);
	printf ("v=%d\n", sceneData.decisionData.hsv.v);
	printf ("角度範囲=%d\n", sceneData.decisionData.angle_range);
	printf ("目標角度=%0.1f\n", sceneData.decisionData.angle);
	printf ("論理演算方法=%d\n", sceneData.decisionData.logic);
	// 補正情報の取り出し方
	printf ("使用補正ｘ=%d\n", sceneData.correctionData.correction[0]);
	printf ("使用補正ｙ=%d\n", sceneData.correctionData.correction[1]);
	printf ("使用補正角度=%d\n", sceneData.correctionData.correction[2]);
	printf ("補正座標ｘ=%0.1f\n", sceneData.correctionData.coordinate.x);
	printf ("補正座標ｙ=%0.1f\n", sceneData.correctionData.coordinate.y);
	printf ("補正角度=%0.1f\n", sceneData.correctionData.angle);
	// 補正用判定の取り出し方
	printf ("補正使用判定1=%d\n", sceneData.correctionData.decisionData.decision[0]);
	printf ("補正使用判定2=%d\n", sceneData.correctionData.decisionData.decision[1]);
	printf ("座標範囲ｘ=%d\n", sceneData.correctionData.decisionData.coordinate.x);
	printf ("座標範囲ｙ=%d\n", sceneData.correctionData.decisionData.coordinate.y);
	printf ("目標座標ｘ=%0.1f\n", sceneData.correctionData.decisionData.coordinate_range[0]);
	printf ("目標座標ｙ=%0.1f\n", sceneData.correctionData.decisionData.coordinate_range[1]);
	printf ("距離範囲=%d\n", sceneData.correctionData.decisionData.distance_range);
	printf ("目標距離=%d\n", sceneData.correctionData.decisionData.distance);
	printf ("目標色=%d\n", sceneData.correctionData.decisionData.color);
	printf ("R範囲=%d\n", sceneData.correctionData.decisionData.rgb_range[0]);
	printf ("g範囲=%d\n", sceneData.correctionData.decisionData.rgb_range[1]);
	printf ("b範囲=%d\n", sceneData.correctionData.decisionData.rgb_range[2]);
	printf ("R=%d\n", sceneData.correctionData.decisionData.rgb.r);
	printf ("g=%d\n", sceneData.correctionData.decisionData.rgb.g);
	printf ("b=%d\n", sceneData.correctionData.decisionData.rgb.b);
	printf ("h範囲=%d\n", sceneData.correctionData.decisionData.hsv_range[0]);
	printf ("s範囲=%d\n", sceneData.correctionData.decisionData.hsv_range[1]);
	printf ("v範囲=%d\n", sceneData.correctionData.decisionData.hsv_range[2]);
	printf ("h=%d\n", sceneData.correctionData.decisionData.hsv.h);
	printf ("s=%d\n", sceneData.correctionData.decisionData.hsv.s);
	printf ("v=%d\n", sceneData.correctionData.decisionData.hsv.v);
	printf ("角度範囲=%d\n", sceneData.correctionData.decisionData.angle_range);
	printf ("目標角度=%0.1f\n", sceneData.correctionData.decisionData.angle);
	printf ("論理演算方法=%d\n", sceneData.correctionData.decisionData.logic);

}
