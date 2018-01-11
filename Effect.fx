#include "Light.fx"

// 카메라 변환 행렬과 투영 변환 행렬을 위한 쉐이더 변수를 선언한다.
cbuffer cbViewProjectionMatrix : register(b0)
{
	matrix gmtxView : packoffset(c0);
	matrix gmtxProjection : packoffset(c4);
}

// 월드 변환 행렬을 위한 쉐이더 변수를 선언한다.(슬롯 1을 사용)
cbuffer cbWorldMatrix : register(b1)
{
	matrix gmtxWorld : packoffset(c0);
}

Texture2D gtxtTexture : register(t0);
SamplerState gSamplerState : register(s0);
Texture2D gtxtDetailTexture : register(t1);
SamplerState gDetailSamplerState : register(s1);

struct VS_INPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
};
// 정점-쉐이더의 출력을 위한 구조체이다.
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.position = mul(input.position, gmtxWorld);
	output.position = mul(output.position, gmtxView);
	output.position = mul(output.position, gmtxProjection);
	output.color = input.color;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	return input.color;
}

//텍스쳐를 사용하는 경우 정점 쉐이더의 입력을 위한 구조체이다.
struct VS_TEXTURED_COLOR_INPUT
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD0;
};

//텍스쳐를 사용하는 경우 정점 쉐이더의 출력을 위한 구조체이다.
struct VS_TEXTURED_COLOR_OUTPUT
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD0;
};

VS_TEXTURED_COLOR_OUTPUT VSTexturedColor(VS_TEXTURED_COLOR_INPUT input)
{
    VS_TEXTURED_COLOR_OUTPUT output = (VS_TEXTURED_COLOR_OUTPUT) 0;
    output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
    output.texCoord = input.texCoord;

    return (output);
}

//각 픽셀에 대하여 텍스쳐 샘플링을 하기 위한 픽셀 쉐이더 함수이다.
float4 PSTexturedColor(VS_TEXTURED_COLOR_OUTPUT input) : SV_Target
{
    float4 cColor = gtxtTexture.Sample(gSamplerState, input.texCoord);

    return (cColor);
}

//디테일 텍스쳐를 사용하는 경우 정점 쉐이더의 입력과 출력을 위한 구조체이다.
struct VS_DETAIL_TEXTURED_COLOR_INPUT
{
    float3 position : POSITION;
    float2 texCoordBase : TEXCOORD0;
    float2 texCoordDetail : TEXCOORD1;
};

struct VS_DETAIL_TEXTURED_COLOR_OUTPUT
{
    float4 position : SV_POSITION;
    float2 texCoordBase : TEXCOORD0;
    float2 texCoordDetail : TEXCOORD1;
};

VS_DETAIL_TEXTURED_COLOR_OUTPUT VSDetailTexturedColor(VS_DETAIL_TEXTURED_COLOR_INPUT input)
{
    VS_DETAIL_TEXTURED_COLOR_OUTPUT output = (VS_DETAIL_TEXTURED_COLOR_OUTPUT) 0;
    output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxWorld), gmtxView), gmtxProjection);
    output.texCoordBase = input.texCoordBase;
    output.texCoordDetail = input.texCoordDetail;

    return (output);
}

float4 PSDetailTexturedColor(VS_DETAIL_TEXTURED_COLOR_OUTPUT input) : SV_Target
{
    float4 cBaseTexColor = gtxtTexture.Sample(gSamplerState, input.texCoordBase);
    float4 cDetailTexColor = gtxtDetailTexture.Sample(gDetailSamplerState, input.texCoordDetail);
    float4 cColor = saturate((cBaseTexColor * 0.5f) + (cDetailTexColor * 0.5f));

    return (cColor);
}

//조명을 사용하는 경우 정점 쉐이더의 입력을 위한 구조체이다.
struct VS_LIGHTING_COLOR_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

//조명을 사용하는 경우 정점 쉐이더의 출력을 위한 구조체이다.
struct VS_LIGHTING_COLOR_OUTPUT
{
    float4 position : SV_POSITION;
//월드좌표계에서 정점의 위치와 법선 벡터를 나타낸다.
    float3 positionW : POSITION;
    float3 normalW : NORMAL;
};

//조명의 영향을 계산하기 위한 정점의 법선 벡터와 정점의 위치를 계산하는 정점 쉐이더 함수이다.
VS_LIGHTING_COLOR_OUTPUT VSLightingColor(VS_LIGHTING_COLOR_INPUT input)
{
    VS_LIGHTING_COLOR_OUTPUT output = (VS_LIGHTING_COLOR_OUTPUT) 0;
//조명의 영향을 계산하기 위하여 월드좌표계에서 정점의 위치와 법선 벡터를 구한다.
    output.normalW = mul(input.normal, (float3x3) gmtxWorld);
    output.positionW = mul(float4(input.position, 1.0f), gmtxWorld).xyz;
    output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);

    return (output);
}

//각 픽셀에 대하여 조명의 영향을 반영한 색상을 계산하기 위한 픽셀 쉐이더 함수이다.
float4 PSLightingColor(VS_LIGHTING_COLOR_OUTPUT input) : SV_Target
{
    input.normalW = normalize(input.normalW);
    float4 cIllumination = Lighting(input.positionW, input.normalW);

    return (cIllumination);
}

//텍스쳐와 조명을 같이 사용하는 경우 정점 쉐이더의 입력을 위한 구조체이다.
struct VS_TEXTURED_LIGHTING_COLOR_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD0;
};

//텍스쳐와 조명을 같이 사용하는 경우 정점 쉐이더의 출력을 위한 구조체이다.
struct VS_TEXTURED_LIGHTING_COLOR_OUTPUT
{
    float4 position : SV_POSITION;
    float3 positionW : POSITION;
    float3 normalW : NORMAL;
    float2 texCoord : TEXCOORD0;
};

//디테일 텍스쳐와 조명을 같이 사용하는 경우 정점 쉐이더의 입력을 위한 구조체이다.
struct VS_DETAIL_TEXTURED_LIGHTING_COLOR_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texCoordBase : TEXCOORD0;
    float2 texCoordDetail : TEXCOORD1;
};

//디테일 텍스쳐와 조명을 같이 사용하는 경우 정점 쉐이더의 출력을 위한 구조체이다.
struct VS_DETAIL_TEXTURED_LIGHTING_COLOR_OUTPUT
{
    float4 position : SV_POSITION;
    float3 positionW : POSITION;
    float3 normalW : NORMAL;
    float2 texCoordBase : TEXCOORD0;
    float2 texCoordDetail : TEXCOORD1;
};

VS_TEXTURED_LIGHTING_COLOR_OUTPUT VSTexturedLightingColor(VS_TEXTURED_LIGHTING_COLOR_INPUT input)
{
    VS_TEXTURED_LIGHTING_COLOR_OUTPUT output = (VS_TEXTURED_LIGHTING_COLOR_OUTPUT) 0;
    output.normalW = mul(input.normal, (float3x3) gmtxWorld);
    output.positionW = mul(float4(input.position, 1.0f), gmtxWorld).xyz;
    output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
    output.texCoord = input.texCoord;

    return (output);
}

float4 PSTexturedLightingColor(VS_TEXTURED_LIGHTING_COLOR_OUTPUT input) : SV_Target
{
    input.normalW = normalize(input.normalW);
    float4 cIllumination = Lighting(input.positionW, input.normalW);
    float4 cColor = gtxtTexture.Sample(gSamplerState, input.texCoord) * cIllumination;

    return (cColor);
}

VS_DETAIL_TEXTURED_LIGHTING_COLOR_OUTPUT VSDetailTexturedLightingColor(VS_DETAIL_TEXTURED_LIGHTING_COLOR_INPUT input)
{
    VS_DETAIL_TEXTURED_LIGHTING_COLOR_OUTPUT output = (VS_DETAIL_TEXTURED_LIGHTING_COLOR_OUTPUT) 0;
    output.normalW = mul(input.normal, (float3x3) gmtxWorld);
    output.positionW = mul(float4(input.position, 1.0f), gmtxWorld).xyz;
    output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
    output.texCoordBase = input.texCoordBase;
    output.texCoordDetail = input.texCoordDetail;

    return (output);
}

float4 PSDetailTexturedLightingColor(VS_DETAIL_TEXTURED_LIGHTING_COLOR_OUTPUT input) : SV_Target
{
    input.normalW = normalize(input.normalW);
    float4 cIllumination = Lighting(input.positionW, input.normalW);
    float4 cBaseTexColor = gtxtTexture.Sample(gSamplerState, input.texCoordBase);
    float4 cDetailTexColor = gtxtDetailTexture.Sample(gDetailSamplerState, input.texCoordDetail);
    float4 cColor = saturate((cBaseTexColor * 0.5f) + (cDetailTexColor * 0.5f));

    return (cColor * cIllumination);
}
