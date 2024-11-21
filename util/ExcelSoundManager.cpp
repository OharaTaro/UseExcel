#include "ExcelSoundManager.h"
#include "DxLib.h"

#include <cassert>
#include <fstream>
#include <sstream>

ExcelSoundManager* ExcelSoundManager::m_instance = nullptr;

namespace
{
	// input�����������delimiter�ŕ�������
	// ������̕������Ԃ�
	std::vector<std::string> split(std::string& input, char delimiter)
	{
		std::istringstream stream(input);	// string��getline�Ŏg����f�[�^�ɕϊ��H
		std::string field;					// ��������������1�����i�[����H
		std::vector<std::string> result;	// ������̕�����̔z��

		while (getline(stream, field, delimiter))
		{
			result.push_back(field);
		}
		return result;
	}
}

void ExcelSoundManager::init()
{
	// cvs�t�@�C���̓ǂݍ���
	std::ifstream ifs("data/csv/ExcelSoundData.csv");
	std::string line;

	// ���o���s�͏o�͂��Ă��Ȃ��̂œǂݎ̂Ă͕s�v
//	// 1�s�ڂ͓ǂݎ̂�
//	getline(ifs, line);

	while (getline(ifs, line))
	{
		// csv�f�[�^1�s��','�ŕ����̕�����ɕ���
		std::vector<std::string>	strvec = split(line, ',');

		// strvec[0]	: BGM�t���O		string (0 or 1)
		// strvec[1]	: �t�@�C����	string
		// strvec[2]	: vol			float

		SoundData data;
		if (strvec[0] == "0")
		{
			data.isBgm = false;
		}
		else if (strvec[0] == "1")
		{
			data.isBgm = true;
		}
		else
		{
			assert(false);
		}
		data.volume = stof(strvec[2]);
		data.handle = LoadSoundMem(strvec[1].c_str());

		m_data.push_back(data);
	}
}

void ExcelSoundManager::end()
{
	// �T�E���h��������������
	for (auto& data : m_data)
	{
		DeleteSoundMem(data.handle);
	}
}

void ExcelSoundManager::play(int id)
{
	int result = PlaySoundMem(m_data.at(id).handle, DX_PLAYTYPE_BACK);	// BGM�Ȃ烋�[�v�Đ��Ƃ�����
	// �{�����[���̐ݒ�Ƃ������

	if (result == -1)
	{
		printfDx("�T�E���h���Đ��ł��܂���ł��� id = %d\n", id);
	}
}

void ExcelSoundManager::stop(int id)
{
	StopSoundMem(m_data.at(id).handle);
}
