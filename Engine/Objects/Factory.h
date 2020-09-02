#pragma once
#include <functional>
#include <map>


namespace nc
{

	template<typename TBase, typename TKey>
	class Factory
	{
	public:
		using function_t = std::function<TBase*()>;

	public:
		template<typename T = TBase>

		T* create(TKey key);
		void registerThing(TKey key, function_t function);

	protected:
		std::map<TKey, function_t> registry;


	};


	template<typename TBase, typename TKey>
	template<typename T>
	inline T* Factory<TBase, TKey>::create(TKey key)
	{
		T* object = nullptr;

		auto iter = registry.find(key);
		if (iter != registry.end()) {
			object = dynamic_cast<T*>(iter->second());
		}

		return object;
	}



	template<typename TBase, typename TKey>
	inline void Factory<TBase, TKey>::registerThing(TKey key, function_t function)
	{
		registry[key] = function;

	}
}