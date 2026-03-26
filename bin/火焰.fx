matrix WorldViewProj;
matrix viewMatrix;

float distortion_amount0 = 0.123f;
float distortion_amount1 = 0.091f;
float distortion_amount2 = 0.0723f;
float4 layer_speed = float4(0.68753f, 0.52000f, 0.75340f, 1);
//float4 height_attenuation = float4();

float time_0_X = 0;
struct VS_INPUT
{
    float3 Pos : POSITION;
    float3 Normal : NORMAL;
    float2 Tex : TEXCOORD0;
};
struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex0 : TEXCOORD0;
};

texture2D myTexture1;
texture2D myTexture2;
texture2D myTexture3;
sampler2D FireSampler = sampler_state
{
    Texture = <myTexture1>;
    MinFilter = Linear;
    MagFilter = Linear;
};
sampler2D DistortionSampler = sampler_state
{
    Texture = <myTexture2>;
    MinFilter = Linear;
    MagFilter = Linear;
};
sampler2D OpacitySampler = sampler_state
{
    Texture = <myTexture3>;
    MinFilter = Linear;
    MagFilter = Linear;
};

PS_INPUT vs_main(VS_INPUT input)
{
    PS_INPUT output;
    output.Pos = mul(float4(input.Pos, 1.0), WorldViewProj);
    output.Tex0 = input.Tex;
    return output;
}

float speed = -1.5f;
float rings = 33;
float exponent = 0.2;
float angle = 0;

float4 bx2(float x)
{
    return 2.0f * x - 1.0f;
}

float4 ps_main(PS_INPUT input) : SV_TARGET
{
    float4 noise1 = tex2D(DistortionSampler, float2(input.Tex0.x, input.Tex0.y + layer_speed.x * time_0_X));
    float4 noise2 = tex2D(DistortionSampler, float2(input.Tex0.x, input.Tex0.y + layer_speed.y * time_0_X));
    float4 noise3 = tex2D(DistortionSampler, float2(input.Tex0.x, input.Tex0.y + layer_speed.z * time_0_X));

    float4 noiseSum = bx2(noise1.g) * distortion_amount0 + bx2(noise2.b) * distortion_amount1 + bx2(noise3.b) * distortion_amount2;
    float2 perturbedBaseCoords = input.Tex0 + noiseSum.xy * (input.Tex0.y * 0.44f + 0.29f);
    
    float4 color1 = tex2D(FireSampler, perturbedBaseCoords);
    float4 color2 = tex2D(OpacitySampler, perturbedBaseCoords);
    return color1 * color2;
}

technique MyEffect01
{
    pass P0
    {
        VertexShader = compile vs_1_1 vs_main();
        PixelShader = compile ps_2_0 ps_main();
    }
}
//ShaderMode-SM1.0 2.0 3.0 4.0 4.1 4.2 5.0 6.0