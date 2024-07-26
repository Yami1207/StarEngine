#pragma once

namespace StarEngine
{
	//////////////////////////////////////////////////////////////////////////
	template<typename ReturnType, typename... ParamType>
	class StaticDelegate<ReturnType(*)(ParamType...)> : public IBaseDelegate<ReturnType, ParamType...>
	{
		typedef ReturnType(*Func)(ParamType...);
	public:
		StaticDelegate(Func func) : m_Func(func)
		{
		}

		virtual ~StaticDelegate()
		{
		}

		virtual sBoolean IsType(const std::type_info& type) sealed
		{
			return typeid(StaticDelegate<ReturnType(*)(ParamType...)>) == type;
		}

		virtual ReturnType Invoke(ParamType... params) sealed
		{
			return m_Func(params...);
		}

		virtual sBoolean Compare(IBaseDelegate<ReturnType, ParamType...>* pDelegate) const sealed
		{
			if (pDelegate == sNull || !pDelegate->IsType(typeid(StaticDelegate<ReturnType(*)(ParamType...)>)))
			{
				return sFalse;
			}

			StaticDelegate<ReturnType(*)(ParamType...)>* pTemp = static_cast<StaticDelegate<ReturnType(*)(ParamType...)>*>(pDelegate);
			return pTemp->m_Func == m_Func;
		}
	private:
		Func	m_Func;
	};

	//////////////////////////////////////////////////////////////////////////
	template<class T, typename ReturnType, typename... ParamType>
	class MethodDelegate<T, ReturnType(T::*)(ParamType...)> : public IBaseDelegate<ReturnType, ParamType...>
	{
		typedef ReturnType(T::*Method)(ParamType...);
	public:
		MethodDelegate(T* pObject, Method method) : m_pObject(pObject), m_Method(method)
		{
		}

		virtual sBoolean IsType(const std::type_info& type) sealed
		{
			return typeid(MethodDelegate<T, ReturnType(T::*)(ParamType...)>) == type;
		}

		virtual ReturnType Invoke(ParamType... params) sealed
		{
			return (m_pObject->*m_Method)(params...);
		}

		virtual sBoolean Compare(IBaseDelegate<ReturnType, ParamType...>* pDelegate) const sealed
		{
			if (pDelegate == sNull || !pDelegate->IsType(typeid(MethodDelegate<T, ReturnType(T::*)(ParamType...)>)))
			{
				return sFalse;
			}

			MethodDelegate<T, ReturnType(T::*)(ParamType...)>* pTemp = static_cast<MethodDelegate<T, ReturnType(T::*)(ParamType...)>*>(pDelegate);
			return pTemp->m_pObject == m_pObject && pTemp->m_Method == m_Method;
		}
	private:
		T*		m_pObject;
		Method	m_Method;
	};

	/// <summary>
	/// lambda特化
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="ReturnType"></typeparam>
	/// <typeparam name="...ParamType"></typeparam>
	template<class T, typename ReturnType, typename... ParamType>
	class MethodDelegate<T, ReturnType(T::*)(ParamType...) const> : public IBaseDelegate<ReturnType, ParamType...>
	{
		typedef ReturnType(T::*Method)(ParamType...) const;
	public:
		MethodDelegate(T* pObject, const Method method) : m_pObject(pObject), m_Method(method)
		{
		}

		virtual sBoolean IsType(const std::type_info& type) sealed
		{
			return typeid(MethodDelegate<T, ReturnType(T::*)(ParamType...) const>) == type;
		}

		virtual ReturnType Invoke(ParamType... params) sealed
		{
			return (m_pObject->*m_Method)(params...);
		}

		virtual sBoolean Compare(IBaseDelegate<ReturnType, ParamType...>* pDelegate) const sealed
		{
			if (pDelegate == sNull || !pDelegate->IsType(typeid(MethodDelegate<T, ReturnType(T::*)(ParamType...) const>)))
			{
				return sFalse;
			}

			MethodDelegate<T, ReturnType(T::*)(ParamType...) const>* pTemp = static_cast<MethodDelegate<T, ReturnType(T::*)(ParamType...) const>*>(pDelegate);
			return pTemp->m_pObject == m_pObject && pTemp->m_Method == m_Method;
		}
	private:
		T*		m_pObject;
		Method	m_Method;
	};

	//////////////////////////////////////////////////////////////////////////
	template<typename ReturnType, typename... ParamType>
	INLINE StaticDelegate<ReturnType(*)(ParamType...)>* NewDelegate(ReturnType(*pFunc)(ParamType...))
	{
		return new StaticDelegate<ReturnType(*)(ParamType...)>(pFunc);
	}

	template<typename T, typename F>
	INLINE MethodDelegate<T, F>* NewDelegate(T* pObject, F func)
	{
		return new MethodDelegate<T, F>(pObject, func);
	}

	template<typename T>
	INLINE MethodDelegate<T, decltype(&T::operator())>* NewDelegate(T& func)
	{
		return new MethodDelegate<T, decltype(&T::operator())>(&func, &T::operator());
	}
}
