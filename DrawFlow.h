
#ifndef DRAW_FLOW_H
#define DRAW_FLOW_H

/////////  类型定义
typedef D3DBLEND    eBlendType ;    //混合类型
typedef D3DPRIMITIVETYPE eShape;    //图元类型

class IDirect3DPixelShader9;



// 目前每帧最多只执行 DRAW_FLOW_SIZE 次绘制命令
#define DRAW_FLOW_SIZE 30000

// 绘制流
struct stDrawCommand
{
    eBlendType src_blend;   //src blend
    eBlendType dest_blend;  //dest blend

    IDirect3DTexture9* pTexture;    //纹理(这里如何保证纹理有效? 智能指针?)

    eShape shape;   //图元类型
    DWORD vFormat;    //顶点格式

    UINT nCount;    //几个图元

    void *pVecBuf;  //顶点数据

    /////需要一个是否透明的开关
};





class CDrawFlow
{
public:
    CDrawFlow();
    ~CDrawFlow();

    static CDrawFlow& Instance(){
        static CDrawFlow inst;
        return inst;
    }

    void clear();

    UINT getIndex()
    {
        return m_nIndex;
    }

    stDrawCommand* getFreeDrawFlow()
    {
        if (m_nIndex < 0 || m_nIndex >= DRAW_FLOW_SIZE)
        {
            return NULL;
        }

        return &m_drawC[m_nIndex];
    }

    void increaseIndex(){
        ++m_nIndex;
#ifdef _DEBUG
		if (m_nIndex >= DRAW_FLOW_SIZE)
		{
			MessageBoxA(0, "d","d", 0);
		}
#endif // _DEBUG
		
    }

    void draw();

private:
    // 绘制流的数据
    stDrawCommand m_drawC[DRAW_FLOW_SIZE]; 
    UINT m_nIndex;


    // 着色器... (test)
    IDirect3DPixelShader9 *m_pPS;   //像素着色器
    ID3DXConstantTable *m_pTable;   //常数
};



#endif