
#include "stdafx.h"
#include "DrawFlow.h"
#include "CSprite.h"
#include "CMSprite.h"


extern IDirect3DDevice9 *g_pDevice;
extern D3DPRESENT_PARAMETERS g_d3dpp;

CDrawFlow::CDrawFlow()
{
    m_nIndex = 0;
    ZeroMemory(m_drawC, sizeof(m_drawC));

    m_pPS = NULL;


//     ID3DXBuffer *shader = NULL;
//     ID3DXBuffer *err = NULL;
//     D3DXCompileShaderFromFile(_T("MyRes/ps.txt"), 0, 0, 
//                                 "Done", "ps_2_0", D3DXSHADER_DEBUG, &shader, &err, &m_pTable);
//     if (err)
//     {
//         MessageBoxA(NULL, (LPCSTR)err->GetBufferPointer(), "着色器", NULL);
//         return ;
//     }
// 
//     g_pDevice->CreatePixelShader((DWORD*)shader->GetBufferPointer(), &m_pPS);
// 
//     // 初始值
//     m_pTable->SetFloat(g_pDevice, "g_devLine", 382.0f); //明暗分割值
}

CDrawFlow::~CDrawFlow()
{

}
//////////////////////

void CDrawFlow::clear()
{
    if (m_nIndex > 0)
    {
        memset(m_drawC, 0, sizeof(m_drawC[0]) * m_nIndex );
    }

    m_nIndex = 0;
}


extern float g_light = 1.0f;
extern float g_duibi = 1.0f; //正常


void CDrawFlow::draw()
{
    if(NULL == g_pDevice)
        return ;

    eBlendType src  = (eBlendType)0;
    eBlendType dest = (eBlendType)0;
    IDirect3DTexture9* pTexture = NULL;
    eShape shape = (eShape)0;
    DWORD vFormat = 0;

    DWORD vFMX = VertexS::FVF;
    DWORD vF3D = Vertex3D::FVF;


	g_pDevice->SetTexture(0, NULL);


    // 上着色器 (注意不要影响到透明度)
    // 1.初始化
//     if (m_pTable && m_pPS)
//     {
//         m_pTable->SetFloat(g_pDevice, "g_fFinWeight", 1.0f);
//         m_pTable->SetFloat(g_pDevice, "g_light", g_light);
//         m_pTable->SetFloat(g_pDevice, "g_duibi", g_duibi); //对比度
//         m_pTable->SetInt(g_pDevice, "g_nCount", 0); //为了计数
//         g_pDevice->SetPixelShader(m_pPS);
//     }
    /// 着色器 end


    for (UINT i = 0; i < m_nIndex; ++i)
    {
        stDrawCommand *pDraw = &m_drawC[i];

        if(pDraw->src_blend != src) {
            g_pDevice->SetRenderState(D3DRS_SRCBLEND, pDraw->src_blend);
            src = pDraw->src_blend;
        }
        if (pDraw->dest_blend != dest) {
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, pDraw->dest_blend);
            dest = pDraw->dest_blend;
        }

        if (pDraw->pTexture != pTexture)
        {
            g_pDevice->SetTexture(0, pDraw->pTexture);
            pTexture = pDraw->pTexture; 
        }

        if (pDraw->vFormat != vFormat)
        {
            if(vF3D == pDraw->vFormat)
            {
                g_pDevice->SetStreamSource(0, (IDirect3DVertexBuffer9 *)pDraw->pVecBuf, 0, sizeof(Vertex3D)); //注意这个sizeof
            }
            else if (vFMX == pDraw->vFormat) //如果是 DrawPrimitiveUP则不需要这步
            {
                //g_pDevice->SetStreamSource(0, (IDirect3DVertexBuffer9 *)pDraw->pVecBuf, 0, sizeof(VertexS)); //注意这个sizeof
            }

            g_pDevice->SetFVF(pDraw->vFormat);
            vFormat = pDraw->vFormat;
        }

        // 画
        HRESULT hr ;
        if(vFMX == pDraw->vFormat)
        {
            //g_pDevice->DrawPrimitive(pDraw->shape, 0, pDraw->nCount);
            hr = g_pDevice->DrawPrimitiveUP(pDraw->shape, pDraw->nCount, pDraw->pVecBuf, sizeof(VertexS));
        }
        else if (vF3D == pDraw->vFormat)
        {
            hr = g_pDevice->DrawPrimitive(pDraw->shape, 0, pDraw->nCount);
        }

        //g_pDevice->SetPixelShader(NULL);
    }



	////// 先检查设备的有效性
	HRESULT hr_device = g_pDevice->TestCooperativeLevel();
	if (hr_device == D3DERR_DEVICELOST){
		printf("设备丢失\n");
		//todo: 释放资源
		CTextureMgr::instance().DeviceReset(); //释放纹理,

		//解除纹理引用

		if (g_pDevice->Reset(&g_d3dpp) == D3D_OK){

			// Store render target surface desc
			LPDIRECT3DSURFACE9 pBackBuffer;
			g_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
			//pBackBuffer->GetDesc(&m_d3dsdBackBuffer);
			pBackBuffer->Release();

			//todo: 重新加载纹理, (恢复)  or 绘制的时候再去

		}
	}
	else if (D3DERR_DEVICENOTRESET == hr_device)
	{
		printf("这个又是啥?\n");
	}
}