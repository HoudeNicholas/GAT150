#pragma once
#include "Core/System.h"
#include <fmod.hpp>

namespace nc
{
	class AudioSystem : public System
	{
	public:
		virtual bool startup() override;
		virtual void shutdown() override;
		virtual void update() override;
		
		friend class Sound;

	protected:
		FMOD::System* m_system{ nullptr };

	};
}
