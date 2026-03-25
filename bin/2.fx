matrix WorldViewProj;
matrix viewMatrix;

float4 AmbientColor = float4(0.3f, 0.3f, 0.3f, 1);
float4 DiffuseColor = float4(0.67f, 0.67f, 0.67f, 1);
float4 SpecularColor = float4(0.67f, 0.67f, 0.67f, 1);
float Power = 15;


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

float angle = 0;
PS_INPUT vs_main(VS_INPUT input)
{
    PS_INPUT output;
    float3 normalDir = input.Pos+(input.Normal * input.Pos) * abs(sin(angle))*0.1f + 0.2f;
    output.Pos = mul(float4(normalDir, 1.0), WorldViewProj);
    output.Normal = mul(input.Normal, WorldViewProj);
    output.Tex = input.Tex;
    return output;
}

float3 EyeDir = float3(0, 0, 0);
float3 SpecularLightDir = float3(-3,3,5);

float4 ps_main(PS_INPUT input) : SV_TARGET
{
    float4 texColor = tex2D(mySampler,input.Tex);
    float3 lightdir = normalize(-1 * EyeDir);
    
    float3 SLD = normalize(SpecularLightDir);
    float3 normal = normalize(input.Normal);
    float3 eye = normalize(EyeDir);
    float3 R = normalize(reflect(SLD, normal));
    float DotRL = max(0,dot(R, eye));
    float DotNL = dot(normal,lightdir);
    float4 Specular = pow(DotRL, Power);
    //return saturate(texColor * AmbientColor + texColor * DiffuseColor * DotNL + texColor * SpecularColor * Specular);
    return texColor * SpecularColor * Specular;

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