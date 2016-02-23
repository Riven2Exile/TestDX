#ifndef I_SPRITE_H
#define I_SPRITE_H

// interface
typedef unsigned long DWORD;
struct IDirect3DDevice9;
struct IDirect3DTexture9;

enum SpriteType{
    ST_MX,  //
    ST_3D,  //
};
extern IDirect3DDevice9 *g_pDevice; //声明


struct FRECT{
    float left;
    float top;
    float right;
    float bottom;

	FRECT():left(0.0f)
		,top(0.0f)
		,right(1.0f)
		,bottom(1.0f)
	{

	}
};


class iSprite
{
public:
    virtual bool LoadAImage(const char* pszName, IDirect3DDevice9 *pDevice) = 0;
    virtual void SetX(float x) = 0;
    virtual void SetY(float y) = 0;
    //void SetClipRect(FRECT& r);

    virtual float GetX() = 0;
    virtual float GetY() = 0;
    //FRECT GetClipRect() const;

    virtual void setWidth(float fw) = 0; //设置图元大小， 而不是纹理大小
    virtual void setHeight(float fh) = 0;
    virtual float getWidth() = 0;
    virtual float getHeight() = 0;

    virtual void SetColor(DWORD color) = 0;
    virtual DWORD GetColor() = 0;

    virtual void SetAlpha(unsigned int al) = 0;
    virtual unsigned int GetAlpha() = 0;

    // 缩放
    virtual void setStretchX(float x) = 0; //1.0f表示不缩放
    virtual void setStretchY(float y) = 0; //1.0f表示不缩放

    virtual void setTexture(IDirect3DTexture9* pTexture) = 0; //设置纹理

    virtual bool isClip() = 0;
    virtual void setClip(bool bClip) = 0;
    virtual void setClipRect(FRECT& rc) = 0; //test 裁剪

    virtual bool isVisible() = 0;
    virtual void setVisible(bool bVisible = true) = 0;

    virtual void Update() = 0;

    virtual void Draw() = 0;
};


iSprite* CreateSprite(SpriteType nType);
iSprite* CreateSprite(SpriteType nType, unsigned int nSize);

#endif