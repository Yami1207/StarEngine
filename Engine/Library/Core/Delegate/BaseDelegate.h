#ifndef __BASE_DELEGATE_H__
#define __BASE_DELEGATE_H__

#include <typeinfo>

namespace StarEngine
{
	template<typename ReturnType, typename... ParamType>
	class IBaseDelegate
	{
	public:
		virtual ~IBaseDelegate() {}

		/// <summary>
		/// 判断类型是否一致
		/// </summary>
		/// <param name="type">类型信息</param>
		/// <returns></returns>
		virtual sBoolean IsType(const std::type_info& type) = 0;

		/// <summary>
		/// 调用委托对象
		/// </summary>
		/// <param name="...params">参数</param>
		/// <returns></returns>
		virtual ReturnType Invoke(ParamType... params) = 0;

		/// <summary>
		/// 是否指向同一个委托对象
		/// </summary>
		/// <param name="pDelegate">委托对象</param>
		/// <returns></returns>
		virtual sBoolean Compare(IBaseDelegate<ReturnType, ParamType...>* pDelegate) const = 0;
	};

	template<typename ReturnType, typename... ParamType>
	class StaticDelegate : public IBaseDelegate<ReturnType, ParamType...>
	{
		typedef ReturnType(*Func)(ParamType...);
	public:
		StaticDelegate(Func func) : m_Func(func)
		{
		}

		virtual sBoolean IsType(const std::type_info& type) sealed
		{
			return typeid(StaticDelegate<ReturnType, ParamType...>) == type;
		}

		virtual ReturnType Invoke(ParamType... params) sealed
		{
			return m_Func(params...);
		}

		virtual sBoolean Compare(IBaseDelegate<ReturnType, ParamType...>* pDelegate) const sealed
		{
			if (pDelegate == sNull || !pDelegate->IsType(typeid(StaticDelegate<ReturnType, ParamType...>)))
			{
				return sFalse;
			}

			StaticDelegate<ReturnType, ParamType...>* pTemp = static_cast<StaticDelegate<ReturnType, ParamType...>*>(pDelegate);
			return pTemp->m_Func == m_Func;
		}
	private:
		Func	m_Func;
	};

	template<class T, typename ReturnType, typename... ParamType>
	class MethodDelegate : public IBaseDelegate<ReturnType, ParamType...>
	{
		typedef ReturnType(T::*Method)(ParamType...);
	public:
		MethodDelegate(T* pObject, Method method) : m_pObject(pObject), m_Method(method)
		{
		}

		virtual sBoolean IsType(const std::type_info& type) sealed
		{
			return typeid(MethodDelegate<T, ReturnType, ParamType...>) == type;
		}

		virtual ReturnType Invoke(ParamType... params) sealed
		{
			return (m_pObject->*m_Method)(params...);
		}

		virtual sBoolean Compare(IBaseDelegate<ReturnType, ParamType...>* pDelegate) const sealed
		{
			if (pDelegate == sNull || !pDelegate->IsType(typeid(MethodDelegate<T, ReturnType, ParamType...>)))
				return sFalse;

			MethodDelegate<T, ReturnType, ParamType...>* pTemp = static_cast<MethodDelegate<T, ReturnType, ParamType...>*>(pDelegate);
			return pTemp->m_pObject == m_pObject && pTemp->m_Method == m_Method;
		}
	private:
		T*		m_pObject;
		Method	m_Method;
	};

	/// <summary>
	/// 创建委托对象
	/// </summary>
	/// <typeparam name="ReturnType">返回类型</typeparam>
	/// <typeparam name="...ParamType">参数类型</typeparam>
	/// <param name="pFunc">函数指针</param>
	/// <returns></returns>
	template<typename ReturnType, typename... ParamType>
	StaticDelegate<ReturnType(*)(ParamType...)>* NewDelegate(ReturnType(*pFunc)(ParamType...));

	/// <summary>
	/// 创建委托对象
	/// </summary>
	/// <typeparam name="T">类</typeparam>
	/// <typeparam name="F">类函数</typeparam>
	/// <param name="_object">类对象</param>
	/// <param name="func">类函数指针</param>
	/// <returns></returns>
	template<typename T, typename F>
	MethodDelegate<T, F>* NewDelegate(T* _object, F func);

	/// <summary>
	/// 创建委托对象
	/// </summary>
	/// <typeparam name="T">类型</typeparam>
	/// <param name="func">lambda函数</param>
	/// <returns></returns>
	template<typename T>
	MethodDelegate<T, decltype(&T::operator())>* NewDelegate(T& func);
}

#include "BaseDelegate.inl"

#endif
