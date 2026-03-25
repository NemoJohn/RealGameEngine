matrix WorldViewProj;
matrix viewMatrix;


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
texture2D OtherTexture;
sampler2D OtherSampler = sampler_state
{
    Texture = <OtherTexture>;
    MinFilter = Linear;
    MagFilter = Linear;
};

PS_INPUT vs_main(VS_INPUT input)
{
    PS_INPUT output;
    output.Pos = mul(float4(input.Pos, 1.0), WorldViewProj);
    output.Normal = input.Normal;
    output.Tex = input.Tex;
    return output;
}

float angle = 0;
float4 ps_main(PS_INPUT input) : SV_TARGET
{
    float4 texColor1 = tex2D(mySampler,input.Tex);
    float2 offsetUV = float2(input.Tex.x + (sin(angle) * 2) / 512.0f, 
    input.Tex.y + (cos(angle) * 2) / 512.0f);
    float4 texColor2 = tex2D(mySampler, offsetUV);
    float4 color = texColor1 - texColor2;
    float gray = 0.3 * color.r + 0.6 * color.g + 0.1 * color.b;
    float4 color2 = float4(gray, gray, gray, 1);
    return color2 + float4(0.5,0.5,0.5,1);

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