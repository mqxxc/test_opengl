#pragma once
#ifndef BUILD_STATIC
	#ifdef YQOPENGL_EXPORTS
		#define YQOpenGL_EXPORT __declspec(dllexport)
	#else
		#define YQOpenGL_EXPORT __declspec(dllimport)
	#endif // YQOPENGL_EXPORTS
#else
	#define YQOpenGL_EXPORT
#endif

