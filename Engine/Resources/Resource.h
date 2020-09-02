#pragma once
#include <string>

namespace nc
{
	class Resource
	{
	public:
		virtual bool create(const std::string& name, void* data = nullptr) = 0;
		virtual void destroy() = 0;
	};
}