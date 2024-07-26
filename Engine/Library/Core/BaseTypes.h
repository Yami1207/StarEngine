#ifndef __BASE_TYPES_H__
#define __BASE_TYPES_H__

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#endif

#include <string>
#include <stdlib.h>

template<typename Bit32, typename Bit64, int PointerSize>
struct SelectIntPointerType
{
};

template<typename Bit32, typename Bit64>
struct SelectIntPointerType<Bit32, Bit64, 8>
{
	typedef Bit64 IntPointer;
};

template<typename Bit32, typename Bit64>
struct SelectIntPointerType<Bit32, Bit64, 4>
{
	typedef Bit32 IntPointer;
};

typedef char		int8;
typedef short		int16;
typedef int			int32;
typedef long long	int64;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

typedef float	F32;
typedef double	F64;

typedef uint8	sBoolean;
typedef uint32	Outcode;

typedef char	ANSICHAR;	// An ANSI character.
typedef uint16	UNICHAR;	// A unicode character.
typedef uint8	ANSICHARU;	// An ANSI character.
typedef uint16	UNICHARU;	// A unicode character.

// 与指针长度相等的整数类型
typedef SelectIntPointerType<int32, int64, sizeof(void*)>::IntPointer intptr;

// 与指针长度相等的无符号整数类型
typedef SelectIntPointerType<uint32, uint64, sizeof(void*)>::IntPointer uintptr;

#ifndef _TCHAR_DEFINED

#ifdef _UNICODE

typedef UNICHAR  TCHAR;
typedef UNICHARU TCHARU;

#else

typedef ANSICHAR  TCHAR;
typedef ANSICHARU TCHARU;

#endif

#endif

namespace StarEngine
{
	namespace Network
	{
		class Address
		{
		public:
			Address() : nAddress(0), nPort(0), nSalt(0) {}
			Address(uint32 address, uint16 port) : nAddress(address), nPort(port), nSalt(0) {}
		public:
			uint32	nAddress;
			uint16	nPort;
			uint16	nSalt;
		};

		inline bool operator ==(const Address& a, const Address& b)
		{
			return a.nAddress == b.nAddress && a.nPort == b.nPort;
		}

		inline bool operator !=(const Address& a, const Address& b)
		{
			return a.nAddress != b.nAddress || a.nPort != b.nPort;
		}

		inline bool	operator <(const Address& a, const Address& b)
		{
			return (a.nAddress < b.nAddress) || (a.nAddress == b.nAddress && (a.nPort < b.nPort));
		}
	}

	class SpaceEntryID : public Network::Address
	{

	};

	inline bool operator ==(const SpaceEntryID& a, const SpaceEntryID& b)
	{
		return a.nAddress == b.nAddress && a.nPort == b.nPort;
	}

	inline bool operator !=(const SpaceEntryID& a, const SpaceEntryID& b)
	{
		return a.nAddress != b.nAddress || a.nPort != b.nPort;
	}

	inline bool	operator <(const SpaceEntryID& a, const SpaceEntryID& b)
	{
		return (a.nAddress < b.nAddress) || (a.nAddress == b.nAddress && (a.nPort < b.nPort));
	}

	/**
	 * @brief StringLength	字符串长度
	 * @param str	字符串
	 * @return
	 */
	inline int32 StringLength(const char* str)
	{
		return static_cast<int32>(strlen(str));
	}

	/**
	 * @brief StringLength	字符串长度
	 * @param str	字符串
	 * @return
	 */
	inline int32 StringLength(const wchar_t* str)
	{
		return static_cast<int32>(wcslen(str));
	}

	//添加scr到dst后面
	inline char* StringCatenate(char* dst, const char* scr)
	{
		return strcat(dst, scr);
	}

	inline wchar_t* StringCatenate(wchar_t* dts, const wchar_t* scr)
	{
		return wcscat(dts, scr);
	}

	//字符串复制
	inline char* StringCopy(char* dst, const char* scr)
	{
		return strcpy(dst, scr);
	}

	inline wchar_t* StringCopy(wchar_t* dts, const wchar_t* scr)
	{
		return wcscpy(dts, scr);
	}

	//将字符串scr中最多n个字符复制到字符数组dst中
	inline char* StringCopy(char* dst, const char* scr, uint32 len)
	{
		return strncpy(dst, scr, len);
	}

	inline wchar_t* StringCopy(wchar_t* dts, const wchar_t* scr, uint32 len)
	{
		return wcsncpy(dts, scr, len);
	}

	//比较字符串
	inline int32 StringCompare(const char* str1, const char* str2)
	{
		return strcmp(str1, str2);
	}

	inline int32 StringCompare(const char* str1, const char* str2, uint32 length)
	{
		return strncmp(str1, str2, length);
	}

	inline int32 StringCompare(const wchar_t* str1, const wchar_t* str2)
	{
		return wcscmp(str1, str2);
	}

	inline int32 StringCompare(const wchar_t* str1, const wchar_t* str2, uint32 length)
	{
		return wcsncmp(str1, str2, length);
	}

	//比较字符串(无视大小写)
	inline int32 StringCompareNoCase(const char* str1, const char* str2)
	{
		return _strcmpi(str1, str2);
	}

	inline int32 StringCompareNoCase(const char* str1, const char* str2, uint32 length)
	{
		return _strnicmp(str1, str2, length);
	}

	inline int32 StringCompareNoCase(const wchar_t* str1, const wchar_t* str2)
	{
		return _wcsicmp(str1, str2);
	}

	inline int32 StringCompareNoCase(const wchar_t* str1, const wchar_t* str2, uint32 length)
	{
		return _wcsnicmp(str1, str2, length);
	}

	//搜索一个字符串在另一个字符串中第一次出现
	inline char* StringSearch(const char* pString, const char* pSub)
	{
		return (char*)strstr(pString, pSub);
	}

	inline wchar_t* StringSearch(const wchar_t* pString, const wchar_t* pSub)
	{
		return (wchar_t*)wcsstr(pString, pSub);
	}

	//查找一个字符串在另一个字符串中末次出现的位置,并返回从字符串中的这个位置起,一直到字符串结束的所有字符
	inline char* StringReverseSearch(char* str, int32 c)
	{
		return strrchr(str, c);
	}

	inline wchar_t* StringReverseSearch(wchar_t* str, int32 c)
	{
		return wcsrchr(str, c);
	}

	inline const char* StringReverseSearch(const char* str, int32 c)
	{
		return strrchr(str, c);
	}

	inline const wchar_t* StringReverseSearch(const wchar_t* str, int32 c)
	{
		return wcsrchr(str, c);
	}

	/**
	 * @brief IsDigit	字符是否数字
	 * @param c	字符
	 * @return
	 */
	inline bool IsDigit(char c)
	{
		return c >= '0' && c <= '9';
	}

	/**
	 * @brief IsAlpha	字符是否字母
	 * @param c	字符
	 * @return
	 */
	inline bool IsAlpha(char c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}

	/**
	 * @brief IsAlphaNumeric	字符是否字母或数字
	 * @param c	字符
	 * @return
	 */
	inline bool IsAlphaNumeric(char c)
	{
		return IsDigit(c) || IsAlpha(c);
	}

	/**
	 * @brief IsSpace	字符是否空格
	 * @param c	字符
	 * @return
	 */
	inline bool IsSpace(char c)
	{
		return c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ';
	}

	/**
	 * @brief IsTabSpace	字符是否Tab或空格
	 * @param c	字符
	 * @return
	 */
	inline bool IsTabSpace(char c)
	{
		return c == '\t' || c == ' ';
	}

	/**
	 * @brief ToUpper	字符转大写
	 * @param c	字符
	 * @return
	 */
	inline char ToUpper(char c)
	{
		return (c >= 'a' && c <= 'z') ? c - 'a' + 'A' : c;
	}

	/**
	 * @brief ToUpper	字符串转大写
	 * @param pText	字符串指针
	 * @return
	 */
	inline char* ToUpper(char* pText)
	{
#ifndef _WIN32
		char* str = pText;
		for (; *pText != '\0'; ++pText)
			*pText = ToUpper(*pText);
		return str;
#else
		return _strupr(pText);
#endif
	}

	/**
	 * @brief ToUpper	字符串转大写
	 * @param text	字符串
	 * @return
	 */
	inline std::string ToUpper(const std::string& text)
	{
		std::string result = text;
		for (uint32 i = 0; i < result.length(); ++i)
		{
			if (result[i] >= 'a' && result[i] <= 'z')
				result[i] = result[i] - 'a' + 'A';
		}
		return result;
	}

	/**
	 * @brief ToLower	字符转小写
	 * @param c	字符
	 * @return
	 */
	inline char ToLower(char c)
	{
		return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
	}

	/**
	 * @brief ToLower	字符串转小写
	 * @param pText	字符串指针
	 * @return
	 */
	inline char* ToLower(char* pText)
	{
#ifndef _WIN32
		char* str = pText;
		for (; *pText != '\0'; ++pText)
			*pText = ToLower(*pText);
		return str;
#else
		return _strlwr(pText);
#endif
	}

	/**
	 * @brief ToLower	字符串转小写
	 * @param text	字符串
	 * @return
	 */
	inline std::string ToLower(const std::string& text)
	{
		std::string result = text;
		for (uint32 i = 0; i < result.length(); ++i)
		{
			if (result[i] >= 'A' && result[i] <= 'Z')
				result[i] = result[i] - 'A' + 'a';
		}
		return result;
	}

	namespace MathLib
	{
		template<class A, class B>
		inline A Min(A a, B b)
		{
			return a < (A)b ? a : (A)b;
		}

		template<class A, class B>
		inline A Max(A a, B b)
		{
			return a > (A)b ? a : (A)b;
		}

		template<typename T>
		inline T Abs(const T a)
		{
			return (a >= (T)0) ? a : -a;
		}

		template<class T>
		inline T Clamp(T value, T min, T max)
		{
			return value < min ? min : (value > max ? max : value);
		}

		template<typename T>
		inline void Swap(T& a, T& b, T& temp)
		{
			temp = a;
			a = b;
			b = temp;
		}

		template<typename T1, typename T2>
		inline T1 Lerp(T1& a, T2& b, F32 t)
		{
			return a + (T1)(t * ((T1)b - a));
		}

		template<typename T1, typename T2>
		inline T1 Lerp(T1& a, T2& b, F64 t)
		{
			return a + (T1)(t * ((T1)b - a));
		}

		/**
		*	向下取整
		*	@param value	取整数值
		*/
		inline int32 FastFloor(F32 value)
		{
			return (int32)(value < 0 ? value - 1 : value);
		}

		/**
		*	获取指定浮点数的小数部分
		*	@param value	浮点数
		*/
		inline F32 Fractional(F32 value)
		{
			return value - (F32)FastFloor(value);
		}

		/**
		*	比较单精度浮点数是否一样
		*	@param a		比较值
		*	@param b		比较值
		*	@param epsilon	误差值
		*/
		inline sBoolean AlmostEqual(const F32 a, const F32 b, const F32 epsilon = 0.0004f)
		{
			return fabsf(a - b) < epsilon;
		}

		/**
		*	比较双精度浮点数是否一样
		*	@param a		比较值
		*	@param b		比较值
		*	@param epsilon	误差值
		*/
		inline sBoolean AlmostEqual(const F64 a, const F64 b, const F64 epsilon = 0.0004)
		{
			return fabs(a - b) < epsilon;
		}

		/**
		 * @brief AlmostZero	比较单精度浮点数是否为零
		 * @param value			浮点值
		 * @param epsilon		误差值
		 * @return
		 */
		inline sBoolean AlmostZero(const F32 value, const F32 epsilon = 0.0004f)
		{
			return AlmostEqual(value, 0.f, epsilon);
		}

		/**
		 * @brief AlmostZero	比较双精度浮点数是否为零
		 * @param value			浮点值
		 * @param epsilon		误差值
		 * @return
		 */
		inline sBoolean AlmostZero(const F64 value, const F64 epsilon = 0.0004)
		{
			return AlmostEqual(value, 0., epsilon);
		}
	}
}

#endif
