#pragma once

namespace StarEngine
{
	template<typename... ParamType>
	class MulticastDelegate<void, ParamType...>
	{
		using DelegateHandle = IBaseDelegate<void, ParamType...>;
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
		void Clear()
		{
			for (int32 i = 0; i < m_Delegates.Size(); ++i)
			{
				DelegateHandle* pDelegate = m_Delegates.At(i);
				SAFE_DELETE(pDelegate);
			}
			m_Delegates.RemoveAll();
		}

		sBoolean IsEmpty()
		{
			return m_Delegates.IsEmpty();
		}
	public:
		MulticastDelegate<void, ParamType...>& operator +=(DelegateHandle* pDelegate)
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

		MulticastDelegate<void, ParamType...>& operator -=(DelegateHandle* pDelegate)
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
		MulticastDelegate(const MulticastDelegate<void, ParamType...>&) = delete;
		MulticastDelegate<void, ParamType...>& operator =(const MulticastDelegate<void, ParamType...>&) = delete;
	private:
		DelegateList	m_Delegates;
	};
}
