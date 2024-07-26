#ifndef __COMMAND_TYPE_H__
#define __COMMAND_TYPE_H__

namespace StarEngine
{
	namespace Rendering
	{
		enum class CommandType
		{
			Unknown = 0,
			SetGlobalVector,
			SetGlobalMatrix,
		};
	}
}

#endif // !__COMMAND_TYPE_H__

