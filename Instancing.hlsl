#include "Effect.fx"

struct VS_INSTANCED_COLOR_INPUT
{
    float3 position : POSITION;
    float4 color : COLOR0;
    float4x4 mtxTransform : INSTANCEPOS;
};

struct VS_INSTANCED_COLOR_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
//시스템 생성 변수로 정점 쉐이더에 전달되는 객체 인스턴스의 ID를 픽셀 쉐이더로 전달한다.
    float4 instanceID : INDEX;
};

//인스턴싱을 하면서 텍스쳐를 사용하는 경우 정점 쉐이더의 입력을 위한 구조체이다.
struct VS_INSTANCED_TEXTURED_COLOR_INPUT
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD0;
    float4x4 mtxTransform : INSTANCEPOS;
};

//인스턴싱을 하면서 텍스쳐를 사용하는 경우 정점 쉐이더의 출력을 위한 구조체이다.
struct VS_INSTANCED_TEXTURED_COLOR_OUTPUT               // = PS
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD0;
};

//인스턴싱을 하면서 텍스쳐와 Normal을 사용하는 경우 정점 쉐이더의 입력을 위한 구조체
struct VS_INSTANCED_TEXTURED_LIGHTING_COLOR_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD0;
    float4x4 mtxTransform : INSTANCEPOS;
};

//인스턴싱을 하면서 텍스쳐와 Normal을 사용하는 경우 정점 쉐이더의 출력을 위한 구조체
struct VS_INSTANCED_TEXTURED_LIGHTING_COLOR_OUTPUT
{
    float4 position : SV_POSITION;
    float3 positionW : POSITION;
    float3 normalW : NORMAL;
    float2 texCoord : TEXCOORD0;
};

VS_INSTANCED_COLOR_OUTPUT VSInstancedDiffusedColor(VS_INSTANCED_COLOR_INPUT input, uint instanceID : SV_InstanceID)
{
    VS_INSTANCED_COLOR_OUTPUT output = (VS_INSTANCED_COLOR_OUTPUT) 0;
    output.position = mul(float4(input.position, 1), input.mtxTransform);
    output.position = mul(output.position, gmtxView);
    output.position = mul(output.position, gmtxProjection);
    output.color = input.color;
    output.instanceID = instanceID;
    return output;
}


float4 PSInstancedDiffusedColor(VS_INSTANCED_COLOR_OUTPUT input) : SV_Target
{
    return input.color;
}

VS_INSTANCED_TEXTURED_COLOR_OUTPUT VSInstancedTexturedColor(VS_INSTANCED_TEXTURED_COLOR_INPUT input)
{
    VS_INSTANCED_TEXTURED_COLOR_OUTPUT output = (VS_INSTANCED_TEXTURED_COLOR_OUTPUT) 0;
    output.position = mul(mul(mul(float4(input.position, 1.0f), input.mtxTransform), gmtxView), gmtxProjection);
    output.texCoord = input.texCoord;

    return (output);
}

float4 PSInstancedTexturedColor(VS_INSTANCED_TEXTURED_COLOR_OUTPUT input) : SV_Target
{
    float4 cColor = gtxtTexture.Sample(gSamplerState, input.texCoord);

    return (cColor);
}

VS_INSTANCED_TEXTURED_LIGHTING_COLOR_OUTPUT VSInstancedTexturedLightingColor(VS_INSTANCED_TEXTURED_LIGHTING_COLOR_INPUT input)
{
    VS_INSTANCED_TEXTURED_LIGHTING_COLOR_OUTPUT output = (VS_INSTANCED_TEXTURED_LIGHTING_COLOR_OUTPUT) 0;
    output.normalW = mul(input.normal, (float3x3) input.mtxTransform);
    output.positionW = mul(float4(input.position, 1.0f), input.mtxTransform).xyz;
    output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
    output.texCoord = input.texCoord;

    return (output);
}

float4 PSInstancedTexturedLightingColor(VS_INSTANCED_TEXTURED_LIGHTING_COLOR_OUTPUT input) : SV_Target
{
    input.normalW = normalize(input.normalW);
    float4 cIllumination = Lighting(input.positionW, input.normalW);
    float4 cColor = gtxtTexture.Sample(gSamplerState, input.texCoord) * cIllumination;

    return (cColor);
}
