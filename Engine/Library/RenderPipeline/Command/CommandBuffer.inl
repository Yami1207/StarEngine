#pragma once

namespace StarEngine
{
	namespace Rendering
	{
		INLINE void CommandBuffer::IncreaseCommand()
		{
			++m_CommandCount;
		}
	}
}
