#ifndef __MULTICAST_DELEGATE_H__
#define __MULTICAST_DELEGATE_H__

#include "Core/Containers/GrowableArray.h"

#include "BaseDelegate.h"

namespace StarEngine
{
	template<typename ReturnType, typename... ParamType>
	class MulticastDelegate
	{
		using DelegateHandle = IBaseDelegate<ReturnType, ParamType...>;
		using DelegateList = GrowableArray<DelegateHandle*>;
	public:
		MulticastDelegate()
		{
		}
		
		virtual ~MulticastDelegate()
		{
			this->Clear();
		}
	public:
		/// <summary>
		/// 清空委托列表
		/// </summary>
		void Clear()
		{
			for (int32 i = 0; i < m_Delegates.Size(); ++i)
			{
				DelegateHandle* pDelegate = m_Delegates.At(i);
				SAFE_DELETE(pDelegate);
			}
			m_Delegates.RemoveAll();
		}

		/// <summary>
		/// 委托列表是否为空
		/// </summary>
		/// <returns></returns>
		sBoolean IsEmpty()
		{
			return m_Delegates.IsEmpty();
		}
	public:
		MulticastDelegate<ReturnType, ParamType...>& operator +=(DelegateHandle* pDelegate)
		{
			for (int32 i = 0; i < m_Delegates.Size(); ++i)
			{
				DelegateHandle* pTemp = m_Delegates.At(i);
				if (pTemp->Compare(pDelegate))
				{
					delete pDelegate;
					return *this;
				}
			}

			m_Delegates.PushBack(pDelegate);
			return *this;
		}

		MulticastDelegate<ReturnType, ParamType...>& operator -=(DelegateHandle* pDelegate)
		{
			for (int32 i = 0; i < m_Delegates.Size(); ++i)
			{
				DelegateHandle* pTemp = m_Delegates.At(i);
				if (pTemp->Compare(pDelegate))
				{
					m_Delegates.Remove(i);
					delete pTemp;
					break;
				}
			}

			delete pDelegate;
			return *this;
		}

		void operator ()(ParamType... params)
		{
			for (int32 i = 0; i < m_Delegates.Size(); ++i)
			{
				DelegateHandle* pDelegate = m_Delegates.At(i);
				pDelegate->Invoke(params...);
			}
		}
	public:
		MulticastDelegate(const MulticastDelegate<ReturnType, ParamType...>&) = delete;
		MulticastDelegate<ReturnType, ParamType...>& operator =(const MulticastDelegate<ReturnType, ParamType...>&) = delete;
	private:
		DelegateList	m_Delegates;
	};
}

#include "MulticastDelegate.inl"

#endif
