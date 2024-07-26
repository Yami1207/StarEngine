#ifndef __COMMAND_BUFFER_POOL_H__
#define __COMMAND_BUFFER_POOL_H__

#include <stack>

#include "Thread/Mutex.h"
#include "Utility/Singleton.h"

namespace StarEngine
{
	namespace Rendering
	{
		class CommandBuffer;

		class CommandBufferPool
		{
			SINGLETON_DECL(CommandBufferPool);

			using FreeBuffers = std::stack<CommandBuffer*>;
		public:
			CommandBuffer* Get();

			void Release(CommandBuffer* pCommandBuffer);
		private:
			Mutex		m_Mutex;

			FreeBuffers	m_FreeBuffers;
		};
	}
}

#endif // !__COMMAND_BUFFER_POOL_H__
