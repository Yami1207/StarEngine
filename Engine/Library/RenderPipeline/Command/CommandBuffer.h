#ifndef __COMMAND_BUFFER_H__
#define __COMMAND_BUFFER_H__

#include "Utility/NonCopyable.h"
#include "CommandType.h"

namespace StarEngine
{
	namespace Rendering
	{
		class CommandBuffer : public NonCopyable
		{
		public:
			CommandBuffer();
			~CommandBuffer();
		public:
			/// <summary>
			/// 复制指令
			/// </summary>
			/// <param name="other">指令对象</param>
			void Copy(const CommandBuffer& other);

			/// <summary>
			/// 清空指令
			/// </summary>
			void Clear();

			/// <summary>
			/// 执行指令
			/// </summary>
			/// <returns></returns>
			void Execute();
		public:
			/// <summary>
			/// 设置全局向量
			/// </summary>
			/// <param name="name">名称</param>
			/// <param name="vec">向量</param>
			void SetGlobalVector(const std::string& name, const Vector4& vec);

			/// <summary>
			/// 设置全局向量
			/// </summary>
			/// <param name="name">id</param>
			/// <param name="vec">向量</param>
			void SetGlobalVector(uint32 id, const Vector4& vec);

			/// <summary>
			/// 设置全局颜色
			/// </summary>
			/// <param name="name">名称</param>
			/// <param name="vec">颜色值</param>
			void SetGlobalColor(const std::string& name, const Color& color);

			/// <summary>
			/// 设置全局向量
			/// </summary>
			/// <param name="name">id</param>
			/// <param name="vec">颜色值</param>
			void SetGlobalColor(uint32 id, const Color& color);

			/// <summary>
			/// 设置全局矩阵
			/// </summary>
			/// <param name="name">名称</param>
			/// <param name="mat">矩阵</param>
			void SetGlobalMatrix(const std::string& name, const Matrix44& mat);

			/// <summary>
			/// 设置全局矩阵
			/// </summary>
			/// <param name="id">id</param>
			/// <param name="mat">矩阵</param>
			void SetGlobalMatrix(uint32 id, const Matrix44& mat);
		private:
			void SetSize(uint32 size);

			void IncreaseCommand();
		private:
			uint32	m_CommandCount;

			uint8*	m_pData;
			uint32	m_DataSize, m_DataMaxSize;
		};
	}
}

#include "CommandBuffer.inl"

#endif // !__COMMAND_BUFFER_H__
