#include "DxLib.h"
#include "Pad.h"

//#define USE_EXCEL_DATA

#ifdef USE_EXCEL_DATA
#include "ExcelSoundManager.h"
#else
#include "CsvSoundManager.h"
#endif

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

#ifdef USE_EXCEL_DATA
	ExcelSoundManager::getInstance().init();
//	ExcelSoundManager::getInstance().play(SndId_bgmTest);
#else
	CsvSoundManager::getInstance().init();
//	CsvSoundManager::getInstance().play("bgmTest");
#endif

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
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

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

#ifdef USE_EXCEL_DATA
	ExcelSoundManager::getInstance().end();
	ExcelSoundManager::destroy();
#else
	CsvSoundManager::getInstance().end();
	CsvSoundManager::destroy();
#endif

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}