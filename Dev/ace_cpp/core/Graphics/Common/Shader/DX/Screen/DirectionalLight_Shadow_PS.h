static const char* directonalLight_Shadow_ps_dx = R"(

Texture2D		g_gbuffer0Texture		: register( t0 );
SamplerState	g_gbuffer0Sampler		: register( s0 );

Texture2D		g_gbuffer1Texture		: register( t1 );
SamplerState	g_gbuffer1Sampler		: register( s1 );

Texture2D		g_gbuffer2Texture		: register( t2 );
SamplerState	g_gbuffer2Sampler		: register( s2 );

Texture2D		g_gbuffer3Texture		: register( t3 );
SamplerState	g_gbuffer3Sampler		: register( s3 );

Texture2D		g_shadowmapTexture		: register( t4 );
SamplerState	g_shadowmapSampler		: register( s4 );

float4x4		g_cameraPositionToShadowCameraPosition		: register( c0 );
float4x4		g_shadowProjection							: register( c4 );

float3 reconstructInfo1	: register( c8 );
float4 reconstructInfo2	: register( c9 );

struct PS_Input
{
	float4 SV_Position		: SV_POSITION;

	float4 Position			: POSITION0;
	float2 UV				: UV0;
};

float GetNormalizedDepth(float2 uv)
{
	return g_gbuffer2Texture.Sample(g_gbuffer2Sampler, uv).w;
}

float ReconstructDepth(float z)
{
	return -((z * reconstructInfo1.x) + reconstructInfo1.y);
}

float3 ReconstructPosition(float2 screenXY, float depth)
{
	return float3( reconstructInfo2.xy * screenXY * (-depth), depth );
}

float4 ReconstructShadowmapPosition(float3 cameraPos)
{
	float4 shadowmapPos = mul( g_cameraPositionToShadowCameraPosition, float4(cameraPos,1.0) );
	shadowmapPos = shadowmapPos / shadowmapPos.w;
	return shadowmapPos;
}

float4 ReconstructProjectedShadowmapPosition(float4 shadowmapPosition)
{
	float4 shadowmapPos = mul( g_shadowProjection, shadowmapPosition );
	shadowmapPos = shadowmapPos / shadowmapPos.w;
	return shadowmapPos;
}

float2 GetShadowmapUV(float4 shadowmapPos)
{
	return float2( (shadowmapPos.x + 1.0) / 2.0f, 1.0 - (shadowmapPos.y + 1.0) / 2.0f );
}

float VSM(float2 moments, float t)
{
	float ex = moments.x;
	float ex2 = moments.y;

	float p = 0.0;
	if (t <= ex) p = 1.0;

	float variance = ex2 - ex * ex;
	variance = max(variance, 0.4 / (reconstructInfo1.x * reconstructInfo1.x));

	float d = t - ex;
	float p_max = variance / (variance + d * d);
	return max(p, p_max);
}

float4 main( const PS_Input Input ) : SV_Target
{
	float2 uv = Input.UV;
	// uv.y = 1.0 - uv.y;

	float3 cameraPos = ReconstructPosition(Input.Position.xy, ReconstructDepth(GetNormalizedDepth(uv)));

	float4 shadowmapPos = ReconstructShadowmapPosition(cameraPos);
	float4 projShadowmapPos = ReconstructProjectedShadowmapPosition(shadowmapPos);
	float2 shadowmapUV = GetShadowmapUV(projShadowmapPos);

	float4 Output = float4(0.0,0.0,0.0,1.0);

	float depth = (-shadowmapPos.z - reconstructInfo1.y) / reconstructInfo1.x;
	float2 shadowParam = g_shadowmapTexture.Sample(g_shadowmapSampler, shadowmapUV).xy;

	float shadow = VSM(shadowParam, depth );

	Output.x = shadow;
	return Output;
}

)";
