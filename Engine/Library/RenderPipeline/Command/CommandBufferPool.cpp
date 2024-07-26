#include "EngineLibrary.h"
#include "CommandBufferPool.h"

#include "CommandBuffer.h"

namespace StarEngine
{
	namespace Rendering
	{
		CommandBufferPool::CommandBufferPool()
		{
		}

		CommandBufferPool::~CommandBufferPool()
		{
			while (!m_FreeBuffers.empty())
			{
				CommandBuffer* pCommandBuffer = m_FreeBuffers.top();
				m_FreeBuffers.pop();
				SAFE_DELETE(pCommandBuffer);
			}
		}

		CommandBuffer* CommandBufferPool::Get()
		{
			MutexHolder holder(m_Mutex);

			if (m_FreeBuffers.empty())
				return new CommandBuffer();
			
			CommandBuffer* pCommandBuffer = m_FreeBuffers.top();
			m_FreeBuffers.pop();
			return pCommandBuffer;
		}

		void CommandBufferPool::Release(CommandBuffer* pCommandBuffer)
		{
			if (pCommandBuffer == sNull)
				return;

			MutexHolder holder(m_Mutex);
			pCommandBuffer->Clear();
			m_FreeBuffers.push(pCommandBuffer);
		}
	}
}
