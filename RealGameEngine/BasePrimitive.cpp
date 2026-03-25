#include "BasePrimitive.h"
#include "GameEngine.h"
#include "SubSystem/TextureCache.h"
#include "SubSystem/CameraManager.h"

BasePrimitive::BasePrimitive()
{
    
}

BasePrimitive::~BasePrimitive()
{
}

void BasePrimitive::CreateVertex()
{
    pDevice = GameEngine::GetDevice();

    //在显存中创建3个CustomVertex大小的显存空间
    //m_pVB该指针保存显存的首地址
    pDevice->CreateVertexBuffer(4 * col * raw * sizeof(CustomVertex),
        0, CustomVertex::FVF,
        D3DPOOL_DEFAULT, &m_pVB, NULL);

    //在内存中创建3个点并赋值 local space
    CustomVertex vertices[6400];
    int i = 0;
    for (int y = 0; y < raw; y++)
    {
        for (int x = 0; x < col; x++)
        {
            vertices[i].x = -1.0f + w * x;
            vertices[i].y = 1 - h * y;
            vertices[i].z = 0;
            vertices[i].u = 0 + (1.0f/ col) * x;
            vertices[i].v = 0 + (1.0f/ raw) * y;
            vertices[i].nx = 0;
            vertices[i].ny = 0;
            vertices[i].nz = -1;

            vertices[i+1].x = -1.0f + w * (x + 1);
            vertices[i+1].y = 1 - h * y;
            vertices[i+1].z = 0;
            vertices[i+1].u = 0 + (1.0f / col) * (x + 1);
            vertices[i+1].v = 0 + (1.0f / raw) * y;
            vertices[i+1].nx = 0;
            vertices[i+1].ny = 0;
            vertices[i+1].nz = -1;

            vertices[i + 2].x = -1.0f + w * x;
            vertices[i + 2].y = 1 - h * (y+1);
            vertices[i + 2].z = 0;
            vertices[i + 2].u = 0 + (1.0f / col) * x;
            vertices[i + 2].v = 0 + (1.0f / raw) * (y + 1);
            vertices[i+2].nx = 0;
            vertices[i+2].ny = 0;
            vertices[i+2].nz = -1;

            vertices[i + 3].x = -1.0f + w * (x + 1);
            vertices[i + 3].y = 1 - h * (y + 1);
            vertices[i + 3].z = 0;
            vertices[i + 3].u = 0 + (1.0f / col) * (x + 1);
            vertices[i + 3].v = 0 + (1.0f / raw) * (y + 1);
            vertices[i+3].nx = 0;
            vertices[i+3].ny = 0;
            vertices[i+3].nz = -1;
            i += 4;
        }
    }
   

    //加锁显存 为显存赋值 解锁-该操作效率极低不要放置到循环中操作
    //Lock加锁的第三个参数会返回显存的指针 操作该指针的内存会直接修改显存中的数据
   
    VOID* pVertices;
    m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0);
    memcpy(pVertices, vertices, sizeof(vertices));
    m_pVB->Unlock();

    D3DVERTEXELEMENT9 vertexElements[] =
    {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
        { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
        D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(vertexElements, &vertexDecl);

	LPD3DXBUFFER buffer = nullptr;
	D3DXCreateEffectFromFileA(pDevice, "画圈圈.fx", NULL, NULL, 0, NULL, &effect, &buffer);
    if (buffer)
    {
		OutputDebugStringA((char*)buffer->GetBufferPointer());
    }

    effect->SetTexture("myTexture", TextureCache::GetInstance()->GetTextureByID("1001"));
    effect->SetTexture("OtherTexture", TextureCache::GetInstance()->GetTextureByID("1002"));

}

void BasePrimitive::OnRender()
{
    static float angle = 0;
    angle += 0.01f;
    effect->SetFloat("angle", angle);

    static float time_0_x = 0;
    time_0_x += GameEngine::GetDeltaTime();
    effect->SetFloat("time_0_X", time_0_x);


	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	D3DXMATRIXA16 mvp = world * CameraManager::GetInstance()->GetViewMatrix() * CameraManager::GetInstance()->GetProjMatrix();

	effect->SetMatrix("WorldViewProj", &mvp);

	


    pDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CustomVertex) );
	pDevice->SetVertexDeclaration(vertexDecl);
	effect->SetTechnique("MyEffect01");
    UINT pass = 0;
	effect->Begin(&pass, 0);
    for (int i = 0; i < pass; i++)
    {
		effect->BeginPass(i);
        for (int i = 0; i < col * raw; i++)
        {
            pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
        }
        effect->EndPass();
    }
	effect->End();

   
}
