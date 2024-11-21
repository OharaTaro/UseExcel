#pragma once

#include <vector>
#include <string>

#include "SoundId.h"

// Excel����o�͂����f�[�^��ǂݎ���ĊǗ�����N���X
class ExcelSoundManager
{
private:
	ExcelSoundManager() = default;
	virtual ~ExcelSoundManager() = default;

	static ExcelSoundManager* m_instance;

public:
	// �R�s�[�R���X�g���N�^�̋֎~
	ExcelSoundManager(const ExcelSoundManager&) = delete;
	ExcelSoundManager& operator=(const ExcelSoundManager&) = delete;
	ExcelSoundManager(ExcelSoundManager&&) = delete;
	ExcelSoundManager& operator=(ExcelSoundManager&&) = delete;

	static ExcelSoundManager& getInstance()
	{
		if (!m_instance)
		{
			m_instance = new ExcelSoundManager;
		}
		return *m_instance;
	}
	static void destroy()
	{
		delete m_instance;
		m_instance = nullptr;
	}

public:

	// csv�ǂݍ��݁A�T�E���h�̃��[�h���s��
	void init();
	// �T�E���h�̉�����s��
	void end();
	// �T�E���h�̍Đ�
	void play(int id);
	// �T�E���h�̒�~
	void stop(int id);

private:
	struct SoundData
	{
		// csv����ǂݎ�������
		bool isBgm;				// ���ꂪBGM�����ʉ���
		//std::string filename;	// �t�@�C����
		float volume;

		// �Đ��f�[�^
		int handle;
	};
private:
	std::vector<SoundData>		m_data;
};

