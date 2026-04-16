#pragma once
#ifndef BUILD_STATIC
	#ifdef YQMATH_EXPORTS
		#define YQMath_EXPORT __declspec(dllexport)
	#else
		#define YQMath_EXPORT __declspec(dllimport)
	#endif // YQOPENGL_EXPORTS
#else
	#define YQMath_EXPORT
#endif