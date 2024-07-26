#include "EngineLibrary.h"
#include "CommandBuffer.h"

#include "RenderCore/RenderContext.h"

#include "Shader/ShaderRegistry.h"
#include "Shader/ShaderPropertySheet.h"

#define COMMAND_DATA_BUFFER_MAX_SIZE	1024

namespace StarEngine
{
	namespace Rendering
	{
		namespace
		{
			template<typename T>
			void ReadBufferData(uint8* pData, T* value, uint32& pos)
			{
				uint32 bytes = sizeof(T);
				MemoryCopy(value, &pData[pos], bytes);
				pos += bytes;
			}

			template<typename T>
			void WriteBufferData(uint8* pData, T* value, uint32& pos)
			{
				uint32 bytes = sizeof(T);
				MemoryCopy(&pData[pos], value, bytes);
				pos += bytes;
			}
		}

		CommandBuffer::CommandBuffer() : m_CommandCount(0), m_pData(sNull), m_DataSize(0), m_DataMaxSize(0)
		{
		}

		CommandBuffer::~CommandBuffer()
		{
			SAFE_FREE(m_pData);
		}

		void CommandBuffer::Copy(const CommandBuffer& other)
		{
			if (m_DataMaxSize < other.m_DataMaxSize)
			{
				m_DataMaxSize = other.m_DataMaxSize;
				if (m_pData == sNull)
					m_pData = (uint8*)MemoryAlloc(m_DataMaxSize);
				else
					m_pData = (uint8*)MemoryRealloc(m_pData, m_DataMaxSize);
			}

			m_CommandCount = other.m_CommandCount;
			m_DataSize = other.m_DataSize;
			
			// 复制缓存数据
			MemoryCopy(m_pData, other.m_pData, m_DataSize);
		}

		void CommandBuffer::Clear()
		{
			m_CommandCount = 0;
			m_DataSize = 0;
		}

		void CommandBuffer::Execute()
		{
			if (m_CommandCount == 0)
				return;

			RenderContext* pRenderContext = RenderContext::Instance();
			ShaderRegistry* pShaderRegistry = ShaderRegistry::Instance();
			uint32 pos = 0;
			
			// 执行指令
			for (uint32 i = 0; i < m_CommandCount; ++i)
			{
				uint8 cmd = (uint8)CommandType::Unknown;
				ReadBufferData(m_pData, &cmd, pos);

				switch (cmd)
				{
				case (uint8)CommandType::SetGlobalVector:
					{
						uint32 id = ShaderPropertyInvalidIndex;
						ReadBufferData(m_pData, &id, pos);

						uint32 cb = ShaderPropertyInvalidIndex;
						ReadBufferData(m_pData, &cb, pos);

						Vector4 vec;
						ReadBufferData(m_pData, &vec, pos);

						ShaderPropertySheet* pSheet = pRenderContext->GetShaderPropertySheet(cb);
						if (pSheet != sNull)
							pSheet->SetVector(id, vec);
					}
					break;
				case (uint8)CommandType::SetGlobalMatrix:
					{
						uint32 id = ShaderPropertyInvalidIndex;
						ReadBufferData(m_pData, &id, pos);

						uint32 cb = ShaderPropertyInvalidIndex;
						ReadBufferData(m_pData, &cb, pos);

						Matrix44 mat;
						ReadBufferData(m_pData, &mat, pos);

						ShaderPropertySheet* pSheet = pRenderContext->GetShaderPropertySheet(cb);
						if (pSheet != sNull)
							pSheet->SetMatrix(id, mat);
					}
					break;
				}
			}
		}

		void CommandBuffer::SetGlobalVector(const std::string& name, const Vector4& vec)
		{
			SetGlobalVector(ShaderRegistry::PropertyToID(name), vec);
		}

		void CommandBuffer::SetGlobalVector(uint32 id, const Vector4& vec)
		{
			ShaderProperty* pProp = ShaderRegistry::GetProperty(id);
			if (pProp == sNull || !pProp->IsBuiltin())
				return;

			uint32 cb = pProp->GetConstantBufferIndex();
			uint32 pos = m_DataSize;

			// 设置数据大小
			SetSize(pos + sizeof(uint8) + sizeof(uint32) + sizeof(uint32) + sizeof(Vector4));

			// 指令ID
			uint8 command = (uint8)CommandType::SetGlobalVector;
			WriteBufferData(m_pData, &command, pos);

			// 向量
			WriteBufferData(m_pData, &id, pos);
			WriteBufferData(m_pData, &cb, pos);
			WriteBufferData(m_pData, &vec, pos);

			IncreaseCommand();
		}

		void CommandBuffer::SetGlobalColor(const std::string& name, const Color& color)
		{
			Vector4 vec = Vector4(color.r, color.g, color.b, color.a);
			SetGlobalVector(ShaderRegistry::PropertyToID(name), vec);
		}

		void CommandBuffer::SetGlobalColor(uint32 id, const Color& color)
		{
			Vector4 vec = Vector4(color.r, color.g, color.b, color.a);
			SetGlobalVector(id, vec);
		}

		void CommandBuffer::SetGlobalMatrix(const std::string& name, const Matrix44& mat)
		{
			SetGlobalMatrix(ShaderRegistry::PropertyToID(name), mat);
		}

		void CommandBuffer::SetGlobalMatrix(uint32 id, const Matrix44& mat)
		{
			ShaderProperty* pProp = ShaderRegistry::GetProperty(id);
			if (pProp == sNull || !pProp->IsBuiltin())
				return;

			uint32 cb = pProp->GetConstantBufferIndex();
			uint32 pos = m_DataSize;

			// 设置数据大小
			SetSize(pos + sizeof(uint8) + sizeof(uint32) + sizeof(uint32) + sizeof(Matrix44));

			// 指令ID
			uint8 command = (uint8)CommandType::SetGlobalMatrix;
			WriteBufferData(m_pData, &command, pos);

			// 矩阵
			WriteBufferData(m_pData, &id, pos);
			WriteBufferData(m_pData, &cb, pos);
			WriteBufferData(m_pData, &mat, pos);

			IncreaseCommand();
		}

		void CommandBuffer::SetSize(uint32 size)
		{
			m_DataSize = size;
			if (m_DataSize > m_DataMaxSize)
			{
				// 缓存数据大小
				if (m_DataMaxSize == 0)
					m_DataMaxSize = COMMAND_DATA_BUFFER_MAX_SIZE;
				else
					m_DataMaxSize += m_DataMaxSize;

				// 分配缓存数据
				if (m_pData == sNull)
					m_pData = (uint8*)MemoryAlloc(m_DataMaxSize);
				else
					m_pData = (uint8*)MemoryRealloc(m_pData, m_DataMaxSize);
			}
		}
	}
}
