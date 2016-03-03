#ifndef CM_SPRITE_H
#define CM_SPRITE_H

#include "iSprite.h"


////// vertex 3D
struct Vertex3D {
    float x, y, z;
    DWORD color;
    float _u, _v;
    static const DWORD FVF;

    Vertex3D(float xx, float yy, float zz, DWORD col, float u, float v)
    {
        x = xx;
        y = yy;
        z = zz;
        color = col;
        _u = u;
        _v = v;
    }
    Vertex3D() {}
};




// 使用矩阵的精灵

class CMSprite : public iSprite
{
public:
    CMSprite();
    virtual ~CMSprite();

    virtual bool LoadAImage(const char* pszName, IDirect3DDevice9 *pDevice);
    virtual void SetX(float x);
    virtual void SetY(float y);
    //void SetClipRect(FRECT& r);

    virtual float GetX() ;
    virtual float GetY() ;
    //FRECT GetClipRect() const;

    virtual void setWidth(float fw) ; //设置图元大小， 而不是纹理大小
    virtual void setHeight(float fh) ;
    float getWidth()    { return m_w; }
    float getHeight()   { return m_h; }

    virtual void SetColor(DWORD color) ;
    virtual DWORD GetColor() ;

    virtual void SetAlpha(unsigned int al){}
    virtual unsigned int GetAlpha() {return 0;}

    // 缩放
    virtual void setStretchX(float x) ; //1.0f表示不缩放
    virtual void setStretchY(float y) ; //1.0f表示不缩放

    virtual void setTexture(IDirect3DTexture9* pTexture) ; //设置纹理
	virtual void setTextureU1(const float& t) {}
	virtual void setTextureU2(const float& t) {}
	virtual void setTextureV1(const float& t) {}
	virtual void setTextureV2(const float& t) {}

    virtual bool isClip();
    virtual void setClip(bool bClip);
    virtual void setClipRect(FRECT& rc); //test 裁剪

    virtual void setVisible(bool bVisible /* = true */) {}
    virtual bool isVisible() { return true; }

    virtual void Update() ;

    virtual void Draw() ;

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
    bool m_bClip;

    DWORD m_color;


    bool m_bDirty; 

    IDirect3DTexture9* m_pTexture;
    IDirect3DVertexBuffer9 *m_pVb;

    void *m_pTest; //自定义的顶点结构

    //static IDirect3DDevice9 * m_pDevice;
};

#endif