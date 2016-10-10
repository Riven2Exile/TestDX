#include "stdafx.h"
#include "CMSprite.h"
#include "DrawFlow.h"

const DWORD Vertex3D::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;


CMSprite::CMSprite()
{
    m_bDirty = false;
    m_bClip = false;
}

CMSprite::~CMSprite()
{

}


bool CMSprite::LoadAImage(const char* pszName, IDirect3DDevice9 *pDevice)
{
    D3DXIMAGE_INFO info;
    D3DXGetImageInfoFromFileA(pszName, &info);

    D3DXCreateTextureFromFileExA(pDevice, pszName, info.Width, info.Height, 
        info.MipLevels, D3DUSAGE_DYNAMIC, info.Format, D3DPOOL_DEFAULT, D3DX_FILTER_TRIANGLE,  // D3DPOOL_DEFAULT才可行。。
        D3DX_FILTER_TRIANGLE, D3DCOLOR_ARGB(255,255,255,255), NULL, NULL, &m_pTexture);

    pDevice->CreateVertexBuffer(3*sizeof(Vertex3D),
        0/*D3DUSAGE_WRITEONLY*/,
        Vertex3D::FVF,
        D3DPOOL_DEFAULT/*D3DPOOL_MANAGED*/,
        &m_pVb,
        0);

    m_x = -1.0f;
    m_y = 0.0f;
    m_w = 1.0f;info.Width;
    m_h = 1.0f;info.Height;

    m_iw = 1.0f; info.Width;
    m_ih = 1.0f; info.Height;

    m_reClip.left = 0.f;
    m_reClip.top = 0.f;
    m_reClip.right = 1.0f;
    m_reClip.bottom = 1.0f;

    m_StretchX = 1.0f;
    m_StretchY = 1.0f;

    Vertex3D *pVec = NULL;
    if( FAILED(m_pVb->Lock(0, sizeof(Vertex3D)*/*6*/3, (void**)&pVec, 0) ) ) {
        MessageBoxA(NULL, "f", "f", NULL);
        return false;
    }

    float fix = /*0.0f; */  -0.5f;
    m_z = 1.0f;
    m_color = 0xffaaffff;

    // 注意坐标 
    /*
      y ^
        |
        |
        |
        ------> x
    */

     pVec[0] = Vertex3D(m_x  + fix, m_y + fix, m_z, 0xffff0000, 0.0f, 1.0f); // -1.0f, 0.0f
     pVec[1] = Vertex3D(m_x  + fix, m_y + m_h+ fix, m_z, 0xff00ff00, 0.0f, 0.0f); // -1.0f, 1.0f
     pVec[2] = Vertex3D(m_x + m_w + fix, m_y + m_h + fix, m_z, 0xffffffff, 1.0f, 0.0f); // 
//     float fixup = 1.0f;
//     pVec[0] = Vertex3D(-1.0f,-1.0f, fixup, 0xffff0000, 0.f, 0.f);
//     pVec[1] = Vertex3D(0.0f, 1.0f, fixup, 0xffffffff, 1.f, 1.f);
//     pVec[2] = Vertex3D(1.0f,-1.0f, fixup, 0xff0000ff, 0.f, 1.f);

    //pVec[3] = Vertex3D(m_x + m_w + fix, m_y + fix, m_z, m_color, 1.0f, 1.0f);

    m_pVb->Unlock();
    m_pTest = m_pVb;//test

	m_bDirty = true; //标记为脏

    return true;
}

void CMSprite::SetX(float x) // 先不考虑坐标的转换
{
    m_x = x;
    m_bDirty = true;
}

void CMSprite::SetY(float y)
{
    m_y = y;
    m_bDirty = true;
}
//void SetClipRect(FRECT& r);

float CMSprite::GetX()
{
    return 0.0f;
}

float CMSprite::GetY()
{
    return 0.0f;
}
//FRECT GetClipRect() const;

void CMSprite::setWidth(float fw)
{

}

void CMSprite::setHeight(float fh)
{

}

void CMSprite::SetColor(DWORD color)
{

}
DWORD CMSprite::GetColor()
{
    return 0;
}

// 缩放
void CMSprite::setStretchX(float x) //1.0f表示不缩放
{

}
void CMSprite::setStretchY(float y) //1.0f表示不缩放
{

}

void CMSprite::setTexture(const stTexInfo* pTexture) //设置纹理
{
	if (pTexture)
	{
		m_pTexture = pTexture->pTex;
	}
	else{
		m_pTexture = nullptr;
	}
}

bool CMSprite::isClip()
{
    return m_bClip;
}
void CMSprite::setClip(bool bClip)
{

}
void CMSprite::setClipRect(FRECT& rc)
{

}

extern IDirect3DDevice9* g_pDevice;

void CMSprite::Update()
{
    
    if (m_bDirty)
    {
        m_bDirty = false;
    }
}

void CMSprite::Draw()
{
    ///// 以下是改版绘制流
    stDrawCommand* pDraw = CDrawFlow::Instance().getFreeDrawFlow();
    if (pDraw)
    {
        pDraw->src_blend = D3DBLEND_SRCALPHA;
        pDraw->dest_blend = D3DBLEND_INVSRCALPHA;
        pDraw->pTexture = m_pTexture;
        pDraw->shape = D3DPT_TRIANGLESTRIP;
        pDraw->vFormat = Vertex3D::FVF;
        pDraw->nCount = 1;
        pDraw->pVecBuf = m_pTest;

        CDrawFlow::Instance().increaseIndex();
    }
}