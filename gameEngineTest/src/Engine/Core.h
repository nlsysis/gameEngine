#pragma once

#ifdef EG_PLATFORM_WINDOWS
	#ifdef EG_BUILD_DLL
		#define  EG_API  _declspec(dllexport)
	#else
		#define EG_API _declspec(dllimport)
	#endif
#else
	#error This engine only support windows.
#endif