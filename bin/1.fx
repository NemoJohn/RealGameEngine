matrix WorldViewProj;

struct VS_INPUT
{
    float3 Pos : POSITION;
    float3 Normal : NORMAL;
    float2 Tex : TEXCOORD0;
};
struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Normal : TEXCOORD0;
    float2 Tex : TEXCOORD1;
};

texture2D myTexture;
sampler2D mySampler = sampler_state
{
    Texture = <myTexture>;
    MinFilter = Linear;
    MagFilter = Linear;
};

float n = 0;
PS_INPUT vs_main(VS_INPUT input)
{
    PS_INPUT output;
    input.Pos.z = sin(input.Pos.y + n) + sin(input.Pos.x + n);
    output.Pos = mul(float4(input.Pos, 1.0), WorldViewProj);
    output.Normal = input.Normal;
    output.Tex = input.Tex;
    return output;
}

float4 ps_main(PS_INPUT input) : SV_TARGET
{
    float4 texColor = tex2D(mySampler,input.Tex);
    float4 color = float4(1.0, 0.0, 0.0, 1.0);
    return texColor;
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