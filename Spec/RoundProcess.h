// 圆形的进度条

typedef unsigned long DWORD;

struct IDirect3DDevice9;
struct IDirect3DTexture9;
struct IDirect3DVertexBuffer9;

class RoundProcess
{
public:
    RoundProcess();
    ~RoundProcess();


    void init();
    void loadImage(const char* pszName, IDirect3DDevice9* pDev);
    void setProcees(float fValue);  //百分比 (0.0f - 1.0f)
    
    void update();
    void draw();

private:
    bool m_bDirty;

    float m_x;
    float m_y;

    float m_w;
    float m_h;

    //控制裁剪
    //FRECT m_reClip;

    DWORD m_color;

    IDirect3DTexture9* m_pTexture;
    IDirect3DVertexBuffer9 *m_pVb;
};