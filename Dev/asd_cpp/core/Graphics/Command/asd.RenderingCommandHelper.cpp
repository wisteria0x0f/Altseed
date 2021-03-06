﻿
#include "asd.RenderingCommandHelper.h"
#include "asd.RenderingCommandFactory.h"
#include "asd.RenderingCommand.h"
#include "../Resource/asd.NativeShader_Imp.h"

namespace asd
{
	int32_t RenderingCommandHelper::GetConstantBufferID(NativeShader_Imp* shader, const char* name)
	{
		return shader->GetConstantBufferID(name);
	}

	int32_t RenderingCommandHelper::GetTextureID(NativeShader_Imp* shader, const char* name)
	{
		return shader->GetTextureID(name);
	}

	Vector4DF* RenderingCommandHelper::MallocVector4DFArrayBuffer(int32_t count)
	{
		return factory->CreateCommands<Vector4DF>(count);
	}

	Matrix44* RenderingCommandHelper::MallocMatrix44ArrayBuffer(int32_t count)
	{
		return factory->CreateCommands<Matrix44>(count);
	}

	RenderingCommandHelper::RenderingCommandHelper(std::vector<RenderingCommand*>& commands, RenderingCommandFactory* factory)
		: commands(commands)
		, factory(factory)
	{
		
	}

	void RenderingCommandHelper::Clear(bool isColorTarget, bool isDepthTarget, const Color& color)
	{
		factory->Clear(commands, isColorTarget, isDepthTarget, color);
	}

	void RenderingCommandHelper::SetRenderTarget(RenderTexture2D* renderTexture0, RenderTexture2D* renderTexture1, RenderTexture2D* renderTexture2, RenderTexture2D* renderTexture3, DepthBuffer_Imp* depth)
	{
		factory->SetRenderTarget(commands, renderTexture0, renderTexture1, renderTexture2, renderTexture3, depth);
	}

	void RenderingCommandHelper::SetRenderTarget(RenderTexture2D* renderTexture0, DepthBuffer_Imp* depth)
	{
		factory->SetRenderTarget(commands, renderTexture0, depth);
	}

	void RenderingCommandHelper::DrawWithPtr(int32_t polyCount, VertexBuffer_Imp* vb, IndexBuffer_Imp* ib, NativeShader_Imp* shader, RenderState rs, ShaderConstantValue* values, int32_t count)
	{
		auto command = factory->CreateCommand<RenderingCommand_Draw>(polyCount, vb, ib, shader, rs);
		command->SetConstantValues(factory, values, count);
		commands.push_back(command);
	}

	void RenderingCommandHelper::DrawWithPtr(int32_t polyOffset, int32_t polyCount, VertexBuffer_Imp* vb, IndexBuffer_Imp* ib, NativeShader_Imp* shader, RenderState rs, ShaderConstantValue* values, int32_t count)
	{
		auto command = factory->CreateCommand<RenderingCommand_Draw>(polyOffset, polyCount, vb, ib, shader, rs);
		command->SetConstantValues(factory, values, count);
		commands.push_back(command);
	}

	void RenderingCommandHelper::DrawInstancedWithPtr(int32_t polyCount, int32_t instanceCount, VertexBuffer_Imp* vb, IndexBuffer_Imp* ib, NativeShader_Imp* shader, RenderState rs, ShaderConstantValue* values, int32_t count)
	{
		auto command = factory->CreateCommand<RenderingCommand_DrawInstanced>(polyCount, instanceCount, vb, ib, shader, rs);
		command->SetConstantValues(factory, values, count);
		commands.push_back(command);
	}

	void RenderingCommandHelper::Draw(int32_t polyCount, VertexBuffer_Imp* vb, IndexBuffer_Imp* ib, NativeShader_Imp* shader, RenderState rs)
	{
		auto command = factory->CreateCommand<RenderingCommand_Draw>(polyCount, vb, ib, shader, rs);
		commands.push_back(command);
	}

	void RenderingCommandHelper::DrawEffect(Matrix44 projMat, Matrix44 cameraMat)
	{
		auto command = factory->CreateCommand<RenderingCommand_DrawEffect>(projMat, cameraMat);
		commands.push_back(command);
	}

	void RenderingCommandHelper::DrawSprite(Matrix44 projMat, Matrix44 cameraMat)
	{
		auto command = factory->CreateCommand<RenderingCommand_DrawSprite>(projMat, cameraMat);
		commands.push_back(command);
	}
}