#pragma once

#include <vector>
#include <string>
#include <map>


// cvs�t�@�C������f�[�^��ǂݎ���ĊǗ�����N���X
class CsvSoundManager
{
private:
	CsvSoundManager() = default;
	virtual ~CsvSoundManager() = default;

	static CsvSoundManager* m_instance;

public:
	// �R�s�[�R���X�g���N�^�̋֎~
	CsvSoundManager(const CsvSoundManager&) = delete;
	CsvSoundManager& operator=(const CsvSoundManager&) = delete;
	CsvSoundManager(CsvSoundManager&&) = delete;
	CsvSoundManager& operator=(CsvSoundManager&&) = delete;

	static CsvSoundManager& getInstance()
	{
		if (!m_instance)
		{
			m_instance = new CsvSoundManager;
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
	void play(std::string id);
	// �T�E���h�̒�~
	void stop(std::string id);
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
	std::map<std::string, SoundData>		m_data;
};

