#ifndef __DELEGATE_H__
#define __DELEGATE_H__

#include "MulticastDelegate.h"

// 声明只有返回值的委托对象
#define DECLARE_DELEGATE_ONLY_RETURN(name, returnType)							\
	typedef IBaseDelegate<returnType> name;

#define DECLARE_DELEGATE_FUNCTION(name, ...)									\
	typedef IBaseDelegate<__VA_ARGS__> name;

#define DECLARE_DELEGATE(name)													\
	DECLARE_DELEGATE_FUNCTION(name, void)

#define DECLARE_DELEGATE_RETURN_ONEPARAM(name, returnType, paramType)			\
	DECLARE_DELEGATE_FUNCTION(name, returnType, paramType)

#define DECLARE_MULTICAST_DELEGATE_FUNCTION(name, ...)							\
	typedef MulticastDelegate<__VA_ARGS__> name;

#define DECLARE_MULTICAST_DELEGATE(name)										\
	DECLARE_MULTICAST_DELEGATE_FUNCTION(name, void)

#define DECLARE_MULTICAST_DELEGATE_RETURN_ONEPARAM(name, returnType, paramType)	\
	DECLARE_MULTICAST_DELEGATE_FUNCTION(name, returnType, paramType)

namespace StarEngine
{
	DECLARE_DELEGATE(SimpleDelegate)
	DECLARE_MULTICAST_DELEGATE(SimpleMulticastDelegate)
}

#endif
