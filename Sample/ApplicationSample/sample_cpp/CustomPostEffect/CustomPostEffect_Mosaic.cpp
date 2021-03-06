﻿#include <Altseed.h>

// 一部の領域にモザイクをかけるポストエフェクトのサンプル。

/**
	@brief	DirectX向けシェーダー(HLSLで記述)
*/
static const char* shader2d_dx_ps = R"(
Texture2D g_texture;
SamplerState g_sampler;

float2 g_windowSize;
float4 g_area;

struct PS_Input
{
	float4 SV_Position	: SV_POSITION;
	float4 Position		: POSITION;
	float2 UV			: UV;
	float4 Color		: COLOR;
};

float2 GetPixelPosition(float2 uv)
{
	return g_windowSize * uv;
}

float4 main( const PS_Input Input ) : SV_Target
{
	float2 pixelPos = GetPixelPosition(Input.UV);

	if(
		g_area.x < pixelPos.x &&
		g_area.x + g_area.z > pixelPos.x &&
		g_area.y < pixelPos.y &&
		g_area.y + g_area.w > pixelPos.y)
	{
		float2 uv = Input.UV;
		uv.x = floor(uv.x * g_windowSize.x / 5.0) * 5.0 / g_windowSize.x;
		uv.y = floor(uv.y * g_windowSize.y / 5.0) * 5.0 / g_windowSize.y;
		return g_texture.Sample(g_sampler, uv);
	}
	else
	{
		return g_texture.Sample(g_sampler, Input.UV);
	}
}

)";

/**
	@brief	OpenGL向けシェーダー(GLSLで記述)
*/
static const char* shader2d_gl_ps = R"(
uniform sampler2D g_texture;

uniform vec2 g_windowSize;
uniform vec4 g_area;

in vec4 inPosition;
in vec2 inUV;
in vec4 inColor;

out vec4 outOutput;

vec2 GetPixelPosition(vec2 uv)
{
	uv.y = 1.0 - uv.y;
	return g_windowSize * uv;
}

void main()
{
	vec2 pixelPos = GetPixelPosition(inUV);

	if(
		g_area.x < pixelPos.x &&
		g_area.x + g_area.z > pixelPos.x &&
		g_area.y < pixelPos.y &&
		g_area.y + g_area.w > pixelPos.y)
	{
		vec2 uv = inUV;
		uv.x = floor(uv.x * g_windowSize.x / 5.0) * 5.0 / g_windowSize.x;
		uv.y = floor(uv.y * g_windowSize.y / 5.0) * 5.0 / g_windowSize.y;
		outOutput = texture(g_texture, uv);
	}
	else
	{
		outOutput = texture(g_texture, inUV);
	}
}

)";

/**
	@brief	一部の領域にモザイクをかけるポストエフェクト
*/
class MosaicPostEffect : public asd::PostEffect
{
public:
	std::shared_ptr<asd::Shader2D>		shader;
	std::shared_ptr<asd::Material2D>	material2d;

public:
	MosaicPostEffect()
	{
		// シェーダーをHLSL/GLSLから生成する。
		if (asd::Engine::GetGraphics()->GetGraphicsDeviceType() == asd::GraphicsDeviceType::DirectX11)
		{
			shader = asd::Engine::GetGraphics()->CreateShader2D(
				asd::ToAString(shader2d_dx_ps).c_str()
				);
		}
		else if (asd::Engine::GetGraphics()->GetGraphicsDeviceType() == asd::GraphicsDeviceType::OpenGL)
		{
			shader = asd::Engine::GetGraphics()->CreateShader2D(
				asd::ToAString(shader2d_gl_ps).c_str()
				);
		}

		material2d = asd::Engine::GetGraphics()->CreateMaterial2D(shader);
	}

protected:
	void OnDraw(std::shared_ptr<asd::RenderTexture2D> dst, std::shared_ptr<asd::RenderTexture2D> src) override
	{
		// マテリアルを経由してシェーダー内のg_texture変数に画面の画像(src)を入力する。
		material2d->SetTexture2D(asd::ToAString("g_texture").c_str(), src);

		// マテリアルを経由してシェーダー内のg_area変数にポストエフェクトを適用する範囲を入力する。
		material2d->SetVector2DF(asd::ToAString("g_windowSize").c_str(), asd::Vector2DF(asd::Engine::GetWindowSize().X, asd::Engine::GetWindowSize().Y));

		// マテリアルを経由してシェーダー内のg_area変数にポストエフェクトを適用する範囲を入力する。
		material2d->SetVector4DF(asd::ToAString("g_area").c_str(), asd::Vector4DF(50, 50, 200, 200));

		// 出力画像(dst)に指定したマテリアルで描画する。
		DrawOnTexture2DWithMaterial(dst, material2d);
	}
};

void CustomPostEffect_Mosaic()
{
	// Altseedを初期化する
	asd::Engine::Initialize(asd::ToAString("CustomPostEffect_Mosaic").c_str(), 640, 480, asd::EngineOption());

	// シーン、レイヤー、画像を表示するオブジェクトを生成する。
	auto scene = std::make_shared<asd::Scene>();
	auto layer = std::make_shared<asd::Layer2D>();
	auto obj = std::make_shared<asd::TextureObject2D>();
	obj->SetTexture(asd::Engine::GetGraphics()->CreateTexture2D(asd::ToAString("Data/Texture/Picture1.png").c_str()));

	// シーンを変更し、そのシーンにレイヤーを追加し、そのレイヤーにオブジェクトを追加する。
	asd::Engine::ChangeScene(scene);
	scene->AddLayer(layer);
	layer->AddObject(obj);

	// レイヤーにポストエフェクトを適用する。
	layer->AddPostEffect(std::make_shared<MosaicPostEffect>());

	while (asd::Engine::DoEvents())
	{
		asd::Engine::Update();
	}

	asd::Engine::Terminate();
}