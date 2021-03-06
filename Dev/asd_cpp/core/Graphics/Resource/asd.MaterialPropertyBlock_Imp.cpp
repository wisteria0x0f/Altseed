﻿
#include "asd.MaterialPropertyBlock_Imp.h"
#include "asd.NativeShader_Imp.h"

namespace asd
{
	MaterialPropertyBlock_Imp::MaterialPropertyBlock_Imp()
	{

	}

	MaterialPropertyBlock_Imp::~MaterialPropertyBlock_Imp()
	{

	}

	float MaterialPropertyBlock_Imp::GetFloat(const achar* name)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Float) return 0.0f;
			return values[name].Data.Float4[0];
		}
		return 0.0f;
	}

	void MaterialPropertyBlock_Imp::SetFloat(const achar* name, float value)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Float) return;
			values[name].Data.Float4[0] = value;
		}
		else
		{
			values[name] = ShaderConstantValue(value);
		}
	}

	Vector2DF MaterialPropertyBlock_Imp::GetVector2DF(const achar* name)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Vector2DF) return Vector2DF(0.0f, 0.0f);
			return Vector2DF(values[name].Data.Float4[0], values[name].Data.Float4[1]);
		}
		return Vector2DF(0.0f, 0.0f);
	}

	void MaterialPropertyBlock_Imp::SetVector2DF(const achar* name, Vector2DF value)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Vector2DF) return;
			values[name].Data.Float4[0] = value.X;
			values[name].Data.Float4[1] = value.Y;
		}
		else
		{
			values[name] = ShaderConstantValue(value);
		}
	}

	Vector3DF MaterialPropertyBlock_Imp::GetVector3DF(const achar* name)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Vector3DF) return Vector3DF(0.0f, 0.0f, 0.0f);
			return Vector3DF(values[name].Data.Float4[0], values[name].Data.Float4[1], values[name].Data.Float4[2]);
		}
		return Vector3DF(0.0f, 0.0f, 0.0f);
	}

	void MaterialPropertyBlock_Imp::SetVector3DF(const achar* name, Vector3DF value)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Vector3DF) return;
			values[name].Data.Float4[0] = value.X;
			values[name].Data.Float4[1] = value.Y;
			values[name].Data.Float4[2] = value.Z;
		}
		else
		{
			values[name] = ShaderConstantValue(value);
		}
	}

	Vector4DF MaterialPropertyBlock_Imp::GetVector4DF(const achar* name)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Vector4DF) return Vector4DF(0.0f, 0.0f, 0.0f, 0.0f);
			return Vector4DF(values[name].Data.Float4[0], values[name].Data.Float4[1], values[name].Data.Float4[2], values[name].Data.Float4[3]);
		}
		return Vector4DF();
	}

	void MaterialPropertyBlock_Imp::SetVector4DF(const achar* name, Vector4DF value)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Vector4DF) return;
			values[name].Data.Float4[0] = value.X;
			values[name].Data.Float4[1] = value.Y;
			values[name].Data.Float4[2] = value.Z;
			values[name].Data.Float4[3] = value.W;
		}
		else
		{
			values[name] = ShaderConstantValue(value);
		}
	}

	Texture2D* MaterialPropertyBlock_Imp::GetTexture2D_(const achar* name)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Texture2D) return nullptr;
			auto ret = values[name].Data.Texture2DPtr.Ptr;
			return ret;
		}
		return nullptr;
	}

	void MaterialPropertyBlock_Imp::SetTexture2D(const achar* name, Texture2D* value)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Texture2D) return;
			SafeSubstitute(values[name].Data.Texture2DPtr.Ptr, value);
		}
		else
		{
			values[name] = ShaderConstantValue(value, TextureFilterType::Nearest, TextureWrapType::Clamp);
		}
	}

	TextureFilterType MaterialPropertyBlock_Imp::GetTextureFilterType(const achar* name)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Texture2D) return TextureFilterType::Linear;
			auto ret = values[name].Data.Texture2DPtr.FilterType;
			return ret;
		}
		return TextureFilterType::Linear;
	}

	void MaterialPropertyBlock_Imp::SetTextureFilterType(const achar* name, TextureFilterType filter)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Texture2D) return;
		}
		else
		{
			Texture2D* texture = nullptr;
			values[name] = ShaderConstantValue(texture, TextureFilterType::Nearest, TextureWrapType::Clamp);
		}

		values[name].Data.Texture2DPtr.FilterType = filter;
	}

	TextureWrapType MaterialPropertyBlock_Imp::GetTextureWrapType(const achar* name)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Texture2D) return TextureWrapType::Clamp;
			auto ret = values[name].Data.Texture2DPtr.WrapType;
			return ret;
		}
		return TextureWrapType::Clamp;
	}

	void MaterialPropertyBlock_Imp::SetTextureWrapType(const achar* name, TextureWrapType wrap)
	{
		if (values.count(name) > 0)
		{
			if (values[name].ValueType != ShaderVariableType::Texture2D) return;
		}
		else
		{
			Texture2D* texture = nullptr;
			values[name] = ShaderConstantValue(texture, TextureFilterType::Nearest, TextureWrapType::Clamp);
		}

		values[name].Data.Texture2DPtr.WrapType = wrap;
	}

	void MaterialPropertyBlock_Imp::AddValuesTo(NativeShader_Imp* shader, std::vector<ShaderConstantValue>& dst)
	{
		for (auto& v : GetValues())
		{
			auto v_ = v.second;
			auto str = ToUtf8String(v.first.c_str());

			if (v.second.ValueType == ShaderVariableType::Texture2D)
			{
				v_.ID = shader->GetTextureID(str.c_str());
			}
			else if (v.second.ValueType == ShaderVariableType::CubemapTexture)
			{
				v_.ID = shader->GetTextureID(str.c_str());
			}
			else
			{
				v_.ID = shader->GetConstantBufferID(str.c_str());
			}

			dst.push_back(v_);
		}
	}
}