matrix WorldViewProj;
matrix viewMatrix;

float fluidity = 0.042f;
float flow = 0.21f;
float bias = 0.9f;
float noisyness = 0.057f;
float xScale = 0.37f;
float4 color = float4(0.0784f, 0.6031f, 1, 1);

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

texture volumeTexture;
sampler3D VolumeSampler = sampler_state
{
    Texture = <volumeTexture>;
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
    float3 uvw = float3(0, 0, 0);
    uvw.x = input.Tex0.x * xScale;
    uvw.y = fluidity * pow((1.6 + input.Tex0.y), 2) + flow * time_0_X;
    uvw.z = noisyness * time_0_X;
    
    float noisy = tex3D(VolumeSampler, uvw).r * 2 - 1;
    
    float flow = saturate(pow(1.7 - input.Tex0.y + 0.1 * noisy, 4));

   // Highlight the edge
    float t = saturate(3 * (0.95 - input.Tex0.y));
    flow += t * (t * (t - 2) + 1) * 6;

   // Give it color and texture
    return flow * (noisy + bias) * color;
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