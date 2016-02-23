
#ifndef CSPRITE_H
#define CSPRITE_H

#include "iSprite.h"


////// vertex2 RHW
struct VertexS{
    float x, y, z;
    float rhw;
    DWORD color;
    float _u, _v;
    static const DWORD FVF;
    VertexS(float xx, float yy, float zz, float r, DWORD col, float u, float v)
    {
        x = xx;
        y = yy;
        z = zz;
        rhw = r;
        color = col;
        _u = u;
        _v = v;
    }
    VertexS(){} //没有实现
};



struct IDirect3DDevice9;
struct IDirect3DTexture9;
struct IDirect3DVertexBuffer9;

/* 后面可以引入dirty的概念 */

class CSprite : public iSprite
{
public:
    CSprite();
    virtual ~CSprite();

    bool LoadAImage(const char* pszName, IDirect3DDevice9 *pDevice);
    inline void SetX(float x);
    inline void SetY(float y);
    //void SetClipRect(FRECT& r);

    inline float GetX();
    inline float GetY();
    //FRECT GetClipRect() const;

    void setWidth(float fw); //设置图元大小， 而不是纹理大小
    void setHeight(float fh);
    float getWidth()    { return m_w; }
    float getHeight()   { return m_h; }

    void SetColor(DWORD color);
    DWORD GetColor();

    void SetAlpha(unsigned int al);
    unsigned int GetAlpha();

    // 缩放
    void setStretchX(float x); //1.0f表示不缩放
    void setStretchY(float y); //1.0f表示不缩放

    void setTexture(IDirect3DTexture9* pTexture); //设置纹理
    
    bool isClip();
    void setClip(bool bClip);
    void setClipRect(FRECT &cr); //test 裁剪

    bool isVisible();
    void setVisible(bool bVisible = true);

    void Update();

    void Draw();

private:
    float m_x;
    float m_y;
    float m_z;

    float m_w;
    float m_h;

    float m_iw; //纹理的宽度
    float m_ih; //纹理的高度

    //缩放
    float m_StretchX;
    float m_StretchY;

    //控制裁剪
    FRECT m_reClip;

    DWORD m_color;

    bool m_bVisible;

    bool m_bClip;   //是否需要被裁剪
    bool m_bDirty; 

    IDirect3DTexture9* m_pTexture;
    IDirect3DVertexBuffer9 *m_pVb;

    void *m_pTest; //自定义的顶点结构
};



////// 工厂方法
// 通过参数


#endif