#include "pch.h"
#include "Texture.h"
#include "Core.h"
#include "ResourceManager.h"

void ResourceManager::Init() {
	GetCurrentDirectory(255, m_resourcePath);
	wcscat_s(m_resourcePath, 255, L"\\Resource\\");
	::SetWindowText(GET_SINGLE(Core)->GetHWnd(), m_resourcePath);

	FMOD::System_Create(&m_pSoundSystem); // �ý��� ���� �Լ�
	// ä�μ�, ���� ���
	if (m_pSoundSystem != nullptr)
		m_pSoundSystem->init((int)SOUND_CHANNEL::END, FMOD_INIT_NORMAL, nullptr);
}

Texture* ResourceManager::TextureLoad(const wstring& key, const wstring& path) {
	Texture* pTex = TextureFind(key);
	if (pTex != nullptr)
		return pTex;

	wstring texPath = m_resourcePath;
	texPath += path;

	pTex = new Texture;
	pTex->Load(texPath);
	pTex->SetKey(key);
	pTex->SetPath(texPath);
	m_mapTextures.insert({ key, pTex });
	return pTex;
}

Texture* ResourceManager::TextureFind(const wstring& key) {
	auto iter = m_mapTextures.find(key);
	if (iter != m_mapTextures.end())
		return iter->second;
	return nullptr;
}

void ResourceManager::Release() {
	map<wstring, Texture*>::iterator iter;
	for (iter = m_mapTextures.begin(); iter != m_mapTextures.end();)
		delete iter++->second;

	m_mapTextures.clear();
}

void ResourceManager::LoadSound(const wstring& _key, const wstring& _path, bool _isLoop) {
	if (FindSound(_key))
		return;
	wstring strFilePath = m_resourcePath;
	strFilePath += _path;

	// wstring to string
	std::string str;
	str.assign(strFilePath.begin(), strFilePath.end());

	// �������� ���� ����
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // �ݺ� ���
	if (!_isLoop)
		eMode = FMOD_DEFAULT; // ���� 1���� ���

	tSoundInfo* ptSound = new tSoundInfo;
	ptSound->IsLoop = _isLoop;
	// ���� ��ü�� ����� ���� system��.
							//���ϰ��,  FMOD_MODE, NULL, &sound
	m_pSoundSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->pSound);
	m_mapSounds.insert({ _key, ptSound });
}

void ResourceManager::Play(const wstring& _key) {
	tSoundInfo* ptSound = FindSound(_key);
	if (!ptSound)
		return;
	m_pSoundSystem->update(); // play�Ҷ� update�� �ֱ������� ȣ���ؾ� ���尡 �������� ����.
	SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
	if (!ptSound->IsLoop)
		eChannel = SOUND_CHANNEL::EFFECT;
	// ���� ��� �Լ�. &channel�� � ä���� ���� ����Ǵ��� ������ �ѱ�
	m_pSoundSystem->playSound(ptSound->pSound, nullptr, false, &m_pChannel[(UINT)eChannel]);
}

void ResourceManager::Stop(SOUND_CHANNEL _channel) {
	m_pChannel[(UINT)_channel]->stop();
}

void ResourceManager::Volume(SOUND_CHANNEL _channel, float _vol) {
	// 0.0 ~ 1.0 ���� ����
	m_pChannel[(UINT)_channel]->setVolume(_vol);
}

void ResourceManager::Pause(SOUND_CHANNEL _channel, bool _ispause) {
	// bool���� true�� �Ͻ�����. ��, �� �Լ��� ������ Createsound�Ҷ� 
	// FMOD_MODE�� FMOD_LOOP_NORMAL �̾�� ��.
	m_pChannel[(UINT)_channel]->setPaused(_ispause);
}

tSoundInfo* ResourceManager::FindSound(const wstring& _key) {
	map<wstring, tSoundInfo*>::iterator iter = m_mapSounds.find(_key);

	if (iter == m_mapSounds.end())
		return nullptr;
	return iter->second;
}
