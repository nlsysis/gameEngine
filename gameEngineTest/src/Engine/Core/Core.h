#pragma once

#include <memory>

#ifdef EG_PLATFORM_WINDOWS
#if EG_DYNAMIC_LINK
	#ifdef EG_BUILD_DLL
		#define  EG_API  _declspec(dllexport)
	#else
		#define EG_API _declspec(dllimport)
	#endif
#else
	#define  EG_API
#endif
#else
	#error This engine only support windows.
#endif

#ifdef EG_DEBUG
	#define EG_ENABLE_ASSERTS
#endif

#ifdef EG_ENABLE_ASSERTS
	#define EG_ASSERT(x, ...) {if(!x) {EG_ERROR("Asserting Failed:{0}",__VA_ARGS__); __debugbreak; } }
	#define EG_CORE_ASSERT(x, ...) {if(!x) {EG_CORE_ERROR("Asserting Failed:{0}",__VA_ARGS__); __debugbreak; } }
#else
	#define EG_ASSERT(x, ...) 
	#define EG_CORE_ASSERT(x, ...) 
#endif // EG_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define EG_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)

namespace Engine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}