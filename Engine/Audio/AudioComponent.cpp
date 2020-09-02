#include "pch.h"
#include "AudioComponent.h"
#include "Audio/Sound.h"
#include "Audio/AudioSystem.h"

namespace nc
{
	bool AudioComponent::create(void* data)
	{
		owner = static_cast<GameObject*>(data);
		return true;
	}

	void AudioComponent::destroy()
	{
		m_channel.Stop();
	}

	void AudioComponent::read(const rapidjson::Value& value)
	{
		json::Get(value, "sound", m_soundName);
		json::Get(value, "loop", m_loop);
		json::Get(value, "playOnAwake", m_playOnAwake);

		if (m_playOnAwake)
		{
			Play();
		}
	}

	void AudioComponent::update()
	{
	}

	void AudioComponent::Play()
	{
		m_channel.Stop();

		Sound* sound = owner->engine->getSystem<nc::ResourceManager>()->Get<nc::Sound>(m_soundName, owner->engine->getSystem<nc::AudioSystem>());
		ASSERT_MSG((sound), "Could not find sound: " + m_soundName);
		m_channel = sound->Play(m_loop);
	}

	void AudioComponent::Stop()
	{
		m_channel.Stop();
	}
}
