#include "DxLib.h"
#include "Pad.h"

//#define USE_EXCEL_DATA

#ifdef USE_EXCEL_DATA
#include "ExcelSoundManager.h"
#else
#include "CsvSoundManager.h"
#endif

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

#ifdef USE_EXCEL_DATA
	ExcelSoundManager::getInstance().init();
//	ExcelSoundManager::getInstance().play(SndId_bgmTest);
#else
	CsvSoundManager::getInstance().init();
//	CsvSoundManager::getInstance().play("bgmTest");
#endif

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理
		Pad::update();

		if (Pad::isTrigger(PAD_INPUT_1))
		{
#ifdef USE_EXCEL_DATA
			ExcelSoundManager::getInstance().play(SndId_decide);
#else
			CsvSoundManager::getInstance().play("decide");
#endif
		}
		if (Pad::isTrigger(PAD_INPUT_2))
		{
#ifdef USE_EXCEL_DATA
			ExcelSoundManager::getInstance().play(SndId_cancel);
#else
			CsvSoundManager::getInstance().play("cancel");
#endif
		}
		if (Pad::isTrigger(PAD_INPUT_3))
		{
#ifdef USE_EXCEL_DATA
			ExcelSoundManager::getInstance().play(SndId_attack);
#else
			CsvSoundManager::getInstance().play("attack");
#endif
		}

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

#ifdef USE_EXCEL_DATA
	ExcelSoundManager::getInstance().end();
	ExcelSoundManager::destroy();
#else
	CsvSoundManager::getInstance().end();
	CsvSoundManager::destroy();
#endif

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}