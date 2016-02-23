#include "stdafx.h"
#include "YanZheng.h"


extern IDirect3DDevice9 *g_pDevice;




bool parseCodeImage(const char* pszPath)
{
    D3DXIMAGE_INFO info;
    HRESULT re = D3DXGetImageInfoFromFileA(pszPath, &info);
    if(re != S_OK)
        return false;


    IDirect3DTexture9 *pText = NULL;
    //D3DXCreateTextureFromFileA(g_pDevice, pszPath, &pText); //用没有 EX 的函数， 创建的纹理长宽会变成 2的 n次方
    re = D3DXCreateTextureFromFileExA(g_pDevice, pszPath, info.Width, info.Height, 
        info.MipLevels, 0/*D3DUSAGE_RENDERTARGET*/, info.Format, D3DPOOL_SYSTEMMEM, 
        D3DX_FILTER_TRIANGLE,D3DX_FILTER_TRIANGLE,D3DCOLOR_ARGB(255,0,0,0), NULL, NULL, &pText);

    FILE* pFile = fopen("D:/hehe.txt", "w");

    D3DLOCKED_RECT rc;
    pText->LockRect(0, &rc, NULL, 0);

    BYTE bR = 0, bG = 0, bB = 0;

    DWORD* pSrc = (DWORD*)rc.pBits;
    for (int i = 0; i < info.Height ; i++)
    {
        for (int j = 0; j < info.Width; j++)
        {
            bR = (*pSrc) >> 16;
            bG = (*pSrc) << 16 >> 24;
            bB = (*pSrc) & 0x000000ff;

           if (bR >= 205 && bG >= 205 && bB >= 205)
           {
                fprintf(pFile, "1");
           }
           else
           {
               fprintf(pFile, "8");
           }

           BYTE t = max( max(bR, bG), bB);

           *pSrc = t | t << 8 | t << 16;
               

            ++pSrc;

        }

        fprintf(pFile, "\r\n");
    }

    pText->UnlockRect(0);

    // 保存灰度图
    re = D3DXSaveTextureToFileA("D:/hehe.jpg", D3DXIFF_BMP, pText, NULL);

    
    pText->Release();

    fclose(pFile);


}