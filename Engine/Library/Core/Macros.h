#ifndef __MACRO_H__
#define __MACRO_H__

#define ENGINE_COMPATIBLE_VERSION	0

#define sNull	nullptr
#define sTrue	1
#define sFalse	0

#define INITIALIZE	0
#define INVALID		((uint32)-1)

#define MAX_STRING_LEN			512
#define MAX_FILE_PATH_LEN		256
#define MAX_NAME_LEN			128
#define MAX_MODEL_TEXTURES		32

#define EPSILON_E3	(F32)(1E-3)
#define EPSILON_E4	(F32)(1E-4)
#define EPSILON_E5	(F32)(1E-5)
#define EPSILON_E6	(F32)(1E-6)

#define MAX_INT32	0x7fffffff
#define MAX_UINT32	0xffffffff

#define MIN_FLOAT	1.175494351e-38F
#define MAX_FLOAT	3.402823466e+38F

#define MATH_2PI	6.2831853f
#define MATH_PI		3.1415926f
#define MATH_PI_2	1.5707963f
#define MATH_PI_4	0.7853982f

#define INV_PI		0.3183098f
#define INV_2PI		0.1591549f

#undef DEG_TO_RAD
#define DEG_TO_RAD	0.0174533f

#undef RAD_TO_DEG
#define RAD_TO_DEG	57.2958f

#ifdef _UNICODE
#ifndef _TEXT_DEFINED
#undef TEXT
#define TEXT(s)	L##s
#endif
#else
#undef TEXT
#define TEXT(s)	s
#endif

#define PATH_SEPARATOR	TEXT("\\")

// 角度转弧度
#define ANGLE_TO_RADIAN(angle)	(DEG_TO_RAD * angle)

// 弧度转角度
#define RADIAN_TO_ANGLE(radian)	(RAD_TO_DEG * radian)

//将角度限制-PI到PI之间
#define WRAP_PI(theta)									\
		{												\
			theta += MATH_PI;							\
			theta -= floor(theta * INV_2PI) * MATH_2PI;	\
			theta -= MATH_PI;							\
		}

#if ENABLE_STRIPPING_SOURCE_FILENAMES
#define __FILE_STRIPPED__ ""
#else
#define __FILE_STRIPPED__ __FILE__
#endif

// 汇编指令断点
#ifdef PLATFORM_WINDOWS
#define DEBUG_BREAK()	__debugbreak()	
#else
#define DEBUG_BREAK()	asm("int $3")
#endif

#define INLINE inline

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if (p) { delete (p); p = sNull; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); p = sNull; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)	{ if (p) { (p)->Release(); p = sNull; } }
#endif

#ifndef SAFE_FREE
#define SAFE_FREE(p) { if (p) { free(p); p = sNull; } }
#endif

#define DETAIL_PP_CONCAT(a, b) a##b
#define DETAIL_PP_EXPAND(a, b) a b

#define DETAIL_PP_VARG_CONCAT_Y(a, b) a##b
#define DETAIL_PP_VARG_CONCAT_X(a, b) DETAIL_PP_VARG_CONCAT_Y(a, b)
#define DETAIL_PP_VARG_CONCAT(a, b) DETAIL_PP_VARG_CONCAT_X(a, b)

// 可变参数
#define DETAIL_PP_VARG_COUNT(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, result, ...) result

#define PP_VARG_COUNT(...)	\
	DETAIL_PP_EXPAND(DETAIL_PP_VARG_COUNT, (__VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

#define PP_VARG_SELECT_OVERLOAD(name, args)	\
	DETAIL_PP_EXPAND(DETAIL_PP_VARG_CONCAT(name, PP_VARG_COUNT args), args)

#define UNSIGNED_FLAGS_1(flag)										static_cast<uint32>(flag)
#define UNSIGNED_FLAGS_2(flag1, flag2)								UNSIGNED_FLAGS_1(flag1) | UNSIGNED_FLAGS_1(flag2)
#define UNSIGNED_FLAGS_3(flag1, flag2, flag3)						UNSIGNED_FLAGS_1(flag1) | UNSIGNED_FLAGS_2(flag2, flag3)
#define UNSIGNED_FLAGS_4(flag1, flag2, flag3, flag4)				UNSIGNED_FLAGS_1(flag1) | UNSIGNED_FLAGS_3(flag2, flag3, flag4)
#define UNSIGNED_FLAGS_5(flag1, flag2, flag3, flag4, flag5)			UNSIGNED_FLAGS_1(flag1) | UNSIGNED_FLAGS_4(flag2, flag3, flag4, flag5)
#define UNSIGNED_FLAGS_6(flag1, flag2, flag3, flag4, flag5, flag6)	UNSIGNED_FLAGS_1(flag1) | UNSIGNED_FLAGS_5(flag2, flag3, flag4, flag5, flag6)
#define UNSIGNED_FLAGS(...) PP_VARG_SELECT_OVERLOAD(UNSIGNED_FLAGS_, (__VA_ARGS__))

#include "Core/Modules/ModuleMacros.h"

#endif
