#pragma once
#include "Components/Component.h"
#include "Audio/AudioChannel.h"

namespace nc
{
	class AudioComponent : public Component
	{
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		Object* Clone() const { return new AudioComponent{ *this }; }

		void read(const rapidjson::Value& value) override;

		virtual void update() override;

		void Play();
		void Stop();
		void SetSoundName(const std::string& soundName) { m_soundName = soundName; }

	protected:
		std::string m_soundName;
		bool m_loop{ false };
		bool m_playOnAwake{ false };

		AudioChannel m_channel;
	};
}
