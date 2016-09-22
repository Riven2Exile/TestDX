
#ifndef DRAW_FLOW_H
#define DRAW_FLOW_H

/////////  ���Ͷ���
typedef D3DBLEND    eBlendType ;    //�������
typedef D3DPRIMITIVETYPE eShape;    //ͼԪ����

class IDirect3DPixelShader9;



// Ŀǰÿ֡���ִֻ�� DRAW_FLOW_SIZE �λ�������
#define DRAW_FLOW_SIZE 30000

// ������
struct stDrawCommand
{
    eBlendType src_blend;   //src blend
    eBlendType dest_blend;  //dest blend

    IDirect3DTexture9* pTexture;    //����(������α�֤������Ч? ����ָ��?)

    eShape shape;   //ͼԪ����
    DWORD vFormat;    //�����ʽ

    UINT nCount;    //����ͼԪ

    void *pVecBuf;  //��������

    /////��Ҫһ���Ƿ�͸���Ŀ���
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
    // ������������
    stDrawCommand m_drawC[DRAW_FLOW_SIZE]; 
    UINT m_nIndex;


    // ��ɫ��... (test)
    IDirect3DPixelShader9 *m_pPS;   //������ɫ��
    ID3DXConstantTable *m_pTable;   //����
};



#endif