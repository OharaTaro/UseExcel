#include "CsvSoundManager.h"
#include "DxLib.h"

#include <cassert>
#include <fstream>
#include <sstream>

CsvSoundManager* CsvSoundManager::m_instance = nullptr;

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

void CsvSoundManager::init()
{
	// cvs�t�@�C���̓ǂݍ���
	std::ifstream ifs("data/csv/CsvSoundData.csv");
	std::string line;

	// 1�s�ڂ͓ǂݎ̂�
	getline(ifs, line);

	while (getline(ifs, line))
	{
		// csv�f�[�^1�s��','�ŕ����̕�����ɕ���
		std::vector<std::string>	strvec = split(line, ',');

		// strvec[0]	: id			string
		// strvec[1]	: BGM�t���O		string (BGM or SE)
		// strvec[2]	: �t�@�C����	string
		// strvec[3]	: vol			float

		SoundData data;
		if (strvec[1] == "SE")
		{
			data.isBgm = false;
		}
		else if (strvec[1] == "BGM")
		{
			data.isBgm = true;
		}
		else
		{
			assert(false);
		}

		data.volume = stof(strvec[3]);

		data.handle = LoadSoundMem(strvec[2].c_str());
		//printfDx(strvec[2].c_str());
		m_data[strvec[0]] = data;
	}
}

void CsvSoundManager::end()
{
	// �T�E���h��������������
	for (auto& data : m_data)
	{
		DeleteSoundMem(data.second.handle);
	}
}

void CsvSoundManager::play(std::string id)
{
//	int result = PlaySoundMem(m_data[id].handle, DX_PLAYTYPE_BACK);	// BGM�Ȃ烋�[�v�Đ��Ƃ�����
	int result = PlaySoundMem(m_data.at(id).handle, DX_PLAYTYPE_BACK);	// BGM�Ȃ烋�[�v�Đ��Ƃ�����
	// �{�����[���̐ݒ�Ƃ������

	if (result == -1)
	{
		printfDx(id.c_str());
		printfDx(" �T�E���h���Đ��ł��܂���ł���\n");
	}
}

void CsvSoundManager::stop(std::string id)
{
	StopSoundMem(m_data.at(id).handle);
}
