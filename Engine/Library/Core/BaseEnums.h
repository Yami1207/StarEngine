#ifndef __BASE_ENUMS_H__
#define __BASE_ENUMS_H__

#include "InputEnums.h"

namespace StarEngine
{
	// 音频参数
	enum class SoundFlags
	{
		None = 0,

		// 循环播放
		Looping = (1 << 1),

		// 流式播放
		Streaming = (1 << 2),

		Music = (1 << 3),

		// 语音音量
		Voice = 256,

		// 音乐音量
		MusicVoice = 512,
	};

	// 比较功能
	enum class CompareFunc
	{
		// 小于
		Less = 0,

		// 小于等于
		LessEqual,

		// 大于
		Greater,

		// 大于等于
		GreaterEqual,

		// 相等
		Equal,

		// 不等
		NotEqual,

		// 从未
		Never,

		// 总是
		Always,
	};

	// 内存对齐机制
	enum MemoryAlignment
	{
		DEFAULT_ALIGNMENT = 0,
		MIN_ALIGNMENT = 8,
	};
}

#endif
